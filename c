#!/bin/bash

console_bin=/home/ceph/CephConsole/./bin
interactive_mode=False

function check_path() {
	if [ ! "$console_bin" ]; then
		echo "Warning: console binary path not set. Did you install by install.sh?"
		echo
	else
		test ! -d $console_bin && echo "Warning: Console binary path not found." && return
		export PATH=${console_bin}:${PATH}
	fi
}

function execute() {
	if [ $1 == "cd" ]; then
		shift
		cd $*
	else
		/bin/bash -c "$*"
	fi
}

if test $# -eq 0; then
	interactive_mode=True
fi

if [ $interactive_mode == False ]; then
	check_path
	execute $*
	exit 0
fi

check_path
while [ 1 ]; do
	echo -n "(Ceph Console) "
	read CMD
	if [ "${CMD}" ]; then
		execute ${CMD}
	fi
done
