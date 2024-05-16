#!/bin/bash

# guard from running without appropriate env-vars set
if [ -z "$MAKING" ]; then
  >&2 echo -e "\e[1;31merror:\e[0;0m must be run via Makefile"
  exit 1
fi

# clone the repo
git clone https://github.com/Dav1dde/glad.git $EXT_DIR/glad-setup --quiet > /dev/null

# generate glad
echo "Generating glad..."
cd $EXT_DIR/glad-setup
git checkout master --quiet > /dev/null
python -m glad --profile="core" --api="gl=3.3" --generator="c" --out-path="." --quiet
cd ../..

# put it into the correct structure for our program
mkdir -p $EXT_DIR/glad
cp -r $EXT_DIR/glad-setup/src $EXT_DIR/glad
cp -r $EXT_DIR/glad-setup/include/* $EXT_DIR

# create a pre-compiled glad object file
mkdir -p $OUT_DIR/$EXT_DIR
g++ $CXXFLAGS -c $EXT_DIR/glad/src/glad.c -I$EXT_DIR -o $OUT_DIR/$EXT_DIR/glad.o

# delete redundant glad-setup files
rm -rf -- $EXT_DIR/glad-setup
rm -r -- $EXT_DIR/glad/src
