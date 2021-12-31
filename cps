#!/bin/bash

echo -e "PID\tComponent\tEntityID"
ps -ef | grep "/usr/bin/\(ceph-mon\|ceph-mds\|ceph-osd\|ceph-mgr\)" | grep -v grep \
| awk '
{
	print($2 "\t" $8 "\t" $13);
}
' \
| while read line; do
	read pid executable entityid <<< "$line"
	echo -e "${pid}\t$(echo ${executable} | awk -F '/' '{print $4}')\t${entityid}"
done \
| sort -k 3 \
| sort -k 2
