#!/bin/bash
DEFAULT_PASSWORD="password"

if [ -z "$ZIP_PASS" ]; then
  ZIP_PASS="$DEFAULT_PASSWORD"
fi

if [ -d ./zip ]; then
  rm -r ./zip/
fi
mkdir ./zip

cd ./target/

# find every folder under src, with a name ending in a number (i.e. a course code) and zip it for convenience.
find . -maxdepth 1 -type d | awk '/[0-9]$/' | cut -d/ -f2 | xargs -i zip --password $ZIP_PASS -r 'transcribed-{}' './{}'
cd ..
mv target/*zip ./zip/
