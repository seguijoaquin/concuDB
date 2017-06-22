#!/bin/bash

cd server

cmake .
make all

"./ConcuServer" &
