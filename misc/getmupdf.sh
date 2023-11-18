#!/bin/sh
set -eu

MUPDF_OUTPUT_DIR="$1"
u="git://git.ghostscript.com/mupdf"
MUPDF_URL="${2-$u}"

if [ ! -d ${MUPDF_OUTPUT_DIR} ]; then
    echo "mupdf does not exist, fetching it from ${MUPDF_URL}"
    git clone ${cloneargs-} ${MUPDF_URL} ${MUPDF_OUTPUT_DIR}
    cd ${MUPDF_OUTPUT_DIR}
    git submodule update --init --recursive --jobs 0
fi

