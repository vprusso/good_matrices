COMP = c++
PHONY:
	@echo "Use ./driver.sh n to enumerate good matrices of odd order n"
bin/generate_matching_instances_comp_%: generate_matching_instances_comp.cpp decomps.h coprimelist.h constants.h utils.h
	$(COMP) generate_matching_instances_comp.cpp -O3 -std=c++0x -lfftw3 -o $@ -DMAX_N=$*
bin/generate_pairedmatchings_%: generate_pairedmatchings.cpp decomps.h constants.h
	$(COMP) generate_pairedmatchings.cpp -O3 -std=c++0x -lfftw3 -o $@ -DMAX_N=$*
bin/join_pairedmatchings_%: join_pairedmatchings.cpp decomps.h
	$(COMP) join_pairedmatchings.cpp -O3 -std=c++0x -o $@ -DMAX_N=$*
bin/remove_equivalent_matchedpairs_%: remove_equivalent_matchedpairs.cpp decomps.h coprimelist.h constants.h utils.h
	$(COMP) remove_equivalent_matchedpairs.cpp -O3 -std=c++0x -o $@ -DMAX_N=$*
clean:
	rm -f bin/generate_matching_instances_comp_* bin/generate_pairedmatchings_* bin/join_pairedmatchings_* bin/remove_equivalent_matchedpairs_*
