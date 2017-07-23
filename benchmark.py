#!/usr/bin/env python2.7

import os
import sys

i = 1

while i <= 10000000:
  print("Merge: n = {}".format(i))
  os.system("shuf -i1-100000000 -n {} | ./measure ./lsort -n > /dev/null".format(i))
  print("Quicksort: n = {}".format(i))
  os.system("shuf -i1-100000000 -n {} | ./measure ./lsort -n -q > /dev/null".format(i))
  i *= 10;
