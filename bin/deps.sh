#!/bin/sh

sudo apt-get update
sudo apt-get install -y gcc-10
sudo apt-get install -y g++-10
sudo apt-get install -y libjsoncpp-dev
sudo apt-get install -y libspdlog-dev

# boost
sudo apt-get install -y libboost-system1.71-dev
sudo apt-get install -y libboost-coroutine1.71-dev
