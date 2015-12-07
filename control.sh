#!/bin/bash

SERVER_FILE="led_server"
FIFO_FILE="/tmp/led_fifo"
STATE_FILE="/tmp/state_fifo"

echo "+=========================+"
echo "|   LED controller v1.0   |"
echo "+=========================+"
echo

# Check if FIFO created
if [ ! -e "$FIFO_FILE" ]; then
    echo "Server not started! Exit."
    exit 1
fi

# Check if FIFO writable
if [ ! -w "$FIFO_FILE" ]; then
    echo "FIFO not writable! Exit."
    exit 1
fi

# Check if state FIFO readable
if [ ! -r "$STATE_FILE" ]; then
    echo "STATE not readable! Exit."
    exit 1
fi

# FIFO is OK

# Opening file descriptors # 3 for writing
exec 3>"$FIFO_FILE"

# Opening file descriptors # 4 for reading
exec 4<"$STATE_FILE"

# Write menu
echo "Main Menu"
PS3="Pick an option: "
main_menu_options=("Set State" "Get State" "Set Color" "Get Color" "Set Rate" "Get Rate")
continue_work=true

while $continue_work; do
    select opt in "${main_menu_options[@]}" "Quit"; do

        case "$REPLY" in

        1 ) serv_cmd="set-led-state";;
        2 ) serv_cmd="get-led-state";;
        3 ) serv_cmd="set-led-color";;
        4 ) serv_cmd="get-led-color";;
        5 ) serv_cmd="set-led-rate";;
        6 ) serv_cmd="get-led-rate";;

        $(( ${#main_menu_options[@]}+1 )) ) echo "Goodbye!"; continue_work=false; break;;
        *) echo "Invalid option. Try another one."; break;;

        esac

        # Special cases
        serv_cmd_arg=""

        # Set LED state
        if [ "$serv_cmd" == "set-led-state" ]; then
            sub_menu_options=("On" "Off")
            select sub_opt in "${sub_menu_options[@]}"; do
              case "$REPLY" in
              1 ) serv_cmd_arg="on"; break;;
              2 ) serv_cmd_arg="off"; break;;
              *) echo "Invalid state. Try another one."; continue;;
              esac
            done
        fi

        # Set LED color
        if [ "$serv_cmd" == "set-led-color" ]; then
            sub_menu_options=("Red" "Green" "Blue")
            select sub_opt in "${sub_menu_options[@]}"; do
              case "$REPLY" in
              1 ) serv_cmd_arg="red"; break;;
              2 ) serv_cmd_arg="green"; break;;
              3 ) serv_cmd_arg="blue"; break;;
              *) echo "Invalid color. Try another one."; continue;;
              esac
            done
        fi

        # Set LED rate
        if [ "$serv_cmd" == "set-led-rate" ]; then
            echo "Enter rate [0..5] in Hz"
            read serv_cmd_arg
        fi

        # Write command to fifo
        echo "$serv_cmd" "$serv_cmd_arg" >&3

        # Read result
        read -a cmd_result <&4
        echo
        echo "------------------------------"
        if [ ${cmd_result[0]} == "FAILED" ]; then
            echo "Command failed"
        else
            case "$serv_cmd" in
            "get-led-state") echo "LED state is ${cmd_result[1]}";;
            "get-led-color") echo "LED color is ${cmd_result[1]}";;
            "get-led-rate") echo "LED rate is ${cmd_result[1]}";;
            *) echo "Command done";;
            esac
        fi
        echo "------------------------------"
        echo
        break

    done
done

# close fd # 3 and # 4
exec 3>&-
exec 4<&-

exit 0
