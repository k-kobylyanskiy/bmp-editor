#!/usr/bin/python

import os
import sys
import subprocess


make = subprocess.call("make", shell=True)
if make:
	print "Compilation error\n"
else:	
	rm = subprocess.call("make clean", shell=True)
	print "Compilation successful\nRunning program...\n"
	rn = subprocess.call("build/main", shell=True)

