#!/bin/bash
set -eu

readonly scriptpath=$0;
readonly scriptdir=$(dirname $0)
readonly srcdir=$scriptdir/../easyj
readonly testdir=$scriptdir/../easyj

function main(){
    format_files $srcdir
    format_files $testdir
}

function format_files(){
    local inpdir=$1; shift
    local files=$(find $inpdir -type f -regex ".*\\.hpp\\|.*\\.cpp")
    for file in $files
    do
        if [[ -f "$file" ]]; then
            format_file $file
        fi
    done
}


function format_file(){
    local file=$1; shift
    astyle --project $file
    if [[ -f $file.orig ]]; then
        echo "$file reformatted"
        rm $file.orig
    fi
}

# execute the main function
main
