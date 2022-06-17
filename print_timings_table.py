import os
import sys


def print_align(w, s):
	if isinstance(s, float):
		print(str("%.2f" % s) + " "*(w-len(str("%.2f" % s))),)
	else:
		print(str(s) + " "*(w-len(str(s))),)

if len(sys.argv) < 2:
	print("Need order (or min and max order) of timings to print")
	quit()

n1 = int(sys.argv[1])
n2 = int(sys.argv[2]) if len(sys.argv) > 2 else n1

print_align(10, "case")
print_align(10, "gen comps")
print_align(10, "gen pairs")
print_align(10, "sort")
print_align(10, "join")
print_align(10, "remequiv")
print_align(10, "solve")
print_align(10, "tally")
print_align(10, "TOTAL (h)")
print_align(10, "numinsts")
print_align(10, "numsols")
print("")

total_gen_time = 0
order_diff = 2 if n1 % 2 == 0 else 6

for n in range(n1, n2+1, order_diff):
	d = 1
	l = n/d

	cases = range(4)
	total_time = 0
	gen_time = 0
	gen_comp_time = 0
	gen_pair_time = 0
	sort_time = 0
	join_time = 0
	equiv_pairs_time = 0
	solve_time = 0
	equiv_exhaust_time = 0
	num_insts = 0
	num_sols = 0

	if os.path.exists("timings/{0}.{1}.gencomptime".format(n, l)):
		f = open("timings/{0}.{1}.gencomptime".format(n, l), "r")
		lines = f.readlines()
		f.close()
		if len(lines) > 0:
			gen_time += float(lines[0])

	total_gen_time += gen_time

	for c in cases:
		if os.path.exists("timings/{0}.{1}.{2}.genpairtime".format(n, c, l)):
			f = open("timings/{0}.{1}.{2}.genpairtime".format(n, c, l), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				gen_pair_time += float(lines[0])

		if os.path.exists("timings/{0}.{1}.{2}.AB.sorttime".format(n, c, l)):
			f = open("timings/{0}.{1}.{2}.AB.sorttime".format(n, c, l), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				sort_time += float(lines[0])

		if os.path.exists("timings/{0}.{1}.{2}.CD.sorttime".format(n, c, l)):
			f = open("timings/{0}.{1}.{2}.CD.sorttime".format(n, c, l), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				sort_time += float(lines[0])

		if os.path.exists("timings/{0}.{1}.{2}.0.jointime".format(n, c, l)):
			for s in range(10):
				f = open("timings/{0}.{1}.{2}.{3}.jointime".format(n, c, l, s), "r")
				lines = f.readlines()
				f.close()
				if len(lines)>0:
					join_time += float(lines[0])
		elif os.path.exists("timings/{0}.{1}.{2}.jointime".format(n, c, l)):
			f = open("timings/{0}.{1}.{2}.jointime".format(n, c, l), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				join_time += float(lines[0])

		if os.path.exists("timings/{0}.{1}.equivpairstime".format(n, c, l)):
			f = open("timings/{0}.{1}.equivpairstime".format(n, c, l), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				equiv_pairs_time += float(lines[0])

		if os.path.exists("timings/{0}.{1}.solvetimesum".format(n, c)):
			f = open("timings/{0}.{1}.solvetimesum".format(n, c), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				solve_time += float(lines[0])
		elif os.path.exists("timings/{0}.{1}.solvetime".format(n, c)):
			f = open("timings/{0}.{1}.solvetime".format(n, c), "r")
			lines = f.readlines()
			f.close()
			if len(lines)>0:
				solve_time += float(lines[0])

		if os.path.exists("matchedseqns/{0}.{1}.{2}.inequiv".format(n, c, l)):
			f = open("matchedseqns/{0}.{1}.{2}.inequiv".format(n, c, l), "r")
			num_insts += len(f.readlines())
			f.close()

	if os.path.exists("timings/{0}.equivexhausttime".format(n)):
		f = open("timings/{0}.equivexhausttime".format(n), "r")
		lines = f.readlines()
		f.close()
		if len(lines)>0:
			equiv_exhaust_time += float(lines[0])

	if os.path.exists("exhaust/{0}.inequiv".format(n)):
		f = open("exhaust/{0}.inequiv".format(n), "r")
		num_sols += len(f.readlines())
		f.close()

	total_time += gen_time 
	total_time += gen_pair_time
	total_time += sort_time
	total_time += join_time
	total_time += equiv_pairs_time
	total_time += solve_time
	total_time += equiv_exhaust_time

	print_align(10, n)
	print_align(10, gen_time)
	print_align(10, gen_pair_time)
	print_align(10, sort_time)
	print_align(10, join_time)
	print_align(10, equiv_pairs_time)
	print_align(10, solve_time)
	print_align(10, equiv_exhaust_time)
	print_align(10, total_time/float(60*60))
	print_align(10, num_insts)
	print_align(10, num_sols)
	print("")
