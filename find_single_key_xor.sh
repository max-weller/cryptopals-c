#!/bin/bash

while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "Text read from file: $line"
./single_fixed_xor -c -d "$line" -p 00000000000000000000010000000000000000000000000000000000000000002C000000000000000000000002000200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000F0205081904030A0C000107040E1003000D0D1206010400030000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 -P 1

done < "$1"


