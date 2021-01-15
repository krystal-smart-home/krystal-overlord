#!/bin/sh

if ! [ -d ./cov_build ]; then
	echo "~ cov_build directory doesn't exists"
	exit 1
fi

cd cov_build

git clone https://github.com/linux-test-project/lcov.git

mkdir ../cov
./lcov/bin/lcov --rc geninfo_gcov_tool=/usr/bin/gcov-10 --capture --initial --directory ./src --output init_cov.info
./lcov/bin/lcov --rc geninfo_gcov_tool=/usr/bin/gcov-10 --capture --directory ./src --output test_cov.info
./lcov/bin/lcov --rc geninfo_gcov_tool=/usr/bin/gcov-10 -a init_cov.info -a test_cov.info -o cov.info

./lcov/bin/genhtml cov.info --output-directory ../cov/overlord-ut-coverage

rm lcov -rf

cd ..

