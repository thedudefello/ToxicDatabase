#!/bin/bash

clear
echo
center_text() {
    local text="$1"
    local term_width=$(tput cols)
    local text_length=${#text}
    local padding=$(( (term_width - text_length) / 2 ))

    printf "%*s%s%*s\n" $padding "" "$text" $padding ""
}

# Centered text output
center_text "          88                                             "
center_text "          88                                             "
center_text "          88                                             "
center_text "          88                                             "
center_text "  ,adPPYb,88  ,adPPYba,   ,adPPYba,  88,dPYba,,adPYba,   "
center_text " a8\"    \`Y88 a8\"     \"8a a8\"     \"8a 88P'   \"88\"    \"8a  "
center_text " 8b       88 8b       d8 8b       d8 88      88      88  "
center_text " \"8a,   ,d88 \"8a,   ,a8\" \"8a,   ,a8\" 88      88      88  "
center_text "  \`\"8bbdP\"Y8  \`\"YbbdP\"'   \`\"YbbdP\"'  88      88      88  "
center_text "Terminal Doom Executor made by fdiskzlez"
echo

center_text "1. Run Doom"
center_text "2. Run Doom with PWAD"
center_text "3. Run Saved Game"
center_text "4. Exit"
echo

read -p "Select an option: " option

case $option in
    1)
        echo "Running Flatpak GZDoom..."
        sleep 1 
        flatpak run org.zdoom.GZDoom
        ;;
    2)
        read -p "Enter PWAD path: " pwad_path
        echo "Running Flatpak GZDoom with PWAD: $pwad_path..."
        sleep 1
        flatpak run org.zdoom.GZDoom -file "$pwad_path"
        ;;
    3)
        read -p "Enter saved game path: " save_path
        echo "Running Flatpak GZDoom with saved game: $save_path..."
        sleep 1
        flatpak run org.zdoom.GZDoom -load "$save_path"
        ;;
    4)
        echo "Exiting..."
        exit 0
        ;;
    *)
        echo "Invalid option. Exiting..."
        exit 1
        ;;
esac
