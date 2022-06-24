#include <tuple>
#include <array>
#include <set>
#include <sys/stat.h>
#include "coprimelist.h"
#include "decomps.h"

#define MAX_N 70

int rowsum(int n, std::array<int, MAX_N> A) {	
	int result;
	for (int i=0; i<n; ++i)
		result += A[i];
	return result;
}

std::array<int, MAX_N> permuteA(int n, int k, std::array<int, MAX_N> A) {	
	std::array<int, MAX_N> result = {};
	for(int i=0; i<n; ++i)
		result[i] = A[(i*k)%n];
	return result;
}

std::tuple<std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>> minrep(int n, std::array<int, MAX_N> A, std::array<int, MAX_N> B, std::array<int, MAX_N> C, std::array<int, MAX_N> D) {	
	std::set<std::tuple<std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>>> equivseqns;

	for(int j=0; j<coprimelist_len[n]; ++j) {	
		int k = coprimelist[n][j];
		std::array<int, MAX_N> permutedA = permuteA(n, k, A);
		std::array<int, MAX_N> permutedB = permuteA(n, k, B);
		std::array<int, MAX_N> permutedC = permuteA(n, k, C);
		std::array<int, MAX_N> permutedD = permuteA(n, k, D);

		if(permutedC > permutedD)
			std::swap(permutedC, permutedD);
		if(permutedB > permutedC)
			std::swap(permutedB, permutedC);
		if(permutedC > permutedD)
			std::swap(permutedC, permutedD);

		equivseqns.insert(make_tuple(permutedA, permutedB, permutedC, permutedD));
	}

	return *(equivseqns.begin());
}

void fprintseqn(FILE* f, int n, std::tuple<std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>> seqn) {	
	std::array<int, MAX_N> A;
	std::array<int, MAX_N> B;
	std::array<int, MAX_N> C;
	std::array<int, MAX_N> D;
	std::tie(A, B, C, D) = seqn;

	for (int i=0; i<n; ++i)
		fprintf(f, "%d ", A[i]);
	for (int i=0; i<n; ++i)
		fprintf(f, "%d ", B[i]);
	for (int i=0; i<n; ++i)
		fprintf(f, "%d ", C[i]);
	for (int i=0; i<n; ++i)
		fprintf(f, "%d ", D[i]);
	fprintf(f, "\n");
}

int main(int argc, char** argv) {
	if (argc == 1)
		fprintf(stderr, "Need order of matched files to remove equivalences from\n"), exit(0);

	const int n = atoi(argv[1]);

	int case_to_solve = -1;
	if (argc>2)
		case_to_solve = atoi(argv[2]);

	int result;
	char filename[100];
	const char seqnsfilename[] = "matchedpairs/%d.%d.%d";
	const char seqnsoutfilename[] = "matchedseqns/%d.%d.%d.inequiv";

	mkdir("timings", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("matchedseqns", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	printf("ORDER %d: Remove equivalent matched compressions\n", n);
	
	FILE* seqnsfile, * seqnsoutfile;

	for(int c = 0; c < decomps_len[n]; ++c) {
		if(case_to_solve != -1 && case_to_solve != c)
			continue;

		sprintf(filename, seqnsoutfilename, n, c, n);
		seqnsoutfile = fopen(filename, "w");

		clock_t start = clock();

		int in, total_count = 0, inequiv_count = 0;
		std::set<std::tuple<std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>>> inequiv_seqns;
		std::array<int, MAX_N> A = {};
		std::array<int, MAX_N> B = {};
		std::array<int, MAX_N> C = {};
		std::array<int, MAX_N> D = {};

		sprintf(filename, seqnsfilename, n, c, n);
		seqnsfile = fopen(filename, "r");

		while(fscanf(seqnsfile, "%d ", &in)>0) {	
			A[0] = in;
			int res;
			for (int i=1; i<n; ++i) {	
				res = fscanf(seqnsfile, "%d ", &in);
				A[i] = in;
			}
			for (int i=0; i<n; ++i) {	
				res = fscanf(seqnsfile, "%d ", &in);
				B[i] = in;
			}
			for (int i=0; i<n; ++i) {	
				res = fscanf(seqnsfile, "%d ", &in);
				C[i] = in;
			}
			for (int i=0; i<n; ++i) {	
				res = fscanf(seqnsfile, "%d ", &in);
				D[i] = in;
			}

			std::tuple<std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>, std::array<int, MAX_N>> repseqn = minrep(n, A, B, C, D);
			if(inequiv_seqns.count(repseqn)==0) {	
				inequiv_seqns.insert(repseqn);
				fprintseqn(seqnsoutfile, n, make_tuple(A, B, C, D));
				inequiv_count++;
			}

			total_count++;
		}

		fclose(seqnsfile);

		sprintf(filename, "timings/%d.%d.equivpairstime", n, c);
		FILE* f = fopen(filename, "w");
		fprintf(f, "%.2f\n", (clock() - start)/(float)CLOCKS_PER_SEC);
		fclose(f);

		printf("  Case %d: %d/%d inequivalent matched sequences of length %d output in %.2f seconds\n", c, inequiv_count, total_count, n, (clock() - start)/(float)CLOCKS_PER_SEC);

		fclose(seqnsoutfile);
	}

}
