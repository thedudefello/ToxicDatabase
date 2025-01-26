#!/bin/bash

clear

center_text() {
    local term_width
    term_width=$(tput cols)
    local padding
    padding=$(( (term_width - ${#1}) / 2 ))
    printf "%*s%s\n" $padding "" "$1"
}

center_text "  _           _        _ _           "
center_text " (_)         | |      | | |          "
center_text "  _ _ __  ___| |_ __ _| | | ___ _ __ "
center_text " | | '_ \/ __| __/ _\` | | |/ _ \ '__|"
center_text " | | | | \__ \ || (_| | | |  __/ |   "
center_text " |_|_| |_|___/\__\__,_|_|_|\___|_|   "
echo ""
center_text "made by fdiskzlez"
echo ""

center_text "You are about to run GZDoom. Are you sure you want to run it? (y/n)"
echo ""

read -p "$(tput cup $(( $(tput lines) / 2 )) $(( ( $(tput cols) - 15 ) / 2 )) )Your choice: " choice

if [[ "$choice" == "y" || "$choice" == "Y" ]]; then
    center_text "Checking if Flatpak is installed..."

    if command -v flatpak > /dev/null 2>&1; then
        center_text "Flatpak is installed. Checking if GZDoom is installed..."
    else
        center_text "Flatpak is not installed. Installing Flatpak..."

        if [ -f /etc/debian_version ]; then
            sudo apt-get update
            sudo apt-get install -y flatpak
        elif [ -f /etc/redhat-release ]; then
            sudo dnf install -y flatpak
        elif [ -f /etc/arch-release ]; then
            sudo pacman -Syu --noconfirm flatpak
        else
            center_text "Unsupported distribution. Please install Flatpak manually."
            exit 1
        fi

        if [[ $? -ne 0 ]]; then
            center_text "Failed to install Flatpak. Exiting..."
            exit 1
        fi

        center_text "Flatpak installed successfully. Proceeding..."
    fi

    sleep 1

    center_text "Checking if GZDoom is installed..."

    if flatpak info org.zdoom.GZDoom > /dev/null 2>&1; then
        center_text "GZDoom is installed. Proceeding..."
        sleep 1
    else
        center_text "GZDoom is not installed. Installing via Flatpak..."
        sleep 1

        flatpak install -y flathub org.zdoom.GZDoom

        if [[ $? -ne 0 ]]; then
            center_text "Failed to install GZDoom. Exiting..."
            exit 1
        fi
        
        center_text "GZDoom installed successfully. Proceeding..."
    fi
    
    clear 

    center_text "Running Doom Script"

    center_text "Executing additional script..."
    bash doom.sh 

else
    center_text "Operation canceled."
    exit 0
fi
