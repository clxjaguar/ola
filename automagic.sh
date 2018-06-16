#!/bin/sh

# Because auto* is too difficult for me

libtoolize && aclocal && autoreconf
automake --add-missing
./configure "$@"

