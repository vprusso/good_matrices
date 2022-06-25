#include <tuple>
#include <array>
#include <set>
#include <sys/stat.h>
#include "coprimelist.h"
#include "decomps.h"

#define MAX_N 70

int paf(int n, const std::array<signed char, MAX_N> &A, int s) {	
	int res = 0;
	int_fast32_t i = 0;
	do {
		res += A[i] * A[(i + s) % n];
		++i;
	} while (i < n);
	return res;
}

void negate(int n, std::array<signed char, MAX_N> &A) {	
	int_fast32_t i = 0;
	do { 
		A[i] = -A[i];
		++i;
	} while (i < n);
}

void altnegate(int n, std::array<signed char, MAX_N> &A) {	
	int_fast32_t i = 1;
	do { 
		A[i] = -A[i];
		i += 2;
	} while (i < n);
}

std::array<signed char, MAX_N> permute(int n, int k, int s, const std::array<signed char, MAX_N> &A) {	
	std::array<signed char, MAX_N> result = {};
	do {
		result[i] = A[(i * k + s) % n];
		++i;
	} while (i < n);
	return result;
}

std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> minrep(int n, const std::array<signed char, MAX_N> &A, const std::array<signed char, MAX_N> &B, const std::array<signed char, MAX_N> &C, const std::array<signed char, MAX_N> &D) {	
	std::set<std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>>> equivseqns;

	for (int j=0; j<coprimelist_len[n]; ++j) {	
		int k = coprimelist[n][j];
		std::array<signed char, MAX_N> permutedA = permute(n, k, 0, A);
		std::array<signed char, MAX_N> permutedB = permute(n, k, 0, B);
		std::array<signed char, MAX_N> permutedC = permute(n, k, 0, C);
		std::array<signed char, MAX_N> permutedD = permute(n, k, 0, D);

		if (permutedA[0] < 0)
			negate(n, permutedA);

		if (permutedB[0] < 0)
			negate(n, permutedB);

		if (permutedC[0] < 0)
			negate(n, permutedC);

		if (permutedD[0] < 0)
			negate(n, permutedD);

		if (n % 2 == 0) {	
			std::array<signed char, MAX_N> altpermutedA = permute(n, 1, n/2, permutedA);
			std::array<signed char, MAX_N> altpermutedB = permute(n, 1, n/2, permutedB);
			std::array<signed char, MAX_N> altpermutedC = permute(n, 1, n/2, permutedC);
			std::array<signed char, MAX_N> altpermutedD = permute(n, 1, n/2, permutedD);

			if (altpermutedA[0] < 0)
				negate(n, altpermutedA);

			if (altpermutedB[0] < 0)
				negate(n, altpermutedB);

			if (altpermutedC[0] < 0)
				negate(n, altpermutedC);

			if (altpermutedD[0] < 0)
				negate(n, altpermutedD);

			if (permutedA < altpermutedA)
				permutedA = altpermutedA;

			if (permutedB < altpermutedB)
				permutedB = altpermutedB;

			if (permutedC < altpermutedC)
				permutedC = altpermutedC;

			if (permutedD < altpermutedD)
				permutedD = altpermutedD;
		}

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

std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> minrep_full(int n, std::array<signed char, MAX_N> &A, std::array<signed char, MAX_N> &B, std::array<signed char, MAX_N> &C, std::array<signed char, MAX_N> &D) {	
	std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> rep1 = minrep(n, A, B, C, D);
	
	if(n % 2 == 1)
		return rep1;
	else {
		altnegate(n, A);
		altnegate(n, B);
		altnegate(n, C);
		altnegate(n, D);
		
		std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> rep2 = minrep(n, A, B, C, D);

		altnegate(n, A);
		altnegate(n, B);
		altnegate(n, C);
		altnegate(n, D);
		
		return (rep1 < rep2) ? rep1 : rep2;
	}
}

void fprintseqn(FILE *f, int n, const std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> &seqn) {	
	std::array<signed char, MAX_N> A;
	std::array<signed char, MAX_N> B;
	std::array<signed char, MAX_N> C;
	std::array<signed char, MAX_N> D;
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

void fprettyprintseqn(FILE *f, int n, const std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> &seqn) {	
	std::array<signed char, MAX_N> A;
	std::array<signed char, MAX_N> B;
	std::array<signed char, MAX_N> C;
	std::array<signed char, MAX_N> D;
	std::tie(A, B, C, D) = seqn;

	for (int i=0; i<n; ++i)
		fprintf(f, "%c", A[i] == 1 ? '+' : '-');
	fprintf(f, " ");
	for (int i=0; i<n; ++i)
		fprintf(f, "%c", B[i] == 1 ? '+' : '-');
	fprintf(f, " ");
	for (int i=0; i<n; ++i)
		fprintf(f, "%c", C[i] == 1 ? '+' : '-');
	fprintf(f, " ");
	for (int i=0; i<n; ++i)
		fprintf(f, "%c", D[i] == 1 ? '+' : '-');
}

int main(int argc, char** argv) {
	if(argc==1)
		fprintf(stderr, "Need order of matched files to remove equivalences from\n"), exit(0);

	const int n = atoi(argv[1]);

	int casetosolve = -1;
	if(argc>2)
		casetosolve = atoi(argv[2]);

	int result;
	char filename[100];
	const char seqnsfilename[] = "exhaust/%d.%d";
	const char seqnsoutfilename[] = "exhaust/%d.inequiv";
	const char seqnsoutfilenamealt[] = "exhaust/%d.%d.inequiv";
	const char seqnsprettyoutfilename[] = "exhaust/good-%d.txt";

	mkdir("timings", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	FILE *seqnsfile, *seqnsoutfile, *seqnsprettyoutfile;

	int invalidcount = 0;
	
	sprintf(filename, seqnsprettyoutfilename, n);
	seqnsprettyoutfile = fopen(filename, "w");

	if(casetosolve==-1)
		sprintf(filename, seqnsoutfilename, n);
	else
		sprintf(filename, seqnsoutfilenamealt, n, casetosolve);
	seqnsoutfile = fopen(filename, "w");

	int in, totalcount = 0, inequivcount = 0;
	std::set<std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>>> inequivseqns;
	std::array<signed char, MAX_N> A = {};
	std::array<signed char, MAX_N> B = {};
	std::array<signed char, MAX_N> C = {};
	std::array<signed char, MAX_N> D = {};

	clock_t start = clock();

	for (int c = 0; c < decomps_len[n]; ++c) {
		if(casetosolve != -1 && casetosolve != c)
			continue;

		sprintf(filename, seqnsfilename, n, c);
		seqnsfile = fopen(filename, "r");
		if(seqnsfile==NULL)
			continue;

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

			for (int s=1; s<=n/2; ++s) {	
				if(paf(n, A, s) + paf(n, B, s) + paf(n, C, s) + paf(n, D, s) != 0) {	
					invalidcount++;
					break;
				}
			}

			std::tuple<std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>, std::array<signed char, MAX_N>> repseqn = minrep_full(n, A, B, C, D);

			if(inequivseqns.count(repseqn)==0) {
				inequivseqns.insert(repseqn);
				fprintseqn(seqnsoutfile, n, make_tuple(A, B, C, D));
				fprettyprintseqn(seqnsprettyoutfile, n, make_tuple(A, B, C, D));
				fprintf(seqnsprettyoutfile, "\n");
				inequivcount++;
			}

			totalcount++;
		}

		fclose(seqnsfile);

		if(invalidcount > 0)
			printf("  WARNING: Read %d sequences which were not defining rows of good matrices\n", invalidcount);
	}
	fclose(seqnsprettyoutfile);
	fclose(seqnsoutfile);

	sprintf(filename, "timings/%d.equivexhausttime", n);
	FILE *f = fopen(filename, "w");
	fprintf(f, "%.2f\n", (clock() - start)/(float)CLOCKS_PER_SEC);
	fclose(f);

	printf("Order %d: %d/%d inequivalent sequences of length %d output in %.2f seconds\n", n, inequivcount, totalcount, n, (clock() - start)/(float)CLOCKS_PER_SEC);

}