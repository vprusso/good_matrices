#include <fstream>
#include <vector>
#include <stdio.h>
#include "decomps.h"
#include "constants.h"


int main(int argc, char** argv) {
	char filename[100];
	const char seqns_filename[] = "matchings/%d.%d.%d.%s.seqns.txt";
	const char pafsfilename[] = "matchings/%d.%d.%d.%s.pafs.sorted.txt";
	const char matchedfilename[] = "matchedpairs/%d.%d.%d";

	printf("ORDER %d: Join compression sequence pairs\n", n);

	std::ifstream file;
	std::string str;
	std::vector<std::string> Aseqns;
	snprintf(filename, sizeof(filename), seqns_filename, n, 0, n, "A");
	file.open(filename);
	while (std::getline(file, str))
		Aseqns.push_back(str);
	file.close();

	for (int c = 0; c < decomps_len[n]; ++c) {

		clock_t start = clock();

		std::vector<std::string> Bseqns, Cseqns, Dseqns, ABseqns, CDseqns;
		std::ofstream outfile;

		snprintf(filename, sizeof(filename), seqns_filename, n, c, n, "B");
		file.open(filename);
		while(std::getline(file, str))
			Bseqns.push_back(str);
		file.close();

		snprintf(filename, sizeof(filename), seqns_filename, n, c, n, "C");
		file.open(filename);
		while(std::getline(file, str))
			Cseqns.push_back(str);
		file.close();

		snprintf(filename, sizeof(filename), seqns_filename, n, c, n, "D");
		file.open(filename);
		while(std::getline(file, str))
			Dseqns.push_back(str);
		file.close();

		std::string ABstr, CDstr;
		std::ifstream ABfile, CDfile;

		snprintf(filename, sizeof(filename), pafsfilename, n, c, n, "AB");
		ABfile.open(filename);
		snprintf(filename, sizeof(filename), pafsfilename, n, c, n, "CD");
		CDfile.open(filename);

		int colonind;
		std::size_t sz;
		int ABind1, ABind2, CDind1, CDind2;
		int seqn_count = 0;
		bool ABend = false, CDend = false;

		if (std::getline(ABfile, str)) {	
			colonind = str.find_first_of(":");
			ABind1 = std::stoi(str.substr(colonind+2), &sz);
			ABind2 = std::stoi(str.substr(colonind+2+sz));
			ABstr = str.substr(0, colonind);
		}
		else
			ABend = CDend = true;

		if (std::getline(CDfile, str)) {	
			colonind = str.find_first_of(":");
			CDind1 = std::stoi(str.substr(colonind+2), &sz);
			CDind2 = std::stoi(str.substr(colonind+2+sz));
			CDstr = str.substr(0, colonind);
		}
		else
			ABend = CDend = true;

		snprintf(filename, sizeof(filename), matchedfilename, n, c, n);
		outfile.open(filename);

		while (!(ABend && CDend)) {	
			if (ABstr == CDstr) {
				std::string eqstr = ABstr;
				while (ABstr == eqstr) {	
					ABseqns.push_back(Aseqns[ABind1] + Bseqns[ABind2]);
					if (std::getline(ABfile, str)) {	
						colonind = str.find_first_of(":");
						ABind1 = std::stoi(str.substr(colonind+2), &sz);
						ABind2 = std::stoi(str.substr(colonind+2+sz));
						ABstr = str.substr(0, colonind);
					}
					else {	
						ABend = true;
						break;
					}
				}
				while (CDstr == eqstr) {	
					CDseqns.push_back(Cseqns[CDind1] + Dseqns[CDind2]);
					if(std::getline(CDfile, str)) {	
						colonind = str.find_first_of(":");
						CDind1 = std::stoi(str.substr(colonind + 2), &sz);
						CDind2 = std::stoi(str.substr(colonind + 2 + sz));
						CDstr = str.substr(0, colonind);
					}
					else {	
						CDend = true;
						break;
					}
				}

				for (int i=0; i<CDseqns.size(); ++i) {
					for (int j=0; j<ABseqns.size(); ++j) {	
						outfile << ABseqns[j] << CDseqns[i] << "\n";
						seqn_count++;
					}
				}

				ABseqns.clear();
				CDseqns.clear();
			}
			else if (ABstr < CDstr) {	
				if (std::getline(ABfile, str)) {	
					colonind = str.find_first_of(":");
					ABind1 = std::stoi(str.substr(colonind+2), &sz);
					ABind2 = std::stoi(str.substr(colonind+2+sz));
					ABstr = str.substr(0, colonind);
				}
				else {	
					ABend = true;
					break;
				}
			}
			else {
				if (std::getline(CDfile, str)) {	
					colonind = str.find_first_of(":");
					CDind1 = std::stoi(str.substr(colonind + 2), &sz);
					CDind2 = std::stoi(str.substr(colonind + 2 + sz));
					CDstr = str.substr(0, colonind);
				}
				else {	
					CDend = true;
					break;
				}
			}
		}
		ABfile.close();
		CDfile.close();
		outfile.close();

		snprintf(filename, sizeof(filename), "timings/%d.%d.%d.jointime", n, c, n);
		FILE *f = fopen(filename, "w");
		fprintf(f, "%.2f\n", (clock() - start)/(float)CLOCKS_PER_SEC);
		fclose(f);

		printf("  Case %d: %d matched sequence pairs of length %d generated in %.2f seconds\n", c, seqn_count, n, (clock() - start)/(float)CLOCKS_PER_SEC);
	}
}
