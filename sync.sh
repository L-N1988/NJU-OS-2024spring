#!/bin/bash

# Assign arguments to variables
source_folder="$HOME/os-workbench/"
destination_folder="./os-workbench/"

# Check if source folder exists
if [ ! -d "$source_folder" ]; then
    echo "Error: Source folder does not exist."
    exit 1
fi

# Create the destination folder if it does not exist
mkdir -p "$destination_folder"

# Copy all non-hidden files and folders from source to destination
# The command `shopt -s dotglob` would include hidden files, which we do not want
cp -r $source_folder/* $destination_folder/

echo "🙂️ Files copied successfully from '$source_folder' to '$destination_folder'"
