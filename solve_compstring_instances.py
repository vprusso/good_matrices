import os, time, sys
import subprocess

verbose = False
uselogs = False

if len(sys.argv) < 2:
	print("Need order (and optionally a case #) of the search to run")
	quit()

n = int(sys.argv[1])
case_to_solve = int(sys.argv[2]) if len(sys.argv) > 2 else -1

def runstr(n, c):
	if c == -1:
		return "%s" % n
	else:
		return "%s.%s" % (n, c)

inname = "input/compstring/%s.in"
logname = "logs/%s.log"
exhaustname = "exhaust/%s"
timingsname = "timings/%s.solvetime"

exhaust_dir = "exhaust"
log_dir = "logs"
timing_dir = "timings"

if not os.path.exists("exhaust"): 
	os.makedirs(exhaust_dir)
if uselogs:
	if not os.path.exists(log_dir): 
		os.makedirs(log_dir)
if not os.path.exists(timing_dir): 
	os.makedirs(timing_dir)

if len(sys.argv) >= 4:
	d = int(sys.argv[3])
elif n % 2 == 0:
	d = 2
elif n % 3 == 0:
	d = 3
elif n % 5 == 0:
	d = 5
elif n % 7 == 0:
	d = 7
else:
	d = 1

l = n/d

if not os.path.exists("maplesat_static_{0}".format(n)):
	subprocess.call(["make", "maplesat_static_{0}".format(n)])

print(f"ORDER {n}: Solve SAT instances")

for c in range(4):

	if case_to_solve != -1 and case_to_solve != c:
		continue

	if uselogs:
		logfile = open(logname % runstr(n, c), "w")
	else:
		logfile = open("/dev/null", "w")

	if not os.path.exists("matchedseqns/{0}.{1}.{2}.inequiv".format(n, c, l)):
		continue

	if os.path.exists(exhaustname % runstr(n, c)):
		subprocess.call(["mv", exhaustname % runstr(n, c), exhaust_dir])
		#call("mv {0} {1}".format(exhaustname % runstr(n, c), exhaustname % runstr(n, c) + ".orig").split(" "))
	subprocess.call(["touch", exhaustname % runstr(n, c)])
	#call("touch {0}".format(exhaustname % runstr(n, c)).split(" "))

	f = open("matchedseqns/{0}.{1}.{2}.inequiv".format(n, c, l), "r")
	lines = f.readlines()
	f.close()

	start = time.time()
	totalsolved = 0

	for li in range(len(lines)):

		pos = lines[li][:-2].split(" ")
		pos = map(int, pos)
		assert(len(pos)==4*l)

		compstring = "{0},".format(d)
		for x in pos:
			compstring += "{0},".format(x)
		compstring = compstring[:-1]

		command = "./maplesat_static_{0} -no-pre -verb={1} ".format(n, 1 if uselogs else 0) + inname % runstr(n, -1) + " -exhaustive=" + exhaustname % runstr(n, c)
		command += " -compstring=" + compstring

		if verbose:
			print(command)

#		call(command.split(" "), stdout=logfile)
		subprocess.run(command.split(" "), stdout=logfile)

		totalsolved += 1

	print("Case {0}: {1} SAT instances solved in %.2f seconds".format(c, totalsolved) % (time.time()-start))

	f = open(timingsname % runstr(n, c), "w")
	f.write("%.2f\n" % (time.time()-start))
	f.close()
