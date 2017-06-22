#!/bin/bash

string=`ps -a | grep ConcuServer`
until [ -z $string ]; do
    set -- $string
	kill -2 $1
	string=`ps -a | grep ConcuServer`
         done

