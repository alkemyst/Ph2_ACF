#!/bin/bash
export QTDIR=/usr/local/Trolltech/Qt-4.8.5
export QMAKESPEC=
export ROOTSYS=/usr/local/qtRoot/root
export QTROOTSYSDIR=/usr/local/qtRoot/root
export XDAQ_ROOT=/opt/xdaq
export XDAQ_DOCUMENT_ROOT=/opt/xdaq/htdocs
export LD_LIBRARY_PATH=$ROOTSYS/lib:$QTDIR/lib:${XDAQ_ROOT}/lib:$LD_LIBRARY_PATH
export PATH=$ROOTSYS/bin:$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTROOTSYSDIR/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/cactus/lib:~/Ph2DAQ_dev/lib:${LD_LIBRARY_PATH}
for dir in lib bin
do
if [ ! -d $dir ];then
mkdir $dir
fi
done
