import subprocess
import os
import sys

if len(sys.argv) != 3:
	print(f"Usage: python3 {sys.argv[0]} [Script Dir] [Out Dir]")
	example_in = 'C:\\Users\\Luke\\Documents\\3ds\\acnl\\romfs\\Script'
	example_out = 'C:\\Users\\Luke\\Documents\\3ds\\myacnl\\acnl-msbt-txts\\Script_USA'
	print(f"Example: python3 {sys.argv[0]} '{example_in}' '{example_out}'")
	do_example = input("Proceed with example? y/N: ")
	if not (do_example == 'y' or do_example == 'Y'):
		exit()

if do_example == 'y' or do_example == 'Y':
	script_dir = example_in
	out_dir = example_out
else:
	script_dir = sys.argv[1]
	out_dir = sys.argv[2]

if not os.path.isdir(script_dir):
	print(f"Sorry! {script_dir} is not a valid directory!")

if not os.path.isdir(out_dir):
	os.mkdir(out_dir)

print(f"Working! Please wait!\nInput: {script_dir}\nOutput: {out_dir}")

for root,dirs,files in os.walk(script_dir):
	#for dir in dirs:
		#print(dir)
	for filename in files:
		if filename.endswith((".umsbt",".msbt")):
			ext = ".msbt"
			if filename.endswith(".umsbt"):
				ext = ".umsbt"
			filename_and_full_path = root + os.sep + filename
			filename_and_relative_path = filename_and_full_path[filename_and_full_path.find('Script'):]
			out_file = out_dir + filename_and_relative_path[filename_and_relative_path.find(os.sep):filename_and_relative_path.find(ext)]
			out_file_relative_dir = out_file[:out_file.rfind(os.sep)]
			if not os.path.isdir(out_file_relative_dir):
				os.makedirs(out_file_relative_dir)
			out_file_final = out_file + ".txt"
			#print(out_file_final)
			subprocess.run(['msbt2txt.exe',filename_and_full_path,'-o',out_file_final])

print("Done!")