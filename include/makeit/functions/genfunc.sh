#!/bin/sh

NAME="$1"
UC_NAME="$2"
FILE_NAME="Fn$NAME"

cp "template.hpp" "$FILE_NAME.hpp"
sed -i "s/NameHere/$NAME/g" "$FILE_NAME.hpp"
sed -i "s/NAME_HERE/$UC_NAME/g" "$FILE_NAME.hpp"

SRC_ROOT="../../../src/makeit/functions"

cp "$SRC_ROOT/template.cpp" "$SRC_ROOT/$FILE_NAME.cpp"
sed -i "s/NameHere/$NAME/g" "$SRC_ROOT/$FILE_NAME.cpp"
