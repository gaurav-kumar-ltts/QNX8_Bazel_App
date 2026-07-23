#!/bin/bash

# Array to hold the clean arguments
CLEANED_ARGS=()

# Loop through all arguments passed by Bazel
while [[ $# -gt 0 ]]; do
    case "$1" in
        # Strip out incompatible GCC tracking options
        -MD|-MMD|-MP)
            shift
            ;;
        # If -MF is passed, strip it and the path that follows it
        -MF)
            shift; shift
            ;;
        *)
            CLEANED_ARGS+=("$1")
            shift
            ;;
    esac
done

# Execute the real QNX qcc compiler with the safe filtered arguments
exec /home/prathik/qnx800/host/linux/x86_64/usr/bin/qcc "${CLEANED_ARGS[@]}"

