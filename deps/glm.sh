#!/bin/bash

# guard from running without appropriate env-vars set
if [ -z "$MAKING" ]; then
  >&2 echo -e "\e[1;31merror:\e[0;0m must be run via Makefile"
  exit 1
fi

# clone the repo
git clone https://github.com/g-truc/glm $EXT_DIR/glm-setup --quiet > /dev/null

# modify structure to better reflect the required structure
cp -r $EXT_DIR/glm-setup/glm $EXT_DIR

# delete redundant glm-setup files
rm -rf -- $EXT_DIR/glm-setup
