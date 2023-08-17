#!/bin/sh
###############################################################
# SPDX-License-Identifier: BSD-2-Clause-Patent
# SPDX-FileCopyrightText: 2019-2020 the prplMesh contributors (see AUTHORS.md)
# This code is subject to the terms of the BSD+Patent license.
# See LICENSE file for more details.
###############################################################

scriptdir="$(dirname "$(readlink -f "${0}")")"
PRPLMESH_DIR="$(cd "${scriptdir}/.." && pwd)"

# Explicitely ignore SIGPIPE to make sure the processes we start in
# the background do not stop in case stdout/stderr gets closed early
# (because the SSH connection calling the script is closed as soon as
# the utils script exits for example). Similarly, ignore SIGHUP to
# make sure the processes do not stop when the session leader
# terminates:
trap '' HUP PIPE

dbg() {
    [ "$VERBOSE" = "true" ] && echo "$@"
}

err() {
    printf '\033[1;31m%s\n\033[0m' "$*"
}

success() {
    printf '\033[1;32m%s\n\033[0m' "$*"
}

run() {
    dbg "$*"
    "$@" || exit $?
}

killall_program() {
    PROGRAM_NAME=$1
    TERM_SIG=${2:-TERM}
    TIMEOUT=10
    echo "terminating $PROGRAM_NAME ($TERM_SIG)"
    start-stop-daemon -K -s "$TERM_SIG" -x "$PRPLMESH_DIR/bin/$PROGRAM_NAME" > /dev/null 2>&1

    # If an explicit signal was provided, we don't do a SIGKILL
    if [ -n "$2" ]; then return; fi

    # `-R` option is not always available for `start-stop-daemon`, we need to imitate it
    for _ in $(seq 1 "$TIMEOUT"); do
        if ! pgrep "$PROGRAM_NAME" > /dev/null; then
           return
        fi
        sleep 1
    done

    echo "killing $PROGRAM_NAME (KILL)"
    start-stop-daemon -K -s "KILL" -x "$PRPLMESH_DIR/bin/$PROGRAM_NAME" > /dev/null 2>&1
}

platform_init() {
    echo "platform init..."
    [ -z "$DATA_IFACE" ] && err "DATA_IFACE not set, abort" && exit 1
    [ -z "$CONTROL_IFACE" ] && err "CONTROL_IFACE not set, abort" && exit 1
    base_mac=46:55:66:77
    bridge_ip=192.168.100.140
    control_ip=192.168.250.140

    ip link add br-lan address "${base_mac}:00:00" type bridge
    ip link add wlan0 address "${base_mac}:00:10" type dummy
    ip link add wlan2 address "${base_mac}:00:20" type dummy
    ip link set dev wlan0 up
    ip link set dev wlan2 up
    for iface in wlan0 wlan2 $DATA_IFACE
    do
        echo "add $iface to br-lan"
        nmcli d set "$iface" managed no
        ip link set dev "$iface" master br-lan
        ip addr flush "$iface"
    done
    ip addr add "$control_ip"/24 dev "$CONTROL_IFACE"
    ip addr add "$bridge_ip"/24 dev br-lan
    ip link set br-lan up
}

platform_deinit() {
    echo "platform deinit"
    [ -z "$DATA_IFACE" ] && err "DATA_IFACE not set, abort" && exit 1
    [ -z "$CONTROL_IFACE" ] && err "CONTROL_IFACE not set, abort" && exit 1
    for iface in wlan0 wlan2 $DATA_IFACE
    do
        echo "remove $iface from br-lan"
        ip link set dev "$iface" nomaster
        nmcli d set "$iface" managed yes
    done
    ip link del wlan0
    ip link del wlan2
    ip link del br-lan
}

prplmesh_platform_db_init() {
    management_mode=${1-Multi-AP-Controller-and-Agent}
    operating_mode=${2-Gateway}

    mkdir -p /tmp/beerocks

    # Put generated prplmesh_platform_db file to the temporary directory
    cp "${PRPLMESH_DIR}/share/prplmesh_platform_db" /tmp/beerocks/prplmesh_platform_db

    # Modify generated parameters to current
    sed -i "s/management_mode=.*/management_mode=${management_mode}/g" /tmp/beerocks/prplmesh_platform_db
    sed -i "s/operating_mode=.*/operating_mode=${operating_mode}/g" /tmp/beerocks/prplmesh_platform_db
}

prplmesh_framework_init() {
    # This is required for solveing issue which causing meesges not geeting to their destination.
    # For more information see: https://github.com/prplfoundation/prplMesh/pull/1029#issuecomment-608353274
    #ebtables -A FORWARD -d 01:80:c2:00:00:13 -j DROP || {
    #    printf "Failed to add the required ebtables rule.\n" >&2
    #    printf "Please make sure the 'ebtables' kernel module is loaded and try again.\n" >&2
    #    exit 1
    #}

    echo "prplmesh_framework_init - starting ieee1905_transport process..."
    "$PRPLMESH_DIR/bin/ieee1905_transport" &
}

prplmesh_framework_deinit() {
    echo "prplmesh_framework_deinit - killing ieee1905_transport process..."
    killall_program ieee1905_transport
    #ebtables -D FORWARD -d 01:80:c2:00:00:13 -j DROP
}

prplmesh_controller_start() {
    echo "prplmesh_controller_start - start beerocks_controller process..."
    "$PRPLMESH_DIR/bin/beerocks_controller" &
}

prplmesh_controller_stop() {
    echo "prplmesh_controller_stop - stopping beerocks_controller process..."
    killall_program beerocks_controller
}

prplmesh_agent_start() {
    echo "prplmesh_agent_start - start beerocks_agent process..."
    "$PRPLMESH_DIR/bin/beerocks_agent" &
}

prplmesh_agent_stop() {
    echo "prplmesh_agent_stop - stopping beerocks_agent process..."
    killall_program beerocks_agent
    killall_program beerocks_fronthaul
}

prplmesh_delete_logs() {
    echo "deleting logs"
    rm -rf /tmp/beerocks/logs

    # Relevant only for Linux environment
    rm -rf "/tmp/beerocks/logs"
}

prplmesh_watchdog() {
    # Store PIDs of the Controller and Agents
    CURR_PIDS="$(pgrep 'beerocks_(agent|controller)' | wc -l)"
    PREV_PIDS="$CURR_PIDS"

    # Make sure there's at least one PID to monitor
    if [ -z "$CURR_PIDS" ]; then
        echo "No controller or agent processes found."
        return
    fi

    # Monitor the number of running processes
    while [ "$CURR_PIDS" -ge "$PREV_PIDS" ]; do
        sleep 5
        CURR_PIDS="$(pgrep 'beerocks_(agent|controller)' | wc -l)"
        if [ "$CURR_PIDS" -gt "$PREV_PIDS" ]; then
            PREV_PIDS=$CURR_PIDS
        fi
    done
}

roll_logs_function()
{
    ROLL_PROGRESS_DIR="roll_in_progress.lock"

    # Switch into the beerocks logs folder
    cd /tmp/beerocks/logs || exit

    # Check if log roll already in progress
    if ! mkdir "$ROLL_PROGRESS_DIR"
    then
        echo "Roll already in progress... Exiting..."
        exit 0
    fi

    # Symlinks point to all log files that can be rotated
    links=$(for file in *; do readlink "$file" > /dev/null && echo "$file"; done)

    for link in $links; do
        # Keep the last 3 versions of the log file
        echo "$link" | sed -e 's/log$/*/' | xargs find . -name | sort -r | awk 'NR>3' | xargs rm -f
    done

    # Send USR1 signals to the beerocks processes to trigger log rolling
    killall_program beerocks_controller USR1
    killall_program beerocks_agent USR1
    killall_program beerocks_fronthaul USR1

    # Cleanup
    rm -r $ROLL_PROGRESS_DIR
}

start_function() {
    echo "$0: start"
    [ "$(id -u)" -ne 0 ] && echo "$0: warning - this commands needs root privileges. It might not work without them (are you root?)"

    # shellcheck disable=SC2050
    [ "NL80211" = "DUMMY" ] && [ "$PLATFORM_INIT" = "true" ] && platform_init
    prplmesh_framework_init
    case "$PRPLMESH_MODE" in
        CA | ca)
            prplmesh_platform_db_init "Multi-AP-Controller-and-Agent"
            prplmesh_controller_start
            prplmesh_agent_start
            ;;
        C | c)
            prplmesh_platform_db_init "Multi-AP-Controller"
            prplmesh_controller_start
            # Dummy agent configures transport layer
            prplmesh_agent_start
            ;;
        A | a)
            prplmesh_platform_db_init "Multi-AP-Agent" "WDS-Repeater"
            prplmesh_agent_start
            ;;
        * ) err "unsupported mode: $PRPLMESH_MODE"; usage; exit 1 ;;
    esac
}

stop_function() {
    echo "$0: stop"
    [ "$(id -u)" -ne 0 ] && echo "$0: warning - this commands needs root privileges. It might not work without them (are you root?)"

    # shellcheck disable=SC2050
    [ "NL80211" = "DUMMY" ] && [ "$PLATFORM_INIT" = "true" ] && platform_deinit
    prplmesh_agent_stop
    prplmesh_controller_stop
    prplmesh_framework_deinit
    [ "$DELETE_LOGS" = "true" ] && prplmesh_delete_logs
}

execute_beerocks_command() {
    dbg "Executing beerocks cli command: $*"
    if [ -e "$PRPLMESH_DIR/bin/beerocks_cli" ]; then
        output="$("${PRPLMESH_DIR}/bin/beerocks_cli" -c "$@")"
        return $?
    else
        err "BML CLI not found"
        output=""
        return 1
    fi
}

# Note: Apparently on some Linux version space is added to the process name.
# Therefore added "($|[[:blank:]])" to the end of the regex expression which means the end of the
# line ($) or blank character ([[:blank:]])
main_agent_operational() {
    pgrep -fx "$PRPLMESH_DIR/bin/beerocks_agent($|[[:blank:]])" > /dev/null 2>&1 || return 1
    grep -q ' --> OPERATIONAL' "$1/beerocks_backhaul.log"
}

radio_agent_operational() {
    grep -q "$2 FSM: .* --> CONFIGURED" "$1/beerocks_agent.log"
}

report() {
    msg="$1"; shift
    if "$@"; then
        success "OK $msg"
    else
        err "FAIL $msg"
        error=1
    fi
}

status_function() {
    echo "$0: status"

    pgrep -l beerocks
    pgrep -l ieee1905_transport

    # Use the given argument as birdge mac if it filled with something, otherwise get the bridge mac
    # of the local platform.
    ARGUMENT_LEN=${#1}
    if [ "$ARGUMENT_LEN" -ne "0" ]; then
        BRIDGE_MAC=$1
    else
        BRIDGE_MAC="$(ip link show dev br-lan | awk '/^ *link\/ether / {print $2}')"
    fi

    bml_cmd="bml_get_device_operational_radios $BRIDGE_MAC"

    if  pgrep -l beerocks_cont ; then
        echo "executing operational test using bml"
        if execute_beerocks_command "$bml_cmd" ; then
            OUTPUT=$output
            # Expecting
            # > OK Main radio agent operational
            # > OK wlan0 radio agent operational
            # > OK wlan2 radio agent operational
            OK_Count=$(echo "$OUTPUT" | grep -c -e "OK.*operational")
            if [ "$OK_Count" -eq 3 ]; then
                success "operational test success!"
                OUTPUT=$(echo "$OUTPUT" | grep -E '(FAIL|OK).*?operational')
                success "$OUTPUT"
                exit 0
            else
                err "operational test failed!"
                OUTPUT=$(echo "$OUTPUT" | grep -E '(FAIL| OK).*?operational' | sed -e "s/ OK/OK/")
                echo "$OUTPUT"
                if [ "$(echo "$OUTPUT" | grep -c -e " wlan0 .*operational")" -eq 0 ]; then
                    err "FAIL wlan0 radio agent operational"
                fi
                if [ "$(echo "$OUTPUT" | grep -c -e " wlan2 .*operational")" -eq 0 ]; then
                    err "FAIL wlan2 radio agent operational"
                fi
                exit 1
            fi
        else
            err "Beerocks command failed to execute!"
            exit 1
        fi
    else
        echo "executing operational test using grep on log files"
        # check for operational status
        LOGS_PATH=/tmp/beerocks/logs

        error=0
        report "Main agent operational" main_agent_operational $LOGS_PATH
        # For each existing slave log file, check if they are OPERATIONAL:
        main_agent_log="$LOGS_PATH/beerocks_agent.log"
        # skip files that aren't symlinks (and skip the literal glob if there is no matching file):
        [ -L "$main_agent_log" ] || return

        radios=$(grep 'fronthaul_iface=' "$main_agent_log"  | cut -d "=" -f2)
        for radio in $radios ; do
            report "$radio radio agent operational" radio_agent_operational "$LOGS_PATH" "$radio"
        done

        exit $error
    fi
}

usage() {
    echo "usage: $(basename "$0") {start|stop|restart|status|roll_logs} [-hvpmdCD]"
}

main() {
    if ! OPTS=$(getopt -o 'hvm:pdC:D:'  -n 'parse-options' \
        --long 'verbose,help,mode:,platform-init,delete-logs,iface-ctrl,iface-data' \
        -- "$@") ; then
            err "Failed parsing options." >&2
            usage
            exit 1
    fi

    eval set -- "$OPTS"

    while true; do
        case "$1" in
            -v | --verbose)       VERBOSE=true; shift ;;
            -h | --help)          usage; exit 0; shift ;;
            -m | --mode)          PRPLMESH_MODE="$2"; shift; shift ;;
            -p | --platform-init) PLATFORM_INIT=true; shift ;;
            -d | --delete-logs)   DELETE_LOGS=true; shift ;;
            -C | --iface-ctrl)    CONTROL_IFACE="$2"; shift; shift ;;
            -D | --iface-data)    DATA_IFACE="$2"; shift; shift ;;
            -- ) shift; break ;;
            * ) err "unsupported argument $1"; usage; exit 1 ;;
        esac
    done

    dbg VERBOSE=$VERBOSE
    dbg PLATFORM_INIT=$PLATFORM_INIT
    dbg DELETE_LOGS=$DELETE_LOGS

    case $1 in
        "start")
            start_function
            ;;
        "start_wait")
            start_function
            prplmesh_watchdog
            stop_function
            ;;
        "stop")
            stop_function
            ;;
        "restart")
            stop_function
            start_function
            ;;
        "status")
            status_function "$2"
            ;;
        "roll_logs")
            roll_logs_function
	    return $?
            ;;
        *)
            err "unsupported argument \"$1\""; usage; exit 1 ;;
    esac

    # Give write permissions (linux only)
    # shellcheck disable=SC2050
    if [ "openwrt" = "linux" ]; then
        chmod -R +o+w "/tmp/beerocks" || true
    fi
}

VERBOSE=false
PLATFORM_INIT=false
DELETE_LOGS=false
CONTROL_IFACE=
DATA_IFACE=
PRPLMESH_MODE="CA" # CA = Controller & Agent, A = Agent only, C = Controller only

main "$@"
