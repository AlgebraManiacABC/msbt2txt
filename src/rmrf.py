import sys
import os
import shutil

if len(sys.argv) < 2:
	print("Need at lest one argument")

for file_num in range(len(sys.argv)-1):
	to_delete = sys.argv[file_num+1]
	if os.path.isdir(to_delete):
		shutil.rmtree(to_delete)
	elif os.path.isfile(to_delete):
		os.remove(to_delete)