#!/bin/sh

sudo apt-get install python3.8
sudo python3.8 -m pip install gcovr

cd cov_build

python3.8 -m gcovr --version
python3.8 -m gcovr -r . -f ../src --gcov-executable /usr/bin/gcov-10 --exclude-throw-branches --exclude-unreachable-branches --xml-pretty --verbose --output ../coverage.xml

cat ../coverage.xml
