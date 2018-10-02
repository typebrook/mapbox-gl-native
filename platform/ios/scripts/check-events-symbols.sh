#!/usr/bin/env bash

set -e
set -o pipefail
set -u

function step { >&2 echo -e "\033[1m\033[36m* $@\033[0m"; }
function finish { >&2 echo -en "\033[0m"; }
trap finish EXIT

FRAMEWORK=build/ios/pkg/dynamic/Mapbox.framework/Mapbox

step "Looking for Mapbox.framework…"

if [ -f ${FRAMEWORK} ]; then
    echo "Found framework: ${FRAMEWORK}"
else
    echo "No framework found — building dynamic Mapbox.framework…"
    make iframework BUILD_DEVICE=false
fi

step "Checking for un-namespaced symbols from mapbox-events-ios…"

# Symbols from mapbox-events-ios are prefixed MME. To avoid duplicate symbol
# warnings when multiple copes of mapbox-events-ios are included in a project,
# the maps SDK prefixes these symbols with MGL_.
SYMBOLS=$( nm ${FRAMEWORK} | grep \$_MME || true )

if [ -z "${SYMBOLS}" ]; then
    echo "✅ Found no un-namespaced symbols."
else
    echo "❗️ Found un-namespaced symbols:"
    echo "${SYMBOLS}"
    exit 1
fi
