#!/usr/bin/env bash
set -ex

# Prepare environment
rm -rf ~/.ndn

if has OSX $NODE_LABELS; then
    security unlock-keychain -p named-data
fi

if has Windows $NODE_LABELS; then
    alias ndnsec-keygen="./build/bin/ndnsec-keygen"
    alias ndnsec-install-cert="./build/bin/ndnsec-install-cert"
fi

ndnsec-keygen "/tmp/jenkins/$NODE_NAME" | ndnsec-install-cert -

# https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
ASAN_OPTIONS="color=always"
ASAN_OPTIONS+=":check_initialization_order=1"
ASAN_OPTIONS+=":detect_stack_use_after_return=1"
ASAN_OPTIONS+=":strict_init_order=1"
ASAN_OPTIONS+=":strict_string_checks=1"
ASAN_OPTIONS+=":detect_invalid_pointer_pairs=2"
ASAN_OPTIONS+=":strip_path_prefix=${PWD}/"
export ASAN_OPTIONS

export BOOST_TEST_BUILD_INFO=1
export BOOST_TEST_COLOR_OUTPUT=1
export BOOST_TEST_DETECT_MEMORY_LEAK=0
export BOOST_TEST_LOGGER=HRF,test_suite,stdout:XML,all,build/xunit-log.xml

# Run unit tests
./build/unit-tests
