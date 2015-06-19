#!/bin/bash

echo Setting up this to create mini-websites on /tmp
echo This should be changed in order to point to a website reachable from afs
tar -xf style.tar -C /tmp

make && ./example.bin

echo Now try looking at this:
echo firefox /tmp/mySite/index.html

