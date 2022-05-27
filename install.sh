#!/bin/bash

if [ -d "release" ];then
    cd release
else
    mkdir release && cd release
fi

cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release .. 
make
sudo make install