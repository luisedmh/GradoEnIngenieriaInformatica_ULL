#!/usr/bin/env bash
set -euo pipefail

main() {
    validate_args "$@"
    analyse_url "$1"
}

validate_args() {   # Check the args, in this case, just the amount
    if [[ $# -ne 1 ]]; then
        echo "Usage: $0 <url>"
        exit 2
    fi
}

analyse_url() {
    local url="$1"
    local output_file="tmp/downloaded_file" # Possible modification: Relate the file name with the url

    mkdir -p "tmp"  # -p in case the folder already exists

    echo "Downloading resource from: $url"

    if ! curl -L --fail --silent --show-error "$url" -o "$output_file"; then    # Explained better in the document, basically getting the file from the url
        echo "Error: Failed to download resource."
        exit 1
    fi

    echo "Download completed."
    echo "----------------------------------------"

    local file_type
    file_type=$(file -b "$output_file") # Get type

    local mime_type
    mime_type=$(file -b --mime-type "$output_file") # Get MIME type

    local size
    size=$(stat -c%s "$output_file")    # Size with stat and format -c

    echo "File type: $file_type"
    echo "MIME type: $mime_type"
    echo "File size (bytes): $size"
    echo "----------------------------------------"

    if [[ "$mime_type" == text/* ]]; then   # Conditional to choose which function to call
        analyse_text_file "$output_file"
    else
        analyse_binary_file "$output_file"
    fi

    echo "Opening file in browser..."
    xdg-open "$output_file" >/dev/null 2>/dev/null  # Open the file on the default app with xdg-open and sends to /dev/null both outputs
}

analyse_text_file() {
    local file="$1"

    echo "Detected as text file."
    echo "----------------------------------------"

    local lines
    lines=$(wc -l < "$file")    # Amount of lines -l

    local words
    words=$(wc -w < "$file")    # Amount of words -w

    local spaces
    spaces=$(grep -o " " "$file" | wc -l)   # Get the spaces separated in a colum, then pipe it to a wc -l

    echo "Number of lines: $lines"
    echo "Number of words: $words"
    echo "Number of spaces: $spaces"

    echo
    echo "First line:"
    head -n 1 "$file"

    echo
    echo "Last line:"
    tail -n 1 "$file"
    
    echo
    echo "----------------------------------------"
}

analyse_binary_file() {
    local file="$1"

    echo "Detected as binary file."
    echo "----------------------------------------"

    local bytes
    bytes=$(wc -c < "$file")    # -c options to count bytes, < "$file" so the output doesn't include the name of the file

    echo "Number of bytes: $bytes"
    echo

    echo "First 10 bytes (printable representation):"
    head -c 10 "$file" | hexdump -C     # With hexdump we get the bytes and if possible, the ASCII translation (readable)

    echo
    echo "Last 10 bytes (printable representation):"
    tail -c 10 "$file" | hexdump -C

    echo "----------------------------------------"
}

main "$@"
