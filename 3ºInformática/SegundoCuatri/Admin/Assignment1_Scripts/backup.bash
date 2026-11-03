#!/usr/bin/env bash
set -euo pipefail	# Check for failed commands, non defined variables and fails in pipes

main() {
    validate_args "$@"
    create_backup "$1"
}

validate_args() {
    if [[ $# -ne 1 ]]; then	# Check for exactly 1 argument as entrance
        echo "Usage: $0 <directory>"
        exit 2
    fi

    if [[ ! -d "$1" ]]; then	# Check if the argument is a directory
        echo "Error: Directory '$1' does not exist."
        exit 1
    fi
}

create_backup() {
    local dir="$1"
    local date_str
    date_str=$(date +%Y-%m-%d)

    #local dir_name=$(basename "$dir")   # get the name of the directory (extra option)
    #local timestapm=$(date +%Y-%m-%d_%H-%M-%S)  # get the timestamp (extra option)


    mkdir -p tmp	# -p solves the problems if tmp already exists

    local backup_file="tmp/backup_${date_str}.tar.gz"
    # local backup_file="tmp/backup_${dir_name}_${date_str}.tar.gz"
    # local backup_file="tmp/backup_${timestamp}.tar.gz"
    # local backup_file="tmp/backup_${dir_name}_${timestamp}.tar.gz"

    if [[ -f "$backup_file" ]]; then	# Check for backup files with the same name, don't overwrite
        echo "Error: Backup file already exists."
        exit 1
    fi

    local start_time	# Get time at the begining to measure how long took to execute the script
    start_time=$(date +%s)

    tar -czf "$backup_file" "$dir"	# Create the backup file

    local end_time
    end_time=$(date +%s)	# Get the time at the end

    echo "Backup created: $backup_file"
    echo "Execution time: $(( end_time - start_time )) seconds"
}

main "$@"	# Call main with all the arguments, actually just 1

