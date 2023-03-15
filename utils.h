#include <array>
#include "constants.h"


std::array<signed char, MAX_N> permute(int k, std::array<signed char, MAX_N> M) {	
	std::array<signed char, MAX_N> result = {};
	int i = n-1;
	do {
		result[i] = M[(i * k) % n];
		--i;
	} while (i >= 0);
	return result;
}
