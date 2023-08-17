#include <linux/of_address.h>
#include <linux/clocksource.h>
#include <linux/irqchip.h>
#include <linux/smp.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/smp_plat.h>
#include <asm/smp_scu.h>
#include <asm/cacheflush.h>
#include <linux/of_clk.h>

#define CHIP_FOURTH_CPU  3
#define CHIP_THIRD_CPU   2
#define CHIP_SECOND_CPU  1
#define CHIP_TRI_IRQ_NUM 192
#define CHIP_L2C_AUX_VAL 0x430001
#define CHIP_L2C_AUX_MASK 0xFFB0FFFE
#define CHIP_GLOBAL_SOFT_RESET_SEQ1 0x51162100
#define CHIP_GLOBAL_SOFT_RESET_SEQ2 0xaee9deff
#define SCCTRL			0x000

enum chip_pwr_on_rest_bits {
	CHIP_PWR_ON_RESET_BIT_6 = 6,
	CHIP_PWR_ON_RESET_BIT_7,
	CHIP_PWR_ON_RESET_BIT_8,
	CHIP_PWR_ON_RESET_BIT_23 = 23,
};

enum chip_cpu_core_soft_rest_bits {
	CHIP_CPU_CORE_SOFT_RESET_BIT_12 = 12,
	CHIP_CPU_CORE_SOFT_RESET_BIT_13,
	CHIP_CPU_CORE_SOFT_RESET_BIT_14,
	CHIP_CPU_CORE_SOFT_RESET_BIT_25 = 25,
};

struct none_mach_addr {
	u32 ctrl_base;            /* sysctrl 基地址   */
	u32 crg_base;             /* crg 基地址       */
	u32 reboot_addr;          /* reboot寄存器地址 */
	u32 smp_resume_addr;      /* 副核解复位基地址 */
	u32 secondary_boot_addr;  /* 副核启动入口地址 */
};

struct none_mach_addr g_none_mach_addr;
volatile void __iomem* sysctl_base;

struct none_mach_addr *chip_get_mach_addr(void)
{
	return &g_none_mach_addr;
}

void chip_get_smp_resume_addr(void)
{
	struct device_node *np = NULL;
	u32 offset;

	/* 获取crg 基地址 */
	np = of_find_compatible_node(NULL, NULL, "tri,crg");
	if (!np) {
		pr_err("failed to find none,crg node\n");
		return;
	}
	g_none_mach_addr.crg_base = (u32)of_iomap(np, 0);
	if (!g_none_mach_addr.crg_base) {
		pr_err("failed to map address\n");
		return;
	}

	/* 获取多核启动唤醒 基地址 */
	if (of_property_read_u32(np, "resume-offset", &offset) < 0) {
		pr_err("failed to find resume-offset property\n");
		return;
	}
	g_none_mach_addr.smp_resume_addr =
		g_none_mach_addr.crg_base + offset;
}

void chip_get_reboot_addr(void)
{
	struct device_node *np = NULL;
	u32 offset;

	/* 获取crg 基地址 */
	np = of_find_compatible_node(NULL, NULL, "tri,crg");
	if (!np) {
		pr_err("failed to find none,crg node\n");
		return;
	}
	g_none_mach_addr.crg_base = (u32)of_iomap(np, 0);
	if (!g_none_mach_addr.crg_base) {
		pr_err("failed to map address\n");
		return;
	}

	/* 获取芯片软复位 基地址 */
	if (of_property_read_u32(np, "reboot-offset", &offset) < 0) {
		pr_err("failed to find reboot-offset property\n");
		return;
	}
	g_none_mach_addr.reboot_addr =
		g_none_mach_addr.crg_base + offset;
}
void chip_get_secondary_boot_addr(void)
{
	struct device_node *np = NULL;
	u32 offset;

	/* 获取sysctrl 基地址 */
	np = of_find_compatible_node(NULL, NULL, "tri,sysctrl");
	if (!np) {
		pr_err("failed to find none,sysctrl node\n");
		return;
	}
	g_none_mach_addr.ctrl_base = (u32)of_iomap(np, 0);
	if (!g_none_mach_addr.ctrl_base) {
		pr_err("failed to map address\n");
		return;
	}

	/* 获取多核启动测试寄存器 基地址 */
	if (of_property_read_u32(np, "smp-offset", &offset) < 0) {
		pr_err("failed to find smp-offset property\n");
		return;
	}
	g_none_mach_addr.secondary_boot_addr =
		g_none_mach_addr.ctrl_base + offset;
}

static int __init chip_arch_init_early(void)
{
	chip_get_smp_resume_addr();
	chip_get_reboot_addr();
	chip_get_secondary_boot_addr();
	return 0;
}

void chip_arch_restart(enum reboot_mode mode, const char *cmd)
{
	printk("\nSystem Reboot(%s)!!!", cmd);
	/* 0x51162100&&0xaee9deff芯片设计约定的复位命令 */
	writel_relaxed(CHIP_GLOBAL_SOFT_RESET_SEQ1, (uintptr_t *)g_none_mach_addr.reboot_addr);
	writel_relaxed(CHIP_GLOBAL_SOFT_RESET_SEQ2, (uintptr_t *)g_none_mach_addr.reboot_addr);
}
EXPORT_SYMBOL(chip_arch_restart);

early_initcall(chip_arch_init_early);


static const char *const tr6560_dt_board_compat[] = {
	"triductor,tr6560",
	NULL
};



static void tri_set_cpu(unsigned int cpu)
{
	u32 value;
	struct none_mach_addr *none_mach_addr = chip_get_mach_addr();

	switch (cpu) {
#ifdef CONFIG_MACH_TR6560
	case CHIP_SECOND_CPU:
		value = readl_relaxed((u32 *)none_mach_addr->smp_resume_addr);
		value &= ~(0x1 << CHIP_CPU_CORE_SOFT_RESET_BIT_25); /* bit25: cpu核软复位 */
		value &= ~(0x1 << CHIP_PWR_ON_RESET_BIT_23); /* bit23: cpu核上电复位 */
		writel_relaxed(value, (u32 *)none_mach_addr->smp_resume_addr);
		break;
#endif
	default:
		break;
	}
}

void tri_set_cpu_jump(int cpu, void *jump_addr)
{
	struct none_mach_addr *none_mach_addr = chip_get_mach_addr();

	cpu = cpu_logical_map(cpu);
	if (!cpu || !none_mach_addr->secondary_boot_addr)
		return;

	writel_relaxed(virt_to_phys(jump_addr), (u32 *)none_mach_addr->secondary_boot_addr);
}

int tri_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	tri_set_cpu_jump(cpu, secondary_startup);
	tri_set_cpu(cpu);
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	return 0;
}


static void __init tri_sysctl_init(void __iomem *base,
				    unsigned int extra_clear,
				    unsigned int extra_set)
{
	u32 scctrl;

	if (WARN_ON(!base))
		return;
	sysctl_base = base;
	scctrl = readl(base + SCCTRL);
	scctrl |= extra_set;
	scctrl &= ~extra_clear;
	writel(scctrl, base + SCCTRL);
}


static void __init tri_dt_timer_init(void)
{
	struct device_node *node;
	unsigned int extra_set;
	unsigned int extra_clear;
	int err;
	printk("[%s(%d)] warning:mdesc->init_time\n", __func__, __LINE__);

	node = of_find_compatible_node(NULL, NULL, "arm,sp810");
	if (WARN_ON(!node))
		return;
	err = of_property_read_u32(node, "extra-set", &extra_set);
	if (err)
		extra_set = 0;

	err = of_property_read_u32(node, "extra-clear", &extra_clear);
	if (err)
		extra_clear = 0;

	tri_sysctl_init(of_iomap(node, 0), extra_clear, extra_set);

	of_clk_init(NULL);
	//clocksource_of_init();
	timer_probe();

}

static const struct smp_operations tri_smp_ops __initconst = {
	.smp_boot_secondary     = tri_boot_secondary,
};




CPU_METHOD_OF_DECLARE(tri_smp_tr6560, "tri,tr6560-cpu-method",
			&tri_smp_ops);



DT_MACHINE_START(TR6560_DT, "Triductor TR6560")
        .dt_compat   = tr6560_dt_board_compat,
        .atag_offset = 0x100, /* atag偏移0x100,和boot协商一致 */
        .restart     = chip_arch_restart,
        .nr_irqs     = CHIP_TRI_IRQ_NUM,
#ifdef CONFIG_CACHE_L2X0
        .l2c_aux_val = CHIP_L2C_AUX_VAL, /* a9芯片带外置l2 cache */
        .l2c_aux_mask = CHIP_L2C_AUX_MASK
#endif
MACHINE_END
