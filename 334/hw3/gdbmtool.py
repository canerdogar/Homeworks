#!/usr/bin/python

import sys
import gdbm
import struct
import time

print sys.argv

if len(sys.argv) != 2:
	sys.stderr.write("usage: " + sys.argv[0] + " gdbmfile")
	exit(-1)



db = gdbm.open(sys.argv[1],"r")

key = db.firstkey()
while key:
	print key
	key = db.nextkey(key)


while True:
	print "Input path to show, 'list' to list all files"
	try:
		path=raw_input()
	except EOFError:
		break
	if path == 'list':
		key = db.firstkey()
		while key:
			print key
			key = db.nextkey(key)
	else:
		try:
			val = db[path + "\000"]
		except KeyError:
			print "No such entry!!!"
			continue
		meta = struct.unpack('cqiiiqqq', val[:56])
		print "type:{} size:{} uid:{} gid:{} perm:{:o}".format(
			meta[0], meta[1], meta[2], meta[3], meta[4])
		print "A: {} , M: {} , C: {}".format(
			time.ctime(meta[5]),
			time.ctime(meta[6]),
			time.ctime(meta[7]))
		print "CONTENT[{}]".format(val[56:])


db.close()