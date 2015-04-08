#!/bin/sh

for x in `seq 1 15`; do
  dir=ex`printf "%02d" $x`
  echo mkdir -p "$dir"
  mkdir -p "$dir"
  touch "$dir/.gitkeep"
  echo chmod 0705 "$dir"
  chmod 0705 "$dir"
done

