#!/bin/bash

# guard from running without appropriate env-vars set
if [ -z "$MAKING" ]; then
  >&2 echo -e "\e[1;31merror:\e[0;0m must be run via Makefile"
  exit 1
fi

# clone the repo
git clone https://github.com/nothings/stb $EXT_DIR/stb-setup --quiet > /dev/null

# make the required directory structure
mkdir -p $EXT_DIR/stb
cp -r $EXT_DIR/stb-setup/stb_image.h $EXT_DIR/stb/stb_image.h

# remove redundant files
rm -rf -- $EXT_DIR/stb-setup
