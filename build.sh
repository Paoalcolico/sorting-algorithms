#!/bin/bash
clear
set -e

initial_time=$(date +%s%3N)

meson compile -j 4 -C build

final_time=$(date +%s%3N)
time_diff=$((final_time - initial_time))

minutes=$((time_diff / 60000))
seconds=$(((time_diff % 60000) / 1000))
milliseconds=$((time_diff % 1000))

echo "Tempo compilando: ${minutes}m ${seconds}s ${milliseconds}ms"
