COMP = c++
PHONY:
	@echo "Use ./driver.sh n to enumerate good matrices of odd order n divisible by 3"
all: generate_matching_instances_comp generate_pairedmatchings join_pairedmatchings remove_equivalent_matchedpairs
generate_matching_instances_comp: generate_matching_instances_comp.cpp decomps.h coprimelist.h
	$(COMP) generate_matching_instances_comp.cpp -O3 -std=c++0x -lfftw3 -o generate_matching_instances_comp
generate_pairedmatchings: generate_pairedmatchings.cpp decomps.h
	$(COMP) generate_pairedmatchings.cpp -O3 -std=c++0x -lfftw3 -o generate_pairedmatchings
join_pairedmatchings: join_pairedmatchings.cpp decomps.h
	$(COMP) join_pairedmatchings.cpp -O3 -std=c++0x -o join_pairedmatchings
remove_equivalent_matchedpairs: remove_equivalent_matchedpairs.cpp decomps.h coprimelist.h
	$(COMP) remove_equivalent_matchedpairs.cpp -O3 -std=c++0x -o remove_equivalent_matchedpairs
clean:
	rm -f generate_matching_instances_comp generate_pairedmatchings join_pairedmatchings remove_equivalent_matchedpairs
	for n in `seq 3 6 69`; \
	do \
		if [ -f maplesat_static_$$n ]; \
		then \
			rm maplesat_static_$$n; \
		fi; \
	done
