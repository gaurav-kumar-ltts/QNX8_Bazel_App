#!/bin/bash

CLEANED_ARGS=()
DEP_FILE=""

# Parse flags from Bazel
while [[ $# -gt 0 ]]; do
    case "$1" in
        -MF)
            DEP_FILE="$2"
            shift; shift
            ;;
        -MD|-MMD|-MP)
            shift
            ;;
        *)
            CLEANED_ARGS+=("$1")
            shift
            ;;
    esac
done

# If Bazel requested a dependency file, tell qcc to write it using POSIX standard flags
if [ -n "$DEP_FILE" ]; then
    CLEANED_ARGS+=("-Wp,-MD,${DEP_FILE}")
fi

# Run the actual QNX qcc compiler
/home/prathik/qnx800/host/linux/x86_64/usr/bin/qcc "${CLEANED_ARGS[@]}"
RC=$?

# CRITICAL BAZEL MATCH: If compilation succeeded and a .d file exists, 
# strip any absolute paths (/home/...) that break Bazel's validation engine.
if [ $RC -eq 0 ] && [ -f "$DEP_FILE" ]; then
    # Filter out entries pointing outside the execution workspace sandbox
    sed -i 's| /home/prathik/[^ ]*||g' "$DEP_FILE"
    sed -i 's|^/home/prathik/[^ ]*||g' "$DEP_FILE"
    # Clean up empty lines or trailing backslashes left over by the filter
    sed -i '/^[[:space:]]*\\*$/d' "$DEP_FILE"
fi

exit $RC
