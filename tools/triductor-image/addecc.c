/******************************************************************************
******************************************************************************
  文件名称: addecc.c
  功能描述: addecc工具，用于flash烧片
  版本描述: V1.0

  创建日期: D2012_09_11

  修改记录:
            生成初稿.
******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>


/* VSPM350 FLASH controller not need page0 special treatment */
#define TRI_BIN_WITH_PAGE0       0

#define TRI_ADDECC_VERSION       "V601"

#define TRI_MAX_PAGE_SIZE        8192
#define TRI_MAX_OOB_SIZE         512
#define TRI_MAX_CHECKSUM_LEN     16

#define TRI_MAX_LFSR_BITS        2048

typedef int tri_int32;
typedef char tri_char8;
typedef unsigned char tri_uchar8;
typedef unsigned long tri_ulong32;
typedef unsigned int tri_uint32;
typedef void tri_void;

tri_int32 g_i_lfsr_len;
tri_char8 g_ac_lfsr_poly[TRI_MAX_LFSR_BITS];
tri_char8 g_ac_lfsr_value[TRI_MAX_LFSR_BITS];

const tri_char8* const g_pc_short_options = "hvi:o:b:p:s:";

static struct option g_ast_long_options[] =
{
    {"input",       1,        NULL,    'i'},    /* input file name */
    {"output",      1,        NULL,    'o'},    /* output file name */
    {"eccbit",      1,        NULL,    'b'},    /* ecc type:1/4/8/24 */
    {"page",        1,        NULL,    'p'},    /* pagesize:2048/4096/8192 */
    {"spare",       1,        NULL,    's'},    /* spare area size/OOB size */
    {"help",        0,        NULL,    'h'},    /* display help info */
    {"version",     0,        NULL,    'v'},    /* display tool's version */
    {NULL,          0,        NULL,    0  },
};

typedef enum hi_ecc_type
{
    TRI_ECC_NONE_EN  = 0,
    TRI_ECC_1BIT_EN  = 1,
    TRI_ECC_4BIT_EN  = 4,
    TRI_ECC_8BIT_EN  = 8,
    TRI_ECC_24BIT_EN = 24,
    TRI_ECC_INVALID
}TRI_ECC_TYPE_EN;

typedef enum hi_page_type
{
    TRI_PAGE_SIZE_2K_EN  = 2048,
    TRI_PAGE_SIZE_4K_EN  = 4096,
    TRI_PAGE_SIZE_8K_EN  = 8192,
    TRI_PAGE_SIZE_INVALID
}TRI_PAGE_SIZE_EN;

static tri_ulong32 hi_tools_ecc_checksum8(tri_uchar8 *puc_data, tri_ulong32 ul_size)
{
    tri_ulong32 i = 0;
    tri_ulong32 ul_accum = 0;

    for (i = 0; i < ul_size; i++)
    {
        ul_accum += puc_data[i];
    }

    return ul_accum;
}

//enc_data_last[24] 初始值 0xFFFFFF ;
// [  23    22    21     20   19    18   17    16   15    14  ]
//  P2048 P2048' P1024 P1024' P512 P512' P256 P256' P128 P128'
// [ 13  12   11  10   9   8    7  6  5   4  3   2  1   0 ]
//  P64 P64' P32 P32' P16 P16' P8 P8' P4 P4' P2 P2' P1 P1'
//addr 表示第几个字节
static tri_void hi_tools_ecc_1bit_make(tri_uint32 ui_addr, tri_uchar8 uc_data_in, tri_uchar8 *puc_enc_data, tri_uchar8 *puc_enc_data_last)
{
    tri_int32 i = 0;
    // ecc_data_in to ECC calculate module
    tri_uchar8 auc_ecc_l1[8] ;
    tri_uchar8 auc_ecc_h1[8] ;
    tri_uchar8 uacnxt_ecc_reg[24];
    tri_uchar8 uc_ecc_p4ol;
    tri_uchar8 uc_ecc_p4el;
    tri_uchar8 uc_ecc_p2ol;
    tri_uchar8 uc_ecc_p2el;
    tri_uchar8 uc_ecc_p1ol;
    tri_uchar8 uc_ecc_p1el;
    tri_uchar8 uc_ecc_p4oh;
    tri_uchar8 uc_ecc_p4eh;
    tri_uchar8 uc_ecc_p2oh;
    tri_uchar8 uc_ecc_p2eh;
    tri_uchar8 uc_ecc_p1oh;
    tri_uchar8 uc_ecc_p1eh;
    tri_uchar8 uc_ecc_p8o;
    tri_uchar8 uc_ecc_p8e;
    tri_uchar8 uc_ecc_p4o;
    tri_uchar8 uc_ecc_p4e;
    tri_uchar8 uc_ecc_p2o;
    tri_uchar8 uc_ecc_p2e;
    tri_uchar8 uc_ecc_p1o;
    tri_uchar8 uc_ecc_p1e;
    tri_uchar8 uc_ecc_pr;
    tri_uchar8 auc_ecc_data_in[16] = {0};
    tri_uchar8 auc_addr_in[9] = {0};

    for (i = 0; i < 8; i++)
    {
        auc_ecc_data_in[i] = (uc_data_in >> i)&0x1;
    }

    for (i = 0; i < 9; i++)
    {
        auc_addr_in[i] = (ui_addr >> i)&0x1;
    }

    //
    auc_ecc_l1[0] = auc_ecc_data_in[0] ^ auc_ecc_data_in[1];
    auc_ecc_l1[1] = auc_ecc_data_in[0] ^ auc_ecc_data_in[2];
    auc_ecc_l1[2] = auc_ecc_data_in[1] ^ auc_ecc_data_in[3];
    auc_ecc_l1[3] = auc_ecc_data_in[2] ^ auc_ecc_data_in[3];
    auc_ecc_l1[4] = auc_ecc_data_in[4] ^ auc_ecc_data_in[5];
    auc_ecc_l1[5] = auc_ecc_data_in[4] ^ auc_ecc_data_in[6];
    auc_ecc_l1[6] = auc_ecc_data_in[5] ^ auc_ecc_data_in[7];
    auc_ecc_l1[7] = auc_ecc_data_in[6] ^ auc_ecc_data_in[7];

    // ---------------------------------------------------------------------
    // level one ECC calculate for high 8bit
    // ---------------------------------------------------------------------
    auc_ecc_h1[0] = auc_ecc_data_in[8] ^ auc_ecc_data_in[9];
    auc_ecc_h1[1] = auc_ecc_data_in[8] ^ auc_ecc_data_in[10];
    auc_ecc_h1[2] = auc_ecc_data_in[9] ^ auc_ecc_data_in[11];
    auc_ecc_h1[3] = auc_ecc_data_in[10] ^ auc_ecc_data_in[11];
    auc_ecc_h1[4] = auc_ecc_data_in[12] ^ auc_ecc_data_in[13];
    auc_ecc_h1[5] = auc_ecc_data_in[12] ^ auc_ecc_data_in[14];
    auc_ecc_h1[6] = auc_ecc_data_in[13] ^ auc_ecc_data_in[15];
    auc_ecc_h1[7] = auc_ecc_data_in[14] ^ auc_ecc_data_in[15];

    // ---------------------------------------------------------------------
    // level two ECC calculate for low 8bit
    // ---------------------------------------------------------------------
    uc_ecc_p4ol = auc_ecc_l1[1] ^ auc_ecc_l1[2];
    uc_ecc_p2ol = auc_ecc_l1[0] ^ auc_ecc_l1[4];
    uc_ecc_p1ol = auc_ecc_l1[1] ^ auc_ecc_l1[5];
    uc_ecc_p1el = auc_ecc_l1[2] ^ auc_ecc_l1[6];
    uc_ecc_p2el = auc_ecc_l1[3] ^ auc_ecc_l1[7];
    uc_ecc_p4el = auc_ecc_l1[5] ^ auc_ecc_l1[6];

    // ---------------------------------------------------------------------
    // level two ECC calculate for high 8bit
    // ---------------------------------------------------------------------
    uc_ecc_p4oh = auc_ecc_h1[1] ^ auc_ecc_h1[2];
    uc_ecc_p2oh = auc_ecc_h1[0] ^ auc_ecc_h1[4];
    uc_ecc_p1oh = auc_ecc_h1[1] ^ auc_ecc_h1[5];
    uc_ecc_p1eh = auc_ecc_h1[2] ^ auc_ecc_h1[6];
    uc_ecc_p2eh = auc_ecc_h1[3] ^ auc_ecc_h1[7];
    uc_ecc_p4eh = auc_ecc_h1[5] ^ auc_ecc_h1[6];

    // ---------------------------------------------------------------------
    // level three ECC calculate
    // ---------------------------------------------------------------------
    uc_ecc_p1o = uc_ecc_p1ol ^ uc_ecc_p1oh;
    uc_ecc_p1e = uc_ecc_p1el ^ uc_ecc_p1eh;
    uc_ecc_p2o = uc_ecc_p2ol ^ uc_ecc_p2oh;
    uc_ecc_p2e = uc_ecc_p2el ^ uc_ecc_p2eh;
    uc_ecc_p4o = uc_ecc_p4ol ^ uc_ecc_p4oh;
    uc_ecc_p4e = uc_ecc_p4el ^ uc_ecc_p4eh;
    uc_ecc_p8o = uc_ecc_p2ol ^ uc_ecc_p2el;
    uc_ecc_p8e = uc_ecc_p2oh ^ uc_ecc_p2eh;

    // ---------------------------------------------------------------------
    // line ECC calculate
    // ---------------------------------------------------------------------
    uc_ecc_pr  = uc_ecc_p8o  ^ uc_ecc_p8e;

    // ---------------------------------------------------------------------
    // generate all row and column ecc result for one read/write cylce nxt_ecc_reg[23:0] = 24'h0;
    // ---------------------------------------------------------------------
    uacnxt_ecc_reg[0] = uc_ecc_p1o;
    uacnxt_ecc_reg[1] = uc_ecc_p1e;
    uacnxt_ecc_reg[2] = uc_ecc_p2o;
    uacnxt_ecc_reg[3] = uc_ecc_p2e;
    uacnxt_ecc_reg[4] = uc_ecc_p4o;
    uacnxt_ecc_reg[5] = uc_ecc_p4e;

    uacnxt_ecc_reg[6] = (~auc_addr_in[0]) & uc_ecc_pr;
    uacnxt_ecc_reg[7] =   auc_addr_in[0]  & uc_ecc_pr;

    uacnxt_ecc_reg[8]  = (~auc_addr_in[1]) & uc_ecc_pr;
    uacnxt_ecc_reg[9]  =   auc_addr_in[1]  & uc_ecc_pr;
    uacnxt_ecc_reg[10] = (~auc_addr_in[2]) & uc_ecc_pr;
    uacnxt_ecc_reg[11] =   auc_addr_in[2]  & uc_ecc_pr;
    uacnxt_ecc_reg[12] = (~auc_addr_in[3]) & uc_ecc_pr;
    uacnxt_ecc_reg[13] =   auc_addr_in[3]  & uc_ecc_pr;
    uacnxt_ecc_reg[14] = (~auc_addr_in[4]) & uc_ecc_pr;
    uacnxt_ecc_reg[15] =   auc_addr_in[4]  & uc_ecc_pr;
    uacnxt_ecc_reg[16] = (~auc_addr_in[5]) & uc_ecc_pr;
    uacnxt_ecc_reg[17] =   auc_addr_in[5]  & uc_ecc_pr;
    uacnxt_ecc_reg[18] = (~auc_addr_in[6]) & uc_ecc_pr;
    uacnxt_ecc_reg[19] =   auc_addr_in[6]  & uc_ecc_pr;
    uacnxt_ecc_reg[20] = (~auc_addr_in[7]) & uc_ecc_pr;
    uacnxt_ecc_reg[21] =   auc_addr_in[7]  & uc_ecc_pr;
    uacnxt_ecc_reg[22] = (~auc_addr_in[8]) & uc_ecc_pr;
    uacnxt_ecc_reg[23] =   auc_addr_in[8]  & uc_ecc_pr;

    for (i = 0; i < 24; i++)
    {
        puc_enc_data[i] = puc_enc_data_last[i] ^ uacnxt_ecc_reg[i];
    }
    return;
}

static tri_void hi_tools_ecc_1bit_gen(tri_uchar8 *puc_data, tri_uint32 ui_len, tri_uchar8 *puc_ecc_code)
{
    tri_uint32 i = 0;
    tri_uchar8 auc_enc_data_last[24] = {0x1};
    tri_uchar8 auc_enc_data[24] ;

    memset(auc_enc_data_last, 0x1, 24);

    for (i = 0; i < ui_len; i++)
    {
        hi_tools_ecc_1bit_make(i, puc_data[i], auc_enc_data, auc_enc_data_last);
        memcpy(auc_enc_data_last, auc_enc_data, 24);
    }

    if (ui_len == 16)
    {
        auc_enc_data[14] = 0x1;
        auc_enc_data[15] = 0x1;
    }

    if (ui_len >= 256)
    {
        for (i = 0; i < 3; i++)
        {
            puc_ecc_code[2 - i] = auc_enc_data[i*8]  + (auc_enc_data[i*8 + 1] << 1) + (auc_enc_data[i*8 + 2] << 2)
                + (auc_enc_data[i*8 + 3] << 3) + (auc_enc_data[i*8 + 4] << 4) + (auc_enc_data[i*8 + 5] << 5)
                + (auc_enc_data[i*8 + 6] << 6) + (auc_enc_data[i*8 + 7] << 7);
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            puc_ecc_code[1 - i] = auc_enc_data[i*8]  + (auc_enc_data[i*8 + 1] << 1) + (auc_enc_data[i*8 + 2] << 2)
                + (auc_enc_data[i*8 + 3] << 3) + (auc_enc_data[i*8 + 4] << 4) + (auc_enc_data[i*8 + 5] << 5)
                + (auc_enc_data[i*8 + 6] << 6) + (auc_enc_data[i*8 + 7] << 7);
        }
    }
}

static tri_void hi_tools_ecc_inttolfsr(tri_char8 *pc_lfsr, tri_int32 i_value)
{
    tri_int32 i;

    for(i=0; i <= g_i_lfsr_len; i++)
    {
    if( i_value & (1 << i))
    {
        pc_lfsr[i] = 1;
    }
    else
    {
        pc_lfsr[i] = 0;
    }
  }
}

static tri_void hi_tools_ecc_strtolfsr(tri_char8 *pc_lfsr, tri_char8 *i_value)
{
    tri_uint32 i;
    tri_char8 c;

    size_t len = strlen(i_value);

    for(i = 0; i < len; i++)
    {
        c = *(i_value + len - 1 - i);
        if(c == '1')
        {
            pc_lfsr[i] = 1;
        }
        else
        {
            pc_lfsr[i] = 0;
        }
    }
}

static tri_void hi_tools_ecc_lfsr_init(tri_int32 i_len, tri_char8 *pc_poly, tri_int32 i_value)
{
    g_i_lfsr_len = i_len;

    memset(g_ac_lfsr_poly, 0x00, TRI_MAX_LFSR_BITS);
    memset(g_ac_lfsr_value, 0x00, TRI_MAX_LFSR_BITS);

    hi_tools_ecc_strtolfsr(g_ac_lfsr_poly, pc_poly);
    hi_tools_ecc_inttolfsr(g_ac_lfsr_value, i_value);
}

static tri_void hi_tools_ecc_parity_lfsr_shift(tri_int32 i_din)
{
    tri_char8 c_feedback;
    tri_int32 i;

    c_feedback = g_ac_lfsr_value[g_i_lfsr_len - 1] ^ i_din;

    for(i = g_i_lfsr_len - 1; i > 0; i--)
        g_ac_lfsr_value[i]=(c_feedback & g_ac_lfsr_poly[i]) ^ g_ac_lfsr_value[i-1];

    g_ac_lfsr_value[0] = (c_feedback & g_ac_lfsr_poly[0]);
}

static tri_void hi_tools_ecc_parity_get(tri_char8 *pc_parity)
{
    tri_int32 i;
    tri_uint32 ui_value;
    tri_int32 i_shift;

    i_shift = 0;
    ui_value = 0;
    for(i = g_i_lfsr_len - 1; i >= 0; i--)
    {
        ui_value |= g_ac_lfsr_value[i] << i_shift;
        i_shift++;
        if(i_shift == 8)
        {
            *pc_parity = ui_value;
            pc_parity++;
            i_shift = 0;
            ui_value = 0;
        }
    }
}

static tri_int32 hi_tools_ecc_parity_gen(tri_uchar8 *puc_data, tri_uint32 ui_bits,tri_uint32 ui_ecc_level,tri_uchar8 *puc_ecc_code)
{
    tri_uint32 i;
    tri_uchar8 c;

    switch(ui_ecc_level)
    {
        case 8:
            hi_tools_ecc_lfsr_init(14*8, "b1111111001111011100101111111111001010011100001000011110001110110010110011110001001110011110011010101110000101101", 0);
            break;
        case 16:
            hi_tools_ecc_lfsr_init(14*16, "b11001100001001000000110001110000010010101010001101001001000101001100001010100010100100010010000001011001010011110111111111010111111000111100001111010101100110000100010011101001111011011000100110101010100000110111011011001111", 0);
            break;
        case 24:
            hi_tools_ecc_lfsr_init(14*24, "b100011101001010011100000001001001000110110010000100111010010101101000101001001010111001011010001111011011101100111010000100110001111111001110011000011101000111010001101001001101100001011010010001010001001001110100011101000000100100001011011110100001010101101101110000010110100100110010010100110100011010101101011110101000011000011101111", 0);
            break;
        case 40:
            hi_tools_ecc_lfsr_init(14*40, "b11000000011111111000100110110001101000001101110001011101100101100110000110011111001100101101000001001001011001110101010011110110110111101001110101001111100100111111010100100111111011110001010011101111101100001111110101010011100110010001010110101000001011001100110110010010010101010010100010000000001100000100011101111101111011100011111100110011100010100101100111101100010111111010001000010000101011111110001011101111110111111010111011010010010001001101111100110001010011011010010100000111011000101011011100100100101000000000001010011100111011110010110111000001", 0);
            break;
        default:
            return -1;
    }

    for(i = 0; i < ui_bits; i++)
    {
        c = *(puc_data + (i >> 3));
        c = (c >> (i & 0x7)) & 0x1;

        hi_tools_ecc_parity_lfsr_shift(c);
    }

    hi_tools_ecc_parity_get(puc_ecc_code);

    return 0;
}

static tri_void hi_tools_ecc_data_gen(tri_uchar8 *puc_data, tri_uint32 ui_len)
{
    tri_uint32 i;

    for(i = 0; i < ui_len; i++)
    {
        puc_data[i] = ~puc_data[i];
    }
}

static tri_int32 hi_tools_ecc_4bit_gen(tri_uchar8 *puc_data, tri_uint32 ui_len, tri_uchar8 *ecc_code)
{
    tri_int32 i, i_ret;

    hi_tools_ecc_data_gen(puc_data, ui_len);
    i_ret = hi_tools_ecc_parity_gen(puc_data, ui_len*8, 8, ecc_code);

    for (i=0; i < 14; i++)
    {
        ecc_code[i] = ~ecc_code[i];
    }

    return i_ret;
}

static tri_int32 hi_tools_ecc_8bit_gen(tri_uchar8 *puc_data, tri_uint32 ui_len, tri_uchar8 *ecc_code)
{
    tri_int32 i, i_ret;

    hi_tools_ecc_data_gen(puc_data, ui_len);
    i_ret = hi_tools_ecc_parity_gen(puc_data, ui_len*8, 16, ecc_code);

    for (i=0; i < 28; i++)
    {
        ecc_code[i] = ~ecc_code[i];
    }

    return i_ret;
}

static tri_int32 hi_tools_ecc_24bit1k_gen(tri_uchar8 *puc_data, tri_uint32 ui_len, tri_uchar8 *ecc_code)
{
    tri_int32 i, i_ret;

    hi_tools_ecc_data_gen(puc_data, ui_len);
    i_ret = hi_tools_ecc_parity_gen(puc_data, ui_len*8, 24, ecc_code);

    for (i=0; i < 42; i++)
    {
        ecc_code[i] = ~ecc_code[i];
    }

    return i_ret;
}

static tri_int32 hi_tools_ecc_40bit1k_gen(tri_uchar8 *puc_data, tri_uint32 ui_len, tri_uchar8 *ecc_code)
{
    tri_int32 i, i_ret;

    hi_tools_ecc_data_gen(puc_data, ui_len);
    i_ret = hi_tools_ecc_parity_gen(puc_data, ui_len*8, 40, ecc_code);

    for (i=0; i < 70; i++)
    {
        ecc_code[i] = ~ecc_code[i];
    }

    return i_ret;
}

#if TRI_BIN_WITH_PAGE0
static tri_int32 hi_tools_ecc_page0_gen(tri_uchar8 *puc_page_buf, TRI_PAGE_SIZE_EN en_page_size, TRI_ECC_TYPE_EN en_ecc_type, tri_int32 i_oob_size)
{
    tri_int32  i_page_size = en_page_size;
    tri_uchar8 ecc_buf[42];
    tri_uchar8 auc_buf[TRI_MAX_PAGE_SIZE + TRI_MAX_OOB_SIZE];

    memcpy(auc_buf, puc_page_buf, i_page_size + i_oob_size);
    
    memset(ecc_buf, 0xFF, sizeof(ecc_buf));
    hi_tools_ecc_24bit1k_gen(auc_buf, 1024, ecc_buf);

    memcpy(puc_page_buf + 1024, ecc_buf, 42);

    return 0;
}
#endif

static tri_int32 hi_tools_ecc_page_gen(tri_uchar8 *puc_page_buf, TRI_PAGE_SIZE_EN en_page_size, TRI_ECC_TYPE_EN en_ecc_type, tri_int32 i_oob_size)
{
    tri_uint32 i;
    tri_int32  i_page_size = en_page_size;
    tri_uchar8 auc_buf[TRI_MAX_PAGE_SIZE + TRI_MAX_OOB_SIZE];
    
    memcpy(auc_buf, puc_page_buf, i_page_size + i_oob_size);

    if((en_ecc_type == TRI_ECC_1BIT_EN) || (en_ecc_type == TRI_ECC_4BIT_EN))
    {
        tri_uchar8 ecc_buf[14];

        if(en_page_size == TRI_PAGE_SIZE_2K_EN)
        {
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_4bit_gen(auc_buf, 1040, ecc_buf);
            
            memcpy(puc_page_buf + 1040, ecc_buf, 14);
            memcpy(puc_page_buf + 1040 + 14, auc_buf + 1040, 994);
            memcpy(puc_page_buf + 1040 + 14 + 994, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + 1040 + 14 + 994 + 2, auc_buf + 1040 + 994, 14);
            memcpy(puc_page_buf + 1040 + 14 + 994 + 2 + 14 + 14, auc_buf + i_page_size + 2, 30);
            
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_4bit_gen(auc_buf + 1040, 1040, ecc_buf);
            
            memcpy(puc_page_buf + 1040 + 14 + 994 + 2 + 14, ecc_buf, 14);
        }
        else if(en_page_size == TRI_PAGE_SIZE_4K_EN)
        {
            for (i=0; i < 3; i++)
            {
                memcpy(puc_page_buf + (1032 + 14)*i, auc_buf + 1032*i, 1032);
                memset(ecc_buf, 0xFF, sizeof(ecc_buf));
                hi_tools_ecc_4bit_gen(auc_buf + 1032*i, 1032, ecc_buf);
                memcpy(puc_page_buf + (1032 + 14)*i + 1032, ecc_buf, 14);
            }

            memcpy(puc_page_buf + (1032 + 14)*3, auc_buf + 1032*3, 958);
            memcpy(puc_page_buf + (1032 + 14)*3 + 958, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + (1032 + 14)*3 + 958 + 2, auc_buf + 1032*3 + 958, 42);
            memcpy(puc_page_buf + (1032 + 14)*3 + 958 + 2 + 42 + 14, auc_buf + i_page_size + 2, 30);
            
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_4bit_gen(auc_buf + 1032*3, 1032, ecc_buf);
            
            memcpy(puc_page_buf + (1032 + 14)*3 + 958 + 2 + 42, ecc_buf, 14);
        }
        else
        {
            printf("mod: ecc [%d] + pagesize [%d] not support!\n",en_ecc_type, en_page_size);
            return -1;
        }

    }
    /* 对于8bit ecc NANDC认的OOB size有两种选择按寄存器默认值设置，否则bootrom引导不了hiboot启动 */
    else if(en_ecc_type == TRI_ECC_8BIT_EN)
    {
        tri_uchar8 ecc_buf[28];

        if(en_page_size == TRI_PAGE_SIZE_2K_EN)
        {
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_8bit_gen(auc_buf, 1028, ecc_buf);
            
            memcpy(puc_page_buf + 1028, ecc_buf, 28);

            memcpy(puc_page_buf + 1028 + 28, auc_buf + 1028, 992);
            memcpy(puc_page_buf + 1028 + 28 + 992, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + 1028 + 28 + 992 + 2, auc_buf + 1028 + 992, 28);
            memcpy(puc_page_buf + 1028 + 28 + 992 + 2 + 28 + 28, auc_buf + i_page_size + 2, 6);

            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_8bit_gen(auc_buf + 1028, 1028, ecc_buf);
            
            memcpy(puc_page_buf + 1028 + 28 + 992 + 2 + 28, ecc_buf, 28);
        }
        else if(en_page_size == TRI_PAGE_SIZE_4K_EN)
        {
            for (i=0; i < 3; i++)
            {
                memcpy(puc_page_buf + (1028 + 28)*i, auc_buf + 1028*i, 1028);
                memset(ecc_buf, 0xFF, sizeof(ecc_buf));
                hi_tools_ecc_8bit_gen(auc_buf + 1028*i, 1028, ecc_buf);
                memcpy(puc_page_buf + (1028 + 28)*i + 1028, ecc_buf, 28);
            }

            memcpy(puc_page_buf + (1028 + 28)*3, auc_buf + 1028*3, 928);
            memcpy(puc_page_buf + (1028 + 28)*3 + 928, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + (1028 + 28)*3 + 928 + 2, auc_buf + 1028*3 + 928, 84);
            memcpy(puc_page_buf + (1028 + 28)*3 + 928 + 2 + 84 + 28, auc_buf + i_page_size + 2, 14);
            
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_8bit_gen(auc_buf + 1028*3, 1028, ecc_buf);
            
            memcpy(puc_page_buf + (1028 + 28)*3 + 928 + 2 + 84, ecc_buf, 28);
        }
        else
        {
            printf("mod: ecc [%d] + pagesize [%d] not support!\n",en_ecc_type, en_page_size);
            return -1;
        }
    }
    else if(en_ecc_type == TRI_ECC_24BIT_EN)
    {
        tri_uchar8 ecc_buf[42];

        if(en_page_size == TRI_PAGE_SIZE_2K_EN)
        {
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_24bit1k_gen(auc_buf, 1040, ecc_buf);
            memcpy(puc_page_buf + 1040, ecc_buf, 42);

            memcpy(puc_page_buf + 1040 + 42, auc_buf + 1040, 966);
            memcpy(puc_page_buf + 1040 + 42 + 966, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + 1040 + 42 + 966 + 2, auc_buf + 1040 + 966, 42);
            memcpy(puc_page_buf + 1040 + 42 + 966 + 2 + 42 + 42, auc_buf + i_page_size + 2, 30);
            
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_24bit1k_gen(auc_buf + 1040, 1040, ecc_buf);
            
            memcpy(puc_page_buf + 1040 + 42 + 966 + 2 + 42, ecc_buf, 42);
        }
        else if(en_page_size == TRI_PAGE_SIZE_4K_EN)
        {
            for (i=0; i < 3; i++)
            {
                memcpy(puc_page_buf + (1032 + 42)*i, auc_buf + 1032*i, 1032);
                memset(ecc_buf, 0xFF, sizeof(ecc_buf));
                hi_tools_ecc_24bit1k_gen(auc_buf + 1032*i, 1032, ecc_buf);
                memcpy(puc_page_buf + (1032 + 42)*i + 1032, ecc_buf, 42);
            }

            memcpy(puc_page_buf + (1032 + 42)*3, auc_buf + 1032*3, 874);
            memcpy(puc_page_buf + (1032 + 42)*3 + 874, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + (1032 + 42)*3 + 874 + 2, auc_buf + 1032*3 + 874, 126);
            memcpy(puc_page_buf + (1032 + 42)*3 + 874 + 2 + 126 + 42, auc_buf + i_page_size + 2, 30);
            
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_24bit1k_gen(auc_buf + 1032*3, 1032, ecc_buf);
            
            memcpy(puc_page_buf + (1032 + 42)*3 + 874 + 2 + 126, ecc_buf, 42);
        }
        else if(en_page_size == TRI_PAGE_SIZE_8K_EN)
        {
            for (i=0; i < 7; i++)
            {
                memcpy(puc_page_buf + (1028 + 42)*i, auc_buf + 1028*i, 1028);
                memset(ecc_buf, 0xFF, sizeof(ecc_buf));
                hi_tools_ecc_24bit1k_gen(auc_buf + 1028*i, 1028, ecc_buf);
                memcpy(puc_page_buf + (1028 + 42)*i + 1028, ecc_buf, 42);
            }

            memcpy(puc_page_buf + (1028 + 42)*7, auc_buf + 1028*7, 702);
            memcpy(puc_page_buf + (1028 + 42)*7 + 702, auc_buf + i_page_size, 2);
            memcpy(puc_page_buf + (1028 + 42)*7 + 702 + 2, auc_buf + 1028*7 + 702, 294);
            memcpy(puc_page_buf + (1028 + 42)*7 + 702 + 2 + 294 + 42, auc_buf + i_page_size + 2, 30);
            
            memset(ecc_buf, 0xFF, sizeof(ecc_buf));
            hi_tools_ecc_24bit1k_gen(auc_buf + 1028*7, 1028, ecc_buf);
            
            memcpy(puc_page_buf + (1028 + 42)*7 + 702 + 2 + 294, ecc_buf, 42);
        }
        else
        {
            printf("mod: ecc [%d] + pagesize [%d] not support!\n",en_ecc_type, en_page_size);
            return -1;
        }

    }
    else
    {
        printf("invalid ecc mod, only support 1 4 24 40bit mode\n");
        return -1;
    }

    return 0;
}

static tri_void hi_tools_ecc_version_print(tri_void)
{
    printf("tools version:\t%s\n",TRI_ADDECC_VERSION);

    exit(0);
}

static tri_void hi_tools_ecc_usage(FILE* pf_stream, tri_int32 i_exit_code)
{
    fprintf (pf_stream,"Usage: options [-h -v -i -b -p -o]\n"
                    " -h --help\tdisplay help info.\n"
                    " -v --version\tdisplay tools version.\n"
                    " -i --input\tinput filename.\n"
                    " -o --output\toutput filename.\n"
                    " -b --eccbit\tnandflash ecc bit mod.\n"
                    " -s --spare\tnandflash real oob size.\n"
                    " -p --page\tnandflasn page size.\n");
    exit(i_exit_code);
}

tri_int32 main(tri_int32 argc, tri_char8 **argv)
{
    FILE       *pf_in      = NULL;
    FILE       *pf_out     = NULL;
    FILE       *pf_chenksum= NULL;
    tri_uint32  i           = 0;
    tri_int32   i_loop      = 0;
    tri_int32   i_ret       = -1;
    tri_int32   i_next_opt  = -1;
    tri_int32   i_ecc_type  = -1;
    tri_int32   i_page_size = -1;
    tri_int32   i_oob_size  = -1;
    tri_char8   *pc_file_in = NULL;
    tri_char8   *pc_file_out= NULL;
    tri_uchar8  ac_checksum[TRI_MAX_CHECKSUM_LEN];
    tri_uchar8  ac_page_buf[TRI_MAX_PAGE_SIZE+TRI_MAX_OOB_SIZE];
    tri_ulong32 ul_checksum = 0;

    /* 参数处理 */
    while(1)
    {
        i_next_opt = getopt_long(argc, argv, g_pc_short_options, g_ast_long_options, NULL);

        if (-1 == i_next_opt)
        {
            break;
        }

        switch (i_next_opt)
        {
            case 'h':        /*-h or --help*/
                hi_tools_ecc_usage(stdout, 0);
                break;

            case 'v':        /*-v or --version*/
                hi_tools_ecc_version_print();
                break;

            case 'i':        /*-i or --input*/
                pc_file_in  = optarg;
                break;

            case 'o':        /*-o or --output*/
                pc_file_out = optarg;
                break;

            case 'b':        /*-b or --eccbit*/
                i_ecc_type  = atoi(optarg);
                break;

            case 'p':        /*-p or --pagesize*/
                i_page_size = atoi(optarg);
                break;

            case 's':        /*-s or --spare*/
                i_oob_size  = atoi(optarg);
                break;

            default:
                hi_tools_ecc_usage(stderr, 1);
                break;
        }
    }

    /* 参数合法性判断 */
    if((-1 == i_ecc_type) || (-1 == i_page_size) || (NULL == pc_file_in) || (NULL == pc_file_out) || (-1 == i_oob_size))
    {
        hi_tools_ecc_usage(stderr, 1);
    }
    else
    {
        printf("ecc_type:%d page_size:%d oob_size:%d\n", i_ecc_type, i_page_size, i_oob_size);
    }

    if((pf_in = fopen(pc_file_in, "rb")) == NULL)
    {
        printf("failed on open input file: %s\n", pc_file_in);
        exit(1);
    }

    if((pf_out = fopen(pc_file_out, "wb+")) == NULL)
    {
        printf("failed on open output file: %s\n", pc_file_out);
        fclose(pf_in);
        exit(1);
    }

    while(!feof(pf_in))
    {
        memset(ac_page_buf, 0xFF, TRI_MAX_PAGE_SIZE + TRI_MAX_OOB_SIZE);
        
        i_ret = fread( ac_page_buf, sizeof(tri_uchar8), i_page_size, pf_in);
        if (i_ret <= 0)
        {
            break;
        }

        if (ferror(pf_in))
        {
            perror( "file read error" );
            fclose(pf_in);
            fclose(pf_out);
            exit(1);
        }

#if TRI_BIN_WITH_PAGE0
        /* page0 of block 0 ecc type must be 24bit */
        if(0 == i_loop)
        {
            i_ret = hi_tools_ecc_page0_gen(ac_page_buf,i_page_size, 24, i_oob_size);
        }
        else
#endif
        {
            i_ret = hi_tools_ecc_page_gen(ac_page_buf,i_page_size, i_ecc_type, i_oob_size);
        }
        
        if(i_ret)
        {
            fclose(pf_in);
            fclose(pf_out);
            exit(1);
        }

        if ((0 == i_loop) || (1 == i_loop))
        {
            /* FLASH控制器要求，前两页的头32 Byte数据，需要按Bit翻转 且计算ECC之后，再翻转*/
            for (i = 0; i < 32; i++)
            {
                ac_page_buf[i] = ~ac_page_buf[i];
            }
        }

        fwrite(ac_page_buf, 1, i_page_size+i_oob_size, pf_out);
        ul_checksum += hi_tools_ecc_checksum8(ac_page_buf, i_page_size+i_oob_size);
        i_loop++;
    }

    fclose(pf_in);
    fclose(pf_out);

    if ((pf_chenksum = fopen("ECC_checksum.txt", "wb")) == NULL)
    {
        printf("failed on open output file: %s\n", "ECC_checksum.txt");
        exit(1);
    }

    snprintf(ac_checksum, TRI_MAX_CHECKSUM_LEN, "%x", (tri_uint32)ul_checksum);
    fputs(ac_checksum, pf_chenksum);
    fclose(pf_chenksum);

    exit(0);
}

