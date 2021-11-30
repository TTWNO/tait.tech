#!/bin/bash

if [ -d "targe"t ]; then
  rm -r ./target
fi
if [ -d "target_tmp" ]; then
  rm -r ./target_tmp
fi

find ./src/ -name *md -exec ~/Documents/transcription-tools/create_html/save_html.sh '{}' ./target \;

./zip.sh
