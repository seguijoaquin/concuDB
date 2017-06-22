#!/bin/bash

string= `ps -a | grep ConcuServer`
set -- $string
kill -2 $1
