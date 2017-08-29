#!/bin/bash

make -C .. clean
make -C .. all

make -C .. TEST=Task_Test test

./Task_Test

