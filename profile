#!/bin/bash

set +x
set +e

program=$1
message=$2
program_dir=`dirname "$program"`
program_file=`basename "$program"`
message_dir=`dirname "$message"`
message_file=`basename "$message"`
dot_file="$program_dir/$program_file-$message_file.dot"
gmon="$program_dir/gmon.out"

$program $message
gprof $program $gmon | gprof2dot -o $dot_file
rm $gmon

