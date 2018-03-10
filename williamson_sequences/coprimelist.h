int coprimelength[100] = {0, 0, 0, 0, 0, 1, 0, 2, 1, 2, 1, 4, 1, 5, 2, 3, 3, 7, 2, 8, 3, 5, 4, 10, 3, 9, 5, 8, 5, 13, 3, 14, 7, 9, 7, 11, 5, 17, 8, 11, 7, 19, 5, 20, 9, 11, 10, 22, 7, 20, 9, 15, 11, 25, 8, 19, 11, 17, 13, 28, 7, 29, 14, 17, 15, 23, 9, 32, 15, 21, 11, 34, 11, 35, 17, 19, 17, 29, 11, 38, 15, 26, 19, 40, 11, 31, 20, 27, 19, 43, 11, 35, 21, 29, 22, 35, 15, 47, 20, 29};

int coprimelist[100][50] = {
 {},
 {1},
 {1},
 {1},
 {1},
 {1, 2},
 {1},
 {1, 2, 3},
 {1, 3},
 {1, 2, 4},
 {1, 3},
 {1, 2, 3, 4, 5},
 {1, 5},
 {1, 2, 3, 4, 5, 6},
 {1, 3, 5},
 {1, 2, 4, 7},
 {1, 3, 5, 7},
 {1, 2, 3, 4, 5, 6, 7, 8},
 {1, 5, 7},
 {1, 2, 3, 4, 5, 6, 7, 8, 9},
 {1, 3, 7, 9},
 {1, 2, 4, 5, 8, 10},
 {1, 3, 5, 7, 9},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
 {1, 5, 7, 11},
 {1, 2, 3, 4, 6, 7, 8, 9, 11, 12},
 {1, 3, 5, 7, 9, 11},
 {1, 2, 4, 5, 7, 8, 10, 11, 13},
 {1, 3, 5, 9, 11, 13},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
 {1, 7, 11, 13},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
 {1, 3, 5, 7, 9, 11, 13, 15},
 {1, 2, 4, 5, 7, 8, 10, 13, 14, 16},
 {1, 3, 5, 7, 9, 11, 13, 15},
 {1, 2, 3, 4, 6, 8, 9, 11, 12, 13, 16, 17},
 {1, 5, 7, 11, 13, 17},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18},
 {1, 3, 5, 7, 9, 11, 13, 15, 17},
 {1, 2, 4, 5, 7, 8, 10, 11, 14, 16, 17, 19},
 {1, 3, 7, 9, 11, 13, 17, 19},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
 {1, 5, 11, 13, 17, 19},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
 {1, 3, 5, 7, 9, 13, 15, 17, 19, 21},
 {1, 2, 4, 7, 8, 11, 13, 14, 16, 17, 19, 22},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
 {1, 5, 7, 11, 13, 17, 19, 23},
 {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 22, 23, 24},
 {1, 3, 7, 9, 11, 13, 17, 19, 21, 23},
 {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 19, 20, 22, 23, 25},
 {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26},
 {1, 5, 7, 11, 13, 17, 19, 23, 25},
 {1, 2, 3, 4, 6, 7, 8, 9, 12, 13, 14, 16, 17, 18, 19, 21, 23, 24, 26, 27},
 {1, 3, 5, 9, 11, 13, 15, 17, 19, 23, 25, 27},
 {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 20, 22, 23, 25, 26, 28},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
 {1, 7, 11, 13, 17, 19, 23, 29},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29},
 {1, 2, 4, 5, 8, 10, 11, 13, 16, 17, 19, 20, 22, 23, 25, 26, 29, 31},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31},
 {1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 14, 16, 17, 18, 19, 21, 22, 23, 24, 27, 28, 29, 31, 32},
 {1, 5, 7, 13, 17, 19, 23, 25, 29, 31},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
 {1, 3, 5, 7, 9, 11, 13, 15, 19, 21, 23, 25, 27, 29, 31, 33},
 {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 25, 26, 28, 29, 31, 32, 34},
 {1, 3, 9, 11, 13, 17, 19, 23, 27, 29, 31, 33},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
 {1, 5, 7, 11, 13, 17, 19, 23, 25, 29, 31, 35},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35},
 {1, 2, 4, 7, 8, 11, 13, 14, 16, 17, 19, 22, 23, 26, 28, 29, 31, 32, 34, 37},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 21, 23, 25, 27, 29, 31, 33, 35, 37},
 {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 13, 15, 16, 17, 18, 19, 20, 23, 24, 25, 26, 27, 29, 30, 31, 32, 34, 36, 37, 38},
 {1, 5, 7, 11, 17, 19, 23, 25, 29, 31, 35, 37},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
 {1, 3, 7, 9, 11, 13, 17, 19, 21, 23, 27, 29, 31, 33, 37, 39},
 {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 29, 31, 32, 34, 35, 37, 38, 40},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41},
 {1, 5, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41},
 {1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 18, 19, 21, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 36, 37, 38, 39, 41, 42},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41},
 {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 31, 32, 34, 35, 37, 38, 40, 41, 43},
 {1, 3, 5, 7, 9, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 35, 37, 39, 41, 43},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44},
 {1, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43},
 {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 15, 16, 17, 18, 19, 20, 22, 23, 24, 25, 27, 29, 30, 31, 32, 33, 34, 36, 37, 38, 40, 41, 43, 44, 45},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45},
 {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 29, 32, 34, 35, 37, 38, 40, 41, 43, 44, 46},
 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45},
 {1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 21, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 34, 36, 37, 39, 41, 42, 43, 44, 46, 47},
 {1, 5, 7, 11, 13, 17, 19, 23, 25, 29, 31, 35, 37, 41, 43, 47},
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48},
 {1, 3, 5, 9, 11, 13, 15, 17, 19, 23, 25, 27, 29, 31, 33, 37, 39, 41, 43, 45, 47},
 {1, 2, 4, 5, 7, 8, 10, 13, 14, 16, 17, 19, 20, 23, 25, 26, 28, 29, 31, 32, 34, 35, 37, 38, 40, 41, 43, 46, 47, 49}
};
