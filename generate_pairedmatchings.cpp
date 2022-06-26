#include <fftw3.h>
#include <array>
#include <vector>
#include "decomps.h"
#include "constants.h"


void fprintpair(FILE *f, int n, signed char *A, int iA, int iB) {	
	for (int i=0; i < n; ++i)
		fprintf(f, "%d ", A[i]);
	fprintf(f, ": %d %d\n", iA, iB);
}

int main(int argc, char** argv) {
	if (argc == 1)
		fprintf(stderr, "Need order of paired matchings files to compute\n"), exit(0);

	const int n = atoi(argv[1]);
	const int pafslen = n/2+1;
	const int psd_scalar = 4*n;
	const float eps = 0.01;

	const char seqns_filename[] = "matchings/%d.%d.%d.%s.seqns.txt";
	const char pafs_filename[] = "matchings/%d.%d.%d.%s.pafs.txt";

	double *fft_signal = (double*)malloc(sizeof(double)*n);
	fftw_complex *fft_result = (fftw_complex*)malloc(sizeof(fftw_complex)*n);
	fftw_plan plan = fftw_plan_dft_r2c_1d(n, fft_signal, fft_result, FFTW_ESTIMATE);

	char filename[100];
	FILE *seqns_file;
	FILE *pafs_file;

	printf("ORDER %d: Generate compression sequence pairs\n", n);

	std::vector<std::array<signed char, MAX_N>> A_seqns;
	std::vector<std::array<signed char, HALF_MAX_N>> A_pafs;
	std::vector<std::array<float, HALF_MAX_N>> A_psds_list;
	std::array<signed char, MAX_N> X = {};
	std::array<signed char, HALF_MAX_N> P = {};
	std::array<float, HALF_MAX_N> psds = {};

	int in, i;

	clock_t start = clock();

	sprintf(filename, seqns_filename, n, 0, n, "A");
	seqns_file = fopen(filename, "r");
	i = 0;
	while (fscanf(seqns_file, "%d ", &in) > 0) {	
		X[i] = in;
		i++;
		if (i % n == 0) {	
			i = 0;
			for (int j = 0; j < n; ++j)
				fft_signal[j] = X[j];
			fftw_execute(plan);
			for (int j = 1; j <= n/2; ++j)
				psds[j] = fft_result[j][0]*fft_result[j][0]+fft_result[j][1]*fft_result[j][1];

			A_seqns.push_back(X);
			A_psds_list.push_back(psds);
		}
	}
	fclose(seqns_file);

	sprintf(filename, pafs_filename, n, 0, n, "A");
	pafs_file = fopen(filename, "r");
	i = 0;
	while (fscanf(pafs_file, "%d ", &in) > 0) {	
		P[i] = in;
		i++;
		if (i % pafslen==0) {	
			i = 0;
			A_pafs.push_back(P);
		}
	}
	fclose(pafs_file);
	printf("  Computed A PSDs in %.2f seconds\n", (clock() - start)/(float)CLOCKS_PER_SEC);

	for (int c = 0; c < decomps_len[n]; ++c) {
			
		std::vector<std::array<signed char, MAX_N>> B_seqns;
		std::vector<std::array<signed char, MAX_N>> C_seqns;
		std::vector<std::array<signed char, MAX_N>> D_seqns;
		std::vector<std::array<float, HALF_MAX_N>> B_psds_list;
		std::vector<std::array<float, HALF_MAX_N>> C_psds_list;
		std::vector<std::array<float, HALF_MAX_N>> D_psds_list;
		std::vector<std::array<signed char, HALF_MAX_N>> B_pafs;
		std::vector<std::array<signed char, HALF_MAX_N>> C_pafs;
		std::vector<std::array<signed char, HALF_MAX_N>> D_pafs;

		std::array<signed char, HALF_MAX_N> AB_pafs;
		std::array<signed char, HALF_MAX_N> CD_pafs;

		clock_t start = clock();
		// TODO: 
		// 1. split these up into PAF and Sequence some number of separate files (maybe the same number of cores to parallize).

		sprintf(filename, seqns_filename, n, c, n, "B");
		seqns_file = fopen(filename, "r");
		i = 0;
		while (fscanf(seqns_file, "%d ", &in)>0) {	
			X[i] = in;
			i++;
			if (i % n == 0) {	
				i = 0;

				for (int j = 0; j < n; ++j)
					fft_signal[j] = X[j];
				fftw_execute(plan);
				for (int j = 1; j <= n/2; ++j)
					psds[j] = fft_result[j][0] * fft_result[j][0];
				
				B_seqns.push_back(X);
				B_psds_list.push_back(psds);
			}
		}
		fclose(seqns_file);

		sprintf(filename, pafs_filename, n, c, n, "B");
		pafs_file = fopen(filename, "r");
		i = 0;
		while (fscanf(pafs_file, "%d ", &in)>0) {	
			P[i] = in;
			i++;
			if(i % pafslen == 0) {	
				i = 0;
				B_pafs.push_back(P);
			}
		}
		fclose(pafs_file);

		sprintf(filename, seqns_filename, n, c, n, "C");
		seqns_file = fopen(filename, "r");
		i = 0;
		while(fscanf(seqns_file, "%d ", &in) > 0) {	
			X[i] = in;
			i++;
			if (i % n == 0) {	
				i = 0;
				for (int j=0; j<n; ++j)
					fft_signal[j] = X[j];
				fftw_execute(plan);
				for (int j=1; j<=n/2; ++j)
					psds[j] = fft_result[j][0]*fft_result[j][0];

				C_seqns.push_back(X);
				C_psds_list.push_back(psds);
			}
		}
		fclose(seqns_file);

		sprintf(filename, pafs_filename, n, c, n, "C");
		pafs_file = fopen(filename, "r");
		i = 0;
		while (fscanf(pafs_file, "%d ", &in) > 0) {	
			P[i] = in;
			i++;
			if (i % pafslen == 0) {	
				i = 0;
				C_pafs.push_back(P);
			}
		}
		fclose(pafs_file);

		sprintf(filename, seqns_filename, n, c, n, "D");
		seqns_file = fopen(filename, "r");
		i = 0;
		while (fscanf(seqns_file, "%d ", &in)>0) {	
			X[i] = in;
			i++;
			if (i % n == 0) {	
				i = 0;
				for (int j = 0; j < n; ++j)
					fft_signal[j] = X[j];
				fftw_execute(plan);
				for (int j = 1; j <= n/2; ++j)
					psds[j] = fft_result[j][0]*fft_result[j][0];
				
				D_seqns.push_back(X);
				D_psds_list.push_back(psds);
			}
		}
		fclose(seqns_file);

		sprintf(filename, pafs_filename, n, c, n, "D");
		pafs_file = fopen(filename, "r");
		i = 0;
		while(fscanf(pafs_file, "%d ", &in)>0) {	
			P[i] = in;
			i++;
			if (i % pafslen == 0) {	
				i = 0;
				D_pafs.push_back(P);
			}
		}
		fclose(pafs_file);

		long ABcount = 0;
		long CD_count = 0;

		std::array<float, HALF_MAX_N> A_psds = {};
		std::array<float, HALF_MAX_N> B_psds = {};
		std::array<float, HALF_MAX_N> AB_psds = {};
		std::array<float, HALF_MAX_N> C_psds = {};
		std::array<float, HALF_MAX_N> D_psds = {};
		std::array<float, HALF_MAX_N> CD_psds = {};

		FILE *pair_file;
		bool to_break;

		sprintf(filename, pafs_filename, n, c, n, "AB");
		pair_file = fopen(filename, "w");

		for (int iA = 0, a_len = A_psds_list.size(); iA < a_len; ++iA) {	
			if(decomps[n][c][0]*decomps[n][c][0]+decomps[n][c][1]*decomps[n][c][1]+decomps[n][c][2]*decomps[n][c][2] == psd_scalar && A_seqns[iA][0] != 0)
				continue;
			if(decomps[n][c][0]*decomps[n][c][0]+decomps[n][c][1]*decomps[n][c][1]+decomps[n][c][2]*decomps[n][c][2] == psd_scalar-2 && A_seqns[iA][0] == 0)
				continue;

			A_psds = A_psds_list[iA];

			for (int iB = 0, b_len = B_psds_list.size(); iB < b_len; ++iB) {	
				B_psds = B_psds_list[iB];

				to_break = false;
				for (int j=1; j<=n/2; ++j) {	
					AB_psds[j] = A_psds[j]+B_psds[j];
					if(AB_psds[j] > psd_scalar+eps) {	
						to_break = true;
						break;
					}
				}
				if (to_break)
					continue;

				for (int i = 0; i < pafslen; ++i)
					AB_pafs[i] = A_pafs[iA][i] + B_pafs[iB][i];

				fprintpair(pair_file, pafslen, AB_pafs.data(), iA, iB);
				ABcount++;
			}
		}
		fclose(pair_file);

		sprintf(filename, pafs_filename, n, c, n, "CD");
		pair_file = fopen(filename, "w");

		for (int iC = 0, c_len = C_psds_list.size(); iC < c_len; ++iC) {	
			C_psds = C_psds_list[iC];

			for (int iD = 0, d_len = D_psds_list.size(); iD < d_len; ++iD) {	
				D_psds = D_psds_list[iD];

				to_break = false;
				for (int j=1; j <= n/2; ++j) {	
					CD_psds[j] = C_psds[j]+D_psds[j];
					if(CD_psds[j] > psd_scalar+eps) {	
						to_break = true;
						break;
					}
				}
				if (to_break)
					continue;

				for (int i = 0; i < pafslen; ++i) {	
					CD_pafs[i] = - (C_pafs[iC][i] + D_pafs[iD][i]);
					if (i == 0)
						CD_pafs[i] += psd_scalar;
				}

				fprintpair(pair_file, pafslen, CD_pafs.data(), iC, iD);
				CD_count++;
			}
		}

		fclose(pair_file);

		sprintf(filename, "timings/%d.%d.%d.genpairtime", n, c, n);
		FILE *f = fopen(filename, "w");
		fprintf(f, "%.2f\n", (clock() - start)/(float)CLOCKS_PER_SEC);
		fclose(f);

		printf("  Case %d: %ld AB and %ld CD paired PAF sequences of length %d generated in %.2f seconds\n", c, ABcount, CD_count, pafslen, (clock() - start)/(float)CLOCKS_PER_SEC);

	}

	fftw_destroy_plan(plan);
	free(fft_signal);
	free(fft_result);
}
