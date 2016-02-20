#!/usr/bin/sh
reset
make clean
make

# create image
esptool.py elf2image build/app.out
