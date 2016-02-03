import time, sys, os.path, glob, math
from subprocess32 import call

sharcnet = False

if len(sys.argv) < 2:
	print "need order of search to run"
	quit()

n = int(sys.argv[1])

def runstr(n, c, k):
	if k == -1 and c == -1:
		return "%s" % n
	elif k == -1 and c == "*":
		return "%d.*" % n
	elif k == -1:
		return "%d.%d" % (n, c)
	elif k == "*" and c == "*":
		return "%d.*.*" % n
	elif k == "*":
		return "%d.%d.*" % (n, c)
	else:
		return "%d.%d.%d" % (n, c, k)

inname = "input/squaredecomp/%s.in"
resultname = "results/squaredecomp/%s.out"
logname = "output/squaredecomp/%s.log"

files = glob.glob(inname % runstr(n, "*", -1))

for f in files:
	c = int(f.split(".")[-2])

	command = "./maplesat_static " + inname % runstr(n, c, -1) + " " + resultname % runstr(n, c, -1)
	callcommand = ["./maplesat_static", inname % runstr(n, c, -1), resultname % runstr(n, c, -1)]
	if sharcnet == True:
		command = "sqsub -r 24h --mpp=2G -o " + logname % runstr(n, c, -1) + " " + command
		callcommand = ["sqsub", "-r", "24h", "--mpp=2G", "-o", logname % runstr(n, c, -1)] + callcommand

	logfile = open(logname % runstr(n, c, -1), "w")
	print command
	if sharcnet == True:
		call(callcommand)
	else:
		call(callcommand, stdout=logfile)
	logfile.close()
