#!/bin/bash

file_path=$1
repl_string=$2
new_string=$3


if [ -z "$file_path" ] || [ -z "$repl_string" ] || [ -z "$new_string" ]; then
    echo "Not enough arguments."
    exit 0
fi

if [ ! -f "$file_path" ]; then
echo "'$file_path' does not exist."
exit 0
fi

if [ ! -s "$file_path" ]; then
echo "'$file_path' is empty."
exit 0
fi

if ! grep -q "$repl_string" "$file_path"; then
echo "'$repl_string' does not exist."
exit
fi

sed -i '' "s/$repl_string/$new_string/g" $file_path

size=$(wc -c < $file_path)
date=$(date -r $file_path '+%Y-%m-%d %H:%M')
shasum=$(shasum -a 256 $file_path)
algsha='sha256'

echo $file_path - $size - $date - ${shasum:0:64} - $algsha >> src/files.log