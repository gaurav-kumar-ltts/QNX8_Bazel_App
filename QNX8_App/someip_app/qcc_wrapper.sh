#!/bin/bash

CLEANED_ARGS=()
DEP_FILE=""

# Use QNX standard C++ driver flag
CLEANED_ARGS+=("-Y_gpp")

# Inject system include paths
CLEANED_ARGS+=("-I/home/prathik/qnx800/target/qnx/usr/include")
CLEANED_ARGS+=("-I/home/prathik/qnx800/Pi5_debin_testing/deployment/third_party/vsomeip/include")

# Inject library search paths
CLEANED_ARGS+=("-L/home/prathik/qnx800/target/qnx/usr/lib")
CLEANED_ARGS+=("-L/home/prathik/qnx800/QNX8_App/someip_app/lib")
CLEANED_ARGS+=("-L/home/prathik/qnx800/Pi5_debin_testing/deployment/third_party/vsomeip/lib")
CLEANED_ARGS+=("-L/home/prathik/qnx800/QNX8_App/dlt-daemon/build/src/lib")

# Parse incoming Bazel arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        -MF)
            DEP_FILE="$2"
            shift; shift
            ;;
        -MD|-MMD|-MP)
            shift
            ;;
        -Wthread-safety|-Wself-assign|-fcolor-diagnostics|-Wno-free-nonheap-object)
            shift
            ;;
        *)
            CLEANED_ARGS+=("$1")
            shift
            ;;
    esac
done

if [ -n "$DEP_FILE" ]; then
    CLEANED_ARGS+=("-Wp,-MD,${DEP_FILE}")
fi

# Execute qcc with retry mechanism for license lock contention
MAX_RETRIES=3
RETRY_COUNT=0
RC=1

while [ $RETRY_COUNT -lt $MAX_RETRIES ] && [ $RC -ne 0 ]; do
    /home/prathik/qnx800/host/linux/x86_64/usr/bin/qcc "${CLEANED_ARGS[@]}"
    RC=$?
    
    if [ $RC -ne 0 ]; then
        rm -f /home/prathik/.qnx/license/licenses.lck 2>/dev/null
        sleep 1
        ((RETRY_COUNT++))
    fi
done

# Filter dependency outputs for Bazel sandbox compatibility
if [ $RC -eq 0 ] && [ -n "$DEP_FILE" ] && [ -f "$DEP_FILE" ]; then
    sed -i 's| /home/prathik/[^ ]*||g' "$DEP_FILE"
    sed -i 's|^/home/prathik/[^ ]*||g' "$DEP_FILE"
    sed -i '/^[[:space:]]*\\*$/d' "$DEP_FILE"
fi

exit $RC