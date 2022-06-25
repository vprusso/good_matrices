#include <tuple>
#include <array>
#include <set>
#include <sys/stat.h>
#include "coprimelist.h"
#include "decomps.h"

#define MAX_N 70

std::array<signed char, MAX_N> permute(int n, int k, std::array<signed char, MAX_N> M) {	
	std::array<signed char, MAX_N> result = {};
	int_fast32_t i = 0;
	do {
		result[i] = M[(i * k) % n];
		++i;
	} while (i < n);
	return result;
}

std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> minrep(int n, std::array<signed char, MAX_N> A, std::array<signed char, MAX_N> B, std::array<signed char, MAX_N> C, std::array<signed char, MAX_N> D) {	
	std::set<std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>>> equivseqns;

	for (int j = 0; j < coprimelist_len[n]; ++j) {	
		int k = coprimelist[n][j];
		std::array<signed char, MAX_N> permutedA = permute(n, k, A);
		std::array<signed char, MAX_N> permutedB = permute(n, k, B);
		std::array<signed char, MAX_N> permutedC = permute(n, k, C);
		std::array<signed char, MAX_N> permutedD = permute(n, k, D);

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

void fprintseqn(FILE *f, int n, std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> seqn) {	
	std::array<signed char, MAX_N> A;
	std::array<signed char, MAX_N> B;
	std::array<signed char, MAX_N> C;
	std::array<signed char, MAX_N> D;
	std::tie(A, B, C, D) = seqn;

	for (int i = 0; i < n; ++i)
		fprintf(f, "%d ", A[i]);
	for (int i = 0; i < n; ++i)
		fprintf(f, "%d ", B[i]);
	for (int i = 0; i < n; ++i)
		fprintf(f, "%d ", C[i]);
	for (int i = 0; i < n; ++i)
		fprintf(f, "%d ", D[i]);
	fprintf(f, "\n");
}

int main(int argc, char **argv) {
	if (argc == 1)
		fprintf(stderr, "Need order of matched files to remove equivalences from\n"), exit(0);

	const int n = atoi(argv[1]);
	int result;
	char filename[100];
	const char seqns_filename[] = "matchedpairs/%d.%d.%d";
	const char seqns_out_filename[] = "matchedseqns/%d.%d.%d.inequiv";

	mkdir("timings", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("matchedseqns", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	printf("ORDER %d: Remove equivalent matched compressions\n", n);
	
	FILE *seqns_file, *seqns_out_file;

	for (int c = 0; c < decomps_len[n]; ++c) {
		sprintf(filename, seqns_out_filename, n, c, n);
		seqns_out_file = fopen(filename, "w");

		clock_t start = clock();
		int in, total_count = 0, inequiv_count = 0;

		std::set<std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>>> inequiv_seqns;
		std::array<signed char, MAX_N> A = {};
		std::array<signed char, MAX_N> B = {};
		std::array<signed char, MAX_N> C = {};
		std::array<signed char, MAX_N> D = {};

		sprintf(filename, seqns_filename, n, c, n);
		seqns_file = fopen(filename, "r");

		while(fscanf(seqns_file, "%d ", &in) > 0) {	
			A[0] = in;
			int res;
			for (int i = 1; i < n; ++i) {	
				res = fscanf(seqns_file, "%d ", &in);
				A[i] = in;
			}
			for (int i = 0; i < n; ++i) {	
				res = fscanf(seqns_file, "%d ", &in);
				B[i] = in;
			}
			for (int i = 0; i < n; ++i) {	
				res = fscanf(seqns_file, "%d ", &in);
				C[i] = in;
			}
			for (int i = 0; i < n; ++i) {	
				res = fscanf(seqns_file, "%d ", &in);
				D[i] = in;
			}

			std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> rep_seqn = minrep(n, A, B, C, D);
			if (inequiv_seqns.count(rep_seqn) == 0) {	
				inequiv_seqns.insert(rep_seqn);
				fprintseqn(seqns_out_file, n, make_tuple(A, B, C, D));
				inequiv_count++;
			}
			total_count++;
		}
		fclose(seqns_file);

		sprintf(filename, "timings/%d.%d.equivpairstime", n, c);
		FILE *f = fopen(filename, "w");
		fprintf(f, "%.2f\n", (clock() - start)/(float)CLOCKS_PER_SEC);
		fclose(f);

		printf("  Case %d: %d/%d inequivalent matched sequences of length %d output in %.2f seconds\n", c, inequiv_count, total_count, n, (clock() - start)/(float)CLOCKS_PER_SEC);
		fclose(seqns_out_file);
	}
}
