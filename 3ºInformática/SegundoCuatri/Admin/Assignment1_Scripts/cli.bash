#!/usr/bin/env bash
#
# Extended CLI utility with quote commands
#

set -euo pipefail  # Added: exits on error, undefined vars, and pipe failures

SCRIPT=$(basename "$0")
VERSION="1.1.0"  # Incremented version number

#
# Usage information
#
function usage {
    local txt=(
        "Utility $SCRIPT for various commands."
        "Usage: $SCRIPT [options] <command> [arguments]"
        ""
        "Commands:"
        "  command1              Demo of command."
        "  command2 [anything]   Demo of command using arguments."
        "  calendar [events]     Print current calendar with(out) events."
        "  quote-local           Print a daily quote using local command."  # Added new command
        "  quote-online          Print a daily quote from online API."      # Added new command
        ""
        "Options:"
        "  --help, -h     Print help."
        "  --version, -v  Print version."
    )
    printf "%s\n" "${txt[@]}"
}

function badUsage {
    local message="$1"
    [[ -n $message ]] && echo "$message"  # Shows error message if provided
    echo "For help, run: $SCRIPT --help"
}

function version {
    echo "$SCRIPT version $VERSION"
}

function app-command1 {
    echo "This is output from command1."
}

function app-command2 {
    echo "This is output from command2."
    echo "Number of arguments: $#"
    echo "Arguments: $*"
}

function app-calendar {
    local events="${1:-}"  # Parameter expansion: defaults to empty if no argument

    cal -3 || echo "You may need to install ncal."  # Uses OR operator for error handling

    if [[ "$events" == "events" ]]; then  # Double brackets for safer string comparison
        echo
        calendar || echo "You may need to install calendar package."
    fi
}

# New function: displays a random quote using the local 'fortune' command
function app-quote-local {
    # command -v checks if a program exists in PATH
    if ! command -v fortune >/dev/null 2>&1; then  # Redirects stdout/stderr to null
        echo "fortune is not installed."
        echo "Install with: sudo apt install fortune-mod"
        exit 1
    fi

    echo "----------------------------------------"
    fortune
    echo "----------------------------------------"
}

# New function: fetches a random quote from an online API
function app-quote-online {
    # Check for required dependencies
    if ! command -v curl >/dev/null 2>&1; then
        echo "curl is not installed."
        exit 1
    fi

    if ! command -v jq >/dev/null 2>&1; then  # jq is a JSON processor
        echo "jq is not installed."
        echo "Install with: sudo apt install jq"
        exit 1
    fi

    local response
    response=$(curl -s https://zenquotes.io/api/random)  # -s flag makes curl silent

    if [[ -z "$response" ]]; then  # Check if response is empty
        echo "Failed to retrieve quote."
        exit 1
    fi

    # jq -r outputs raw strings without JSON quotes
    local quote
    quote=$(echo "$response" | jq -r '.[0].q')  # Extracts quote text from JSON array

    local author
    author=$(echo "$response" | jq -r '.[0].a')  # Extracts author from JSON array

    echo "----------------------------------------"
    echo "\"$quote\""  # Escapes double quotes around the quote
    echo "   - $author"
    echo "----------------------------------------"
}

#
# Main logic
#
if [[ $# -eq 0 ]]; then  # Shows usage if no arguments provided
    usage
    exit 1
fi

while (( $# )); do
    case "$1" in
        --help|-h)
            usage
            exit 0
            ;;
        --version|-v)
            version
            exit 0
            ;;
        command1|command2|calendar|quote-local|quote-online)  # Added new commands to case
            command="$1"
            shift
            app-"$command" "$@"  # Passes all remaining arguments with "$@"
            exit 0
            ;;
        *)
            badUsage "Command not recognized."
            exit 1
            ;;
    esac
done