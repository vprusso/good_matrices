#include <fftw3.h>
#include <sys/stat.h>
#include <array>
#include <set>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include "decomps.h"
#include "coprimelist.h"
#include "constants.h"
#include "utils.h"


void make_dirs() {
	/* Make all directories for file output. */
	mkdir("matchings", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("timings", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("matchedpairs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("matchedseqns", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

int paf(signed char *A, int s) {
	int res = 0;
	int i = n-1;
	do {
		res += A[i]*A[(i+s)%n];
		--i;
	} while (i >= 0);
	return res;
}

void fprintseqn(FILE *f, signed char *A) {
	for (int i = 0; i < n; ++i)
		fprintf(f, "%d ", A[i]);
	fprintf(f, "\n");
}

void fprintpafs(FILE *f, signed char *A) {
	for (int i = 0; i <= n/2; ++i)
		fprintf(f, "%d ", paf(A, i));
	fprintf(f, "\n");
}

double *fft_signal_A;
fftw_complex *fft_result_A;
fftw_plan plan_A;

double *fft_signal_B;
fftw_complex *fft_result_B;
fftw_plan plan_B;

int main(int argc, char** argv) {
	char filename[100];
	const char seqns_filename[] = "matchings/%d.%d.%d.%c.seqns.txt";
	const char pafs_filename[] = "matchings/%d.%d.%d.%c.pafs.txt";

	make_dirs();

	printf("ORDER %d: Generate compression sequences\n", n);

	fft_signal_A = (double*)malloc(sizeof(double)*n);
	fft_result_A = (fftw_complex*)malloc(sizeof(fftw_complex)*n);
	plan_A = fftw_plan_dft_r2c_1d(n, fft_signal_A, fft_result_A, FFTW_ESTIMATE);

	fft_signal_B = (double*)malloc(sizeof(double)*n);
	fft_result_B = (fftw_complex*)malloc(sizeof(fftw_complex)*n);
	plan_B = fftw_plan_dft_r2c_1d(n, fft_signal_B, fft_result_B, FFTW_ESTIMATE);

	FILE *A_seqns_file, *B_seqns_file[4], *C_seqns_file[4], *D_seqns_file[4];
	FILE *A_pafs_file,  *B_pafs_file[4],  *C_pafs_file[4],  *D_pafs_file[4];
	int Btarget[4], Ctarget[4], Dtarget[4];
	
	snprintf(filename, sizeof(filename), seqns_filename, n, 0, n, 'A');
	A_seqns_file = fopen(filename, "w");
	snprintf(filename, sizeof(filename), pafs_filename, n, 0, n, 'A');
	A_pafs_file = fopen(filename, "w");
	
	for (int c = 0; c < decomps_len[n]; ++c) {
		snprintf(filename, sizeof(filename), seqns_filename, n, c, n, 'B');
		B_seqns_file[c] = fopen(filename, "w");
		snprintf(filename, sizeof(filename), seqns_filename, n, c, n, 'C');
		C_seqns_file[c] = fopen(filename, "w");
		snprintf(filename, sizeof(filename), seqns_filename, n, c, n, 'D');
		D_seqns_file[c] = fopen(filename, "w");
		snprintf(filename, sizeof(filename), pafs_filename, n, c, n, 'B');
		B_pafs_file[c] = fopen(filename, "w");
		snprintf(filename, sizeof(filename), pafs_filename, n, c, n, 'C');
		C_pafs_file[c] = fopen(filename, "w");
		snprintf(filename, sizeof(filename), pafs_filename, n, c, n, 'D');
		D_pafs_file[c] = fopen(filename, "w");

		Btarget[c] = decomps[n][c][1]*(decomps[n][c][1] % 4 == n % 4 ? 1 : -1);
		Ctarget[c] = decomps[n][c][2]*(decomps[n][c][2] % 4 == n % 4 ? 1 : -1);
		Dtarget[c] = decomps[n][c][3]*(decomps[n][c][3] % 4 == n % 4 ? 1 : -1);
	}

	clock_t start = clock();
	int Acount = 0, Bcount[4] = {}, Ccount[4] = {}, Dcount[4] = {};

	std::array<signed char, MAX_N> A = {};
	std::array<signed char, MAX_N> B = {};
	A[0] = 1;
	B[0] = 1;
	fft_signal_A[0] = 1;
	fft_signal_B[0] = 1;
	for (int i = 1; i <= n/2; ++i) {	
		A[i] = -1;
		B[i] = -1;
		fft_signal_A[i] = A[i];
		fft_signal_B[i] = B[i];
	}
	for (int i = n/2+1; i < n; ++i) {	
		A[i] = 1;
		B[i] = -1;
		fft_signal_A[i] = A[i];
		fft_signal_B[i] = B[i];
	}

	int rowsum = -n+2;

	std::set<std::array<signed char, MAX_N>> myset_A;
	std::set<std::array<signed char, MAX_N>> myset_B;

	while(1) {	
		bool filtered_A = false;
		bool filtered_B = false;
		
		fftw_execute(plan_A);
		for (int i=0; i<=n/2; ++i) {	
			double psd_A_i = fft_result_A[i][0]*fft_result_A[i][0] + fft_result_A[i][1]*fft_result_A[i][1];
			if(psd_A_i > 4*n + 0.01)
				filtered_A = true;
		}

		fftw_execute(plan_B);
		for (int i=0; i<=n/2; ++i) {	
			double psd_B_i = fft_result_B[i][0]*fft_result_B[i][0] + fft_result_B[i][1]*fft_result_B[i][1];
			if(psd_B_i > 4*n + 0.01)
				filtered_B = true;
		}

		if(!filtered_A) {	
			if(myset_A.count(A)==0) {	
				bool toadd_A = true;
				for (int j=0; j<coprimelist_len[n] && toadd_A==true; ++j) {	
					const int k = coprimelist[n][j];
					std::array<signed char, MAX_N> permutedcomp = permute(k, A);
					if(myset_A.count(permutedcomp)!=0)
						toadd_A = false;
				}
				
				if(toadd_A == true) {	
					fprintseqn(A_seqns_file, A.data());
					fprintpafs(A_pafs_file, A.data());
					Acount++;
				}
				
				myset_A.insert(A);
			}
		}

		if (!filtered_B) {
			for (int c = 0; c < decomps_len[n]; ++c) {

				if(rowsum == Btarget[c]) {	
					fprintseqn(B_seqns_file[c], B.data());
					fprintpafs(B_pafs_file[c], B.data());
					Bcount[c]++;
				}
				if (rowsum == Ctarget[c]) {	
					fprintseqn(C_seqns_file[c], B.data());
					fprintpafs(C_pafs_file[c], B.data());
					Ccount[c]++;
				}
				if (rowsum == Dtarget[c]) {	
					fprintseqn(D_seqns_file[c], B.data());
					fprintpafs(D_pafs_file[c], B.data());
					Dcount[c]++;
				}
			}
		}

		int i;
		for (i = n/2; i >= 1; --i) {	
			B[i] += 2;
			rowsum += 2;
			fft_signal_A[i] = fft_signal_B[i] = A[i] = B[i];
			if(2*i<n) {	
				B[n-i] += 2;
				rowsum += 2;
				fft_signal_B[n-i] = B[n-i];
				fft_signal_A[n-i] = A[n-i] = -B[n-i];
			}
			if (B[i] == 3) {	
				B[i] = -1;
				rowsum -= 4;
				fft_signal_A[i] = fft_signal_B[i] = A[i] = B[i];
				if (2*i < n) {	
					B[n-i] = -1;
					rowsum -= 4;
					fft_signal_B[n-i] = B[n-i];
					fft_signal_A[n-i] = A[n-i] = -B[n-i];
				}
			}
			else
				break;
		}
		if (i == 0)
			break;
	}

	snprintf(filename, sizeof(filename), "timings/%d.%d.gencomptime", n, n);
	FILE *f = fopen(filename, "w");
	fprintf(f, "%.2f\n", (clock() - start)/(float)CLOCKS_PER_SEC);
	fclose(f);

	printf("  %d-compressed matchings of length %d generated in %.2f seconds\n", 1, n, (clock() - start)/(float)CLOCKS_PER_SEC);
	for (int c = 0; c < decomps_len[n]; ++c)
		printf("    Case (%d, %d, %d): %d As, %d Bs, %d Cs, %d Ds\n", Btarget[c], Ctarget[c], Dtarget[c], Acount, Bcount[c], Ccount[c], Dcount[c]);

	fclose(A_seqns_file);
	fclose(A_pafs_file);

	for (int c = 0; c < decomps_len[n]; ++c) {	
		fclose(B_seqns_file[c]);
		fclose(C_seqns_file[c]);
		fclose(D_seqns_file[c]);
		fclose(B_pafs_file[c]);
		fclose(C_pafs_file[c]);
		fclose(D_pafs_file[c]);
	}

	fftw_destroy_plan(plan_A);
	free(fft_signal_A);
	free(fft_result_A);
	fftw_destroy_plan(plan_B);
	free(fft_signal_B);
	free(fft_result_B);
}
