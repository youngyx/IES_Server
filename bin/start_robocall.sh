#!/bin/sh
ulimit -v unlimited
ulimit -m unlimited
ulimit -c unlimited
ulimit -n 65536
echo 4096 > /proc/sys/net/core/somaxconn
export LD_LIBRARY_PATH=`pwd`:`pwd`/../lib_linux:$LD_LIBRARY_PATH
source ~/.bash_profile
sync
echo 3 > /proc/sys/vm/drop_caches
nohup ./app -d >/dev/null 2>&1 &
#chmod +x auto.sh
#./auto.sh
