#!/usr/bin/env bash
set -euo pipefail

main() {
    validate_args "$@"
    analyse_path "$1"
}

validate_args() {
    if [[ $# -ne 1 ]]; then     # Check the amount of arguments
        echo "Usage: $0 <path>"
        exit 2
    fi

    if [[ ! -d "$1" ]]; then    # Check if the argument given is the path of a folder
        echo "Error: Path '$1' does not exist or is not a directory."
        exit 1
    fi
}

analyse_path() {
    local path="$1"

    echo "Scanning directory: $path"
    echo "----------------------------------------"

    # Total number of files
    local total_files
    total_files=$(find "$path" -type f | wc -l) # -type f ditinguishes only files and wc -l says the amount, find is recursive by itself

    # Total size in bytes
    local total_size
    total_size=$(find "$path" -type f -exec stat -c%s {} + | awk 'BEGIN {sum = 0} {sum += $1} END {print sum}')
    # -exec stat to get the stats of the files, -c%s for the format of stat, only size, then {} + to pipe it to the awk
    # Declare sum in the begining, sum the first column and print it

    echo "Total files scanned: $total_files"
    echo "Total size (bytes): $total_size"
    echo

    echo "Top 5 largest files:"
    echo "----------------------------------------"

    # Get top 5 largest files
    find "$path" -type f -exec stat -c "%s %n" {} + \
        | sort -nr \
        | head -5 \
        | while read -r size file; do

            file_type=$(file -b "$file")

            echo "File: $file"
            echo "Size (bytes): $size"
            echo "Type: $file_type"
            echo "----------------------------------------"
        done
}
    # Same find as before, sort numeric reverse, first 5, while; get file type and print everything

main "$@"

