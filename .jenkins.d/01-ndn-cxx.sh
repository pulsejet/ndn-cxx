#!/usr/bin/env bash
set -ex

if ! has Windows $NODE_LABELS; then
    sudo rm -f /usr/local/bin/ndnsec*
    sudo rm -fr /usr/local/include/ndn-cxx
    sudo rm -f /usr/local/lib{,64}/libndn-cxx*
    sudo rm -f /usr/local/lib{,64}/pkgconfig/libndn-cxx.pc
fi
