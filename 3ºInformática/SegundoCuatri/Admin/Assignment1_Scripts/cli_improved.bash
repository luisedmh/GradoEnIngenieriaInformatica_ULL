#!/usr/bin/env bash
#
# Extended CLI utility with quote commands
#

set -euo pipefail

SCRIPT=$(basename "$0")
VERSION="1.1.0"

#
# Usage information
#
function usage
{
    local txt=(
"Utility $SCRIPT for various commands."
"Usage: $SCRIPT [options] <command> [arguments]"
""
"Command:"
"  command1              Demo of command."
"  command2 [anything]   Demo of command using arguments."
"  calendar [events]     Print current calendar with(out) events."
"  quote-local           Print a daily quote using local command."
"  quote-online          Print a daily quote from online API."
""
"Options:"
"  --help, -h     Print help."
"  --version, -v  Print version."
    )

    printf "%s\n" "${txt[@]}"
}


function badUsage
{
    local message="$1"
    [[ -n $message ]] && printf "%s\n" "$message"
    echo "For help, run: $SCRIPT --help"
}

function version
{
    echo "$SCRIPT version $VERSION"
}

#
# Existing demo commands
#
function app-command1
{
    echo "This is output from command1."
}

function app-command2
{
    echo "This is output from command2."
    echo "Number of arguments: $#"
    echo "Arguments: $*"
}

function app-calendar
{
    local events="${1:-}"

    cal -3 || echo "You may need to install ncal."

    if [[ "$events" == "events" ]]; then
        echo
        calendar || echo "You may need to install calendar package."
    fi
}

#
# NEW COMMAND: Local Quote
#
function app-quote-local
{
    if ! command -v fortune >/dev/null 2>&1; then
        echo "fortune is not installed."
        echo "Install with: sudo apt install fortune-mod"
        exit 1
    fi

    echo "----------------------------------------"
    fortune
    echo "----------------------------------------"
}

#
# NEW COMMAND: Online Quote
#
function app-quote-online
{
    if ! command -v curl >/dev/null 2>&1; then
        echo "curl is not installed."
        exit 1
    fi

    if ! command -v jq >/dev/null 2>&1; then
        echo "jq is not installed."
        echo "Install with: sudo apt install jq"
        exit 1
    fi

    local response
    response=$(curl -s https://zenquotes.io/api/random)

    if [[ -z "$response" ]]; then
        echo "Failed to retrieve quote."
        exit 1
    fi

    local quote
    quote=$(echo "$response" | jq -r '.[0].q')

    local author
    author=$(echo "$response" | jq -r '.[0].a')

    echo "----------------------------------------"
    echo "\"$quote\""
    echo "   - $author"
    echo "----------------------------------------"
}

if [[ $# -eq 0 ]]; then
    usage
    exit 1
fi

#
# Process options and commands
#
while (( $# ))
do
    case "$1" in

        --help | -h)
            usage
            exit 0
        ;;

        --version | -v)
            version
            exit 0
        ;;

        command1 \
        | command2 \
        | calendar \
        | quote-local \
        | quote-online)
            command="$1"
            shift
            app-"$command" "$@"
            exit 0
        ;;

        *)
            badUsage "Command not recognized."
            exit 1
        ;;
    esac
done

badUsage
exit 1