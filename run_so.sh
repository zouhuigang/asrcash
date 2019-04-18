#!/bin/bash
rm -rf libasr.go
mv /home/linux-cpp-sdk/sample/asr/src/libasr.so ./
python test.py