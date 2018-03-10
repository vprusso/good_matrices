#sums of squares decompositions for 4*n for n = 1..69
sq = [0 for i in range(71)]
sq[1] = [[1, 1, 1, 1]]
sq[2] = [[0, 0, 2, 2]]
sq[3] = [[1, 1, 1, 3]]
sq[4] = [[0, 0, 0, 4], [2, 2, 2, 2]]
sq[5] = [[1, 1, 3, 3]]
sq[6] = [[0, 2, 2, 4]]
sq[7] = [[1, 1, 1, 5], [1, 3, 3, 3]]
sq[8] = [[0, 0, 4, 4]]
sq[9] = [[1, 1, 3, 5], [3, 3, 3, 3]]
sq[10] = [[0, 0, 2, 6], [2, 2, 4, 4]]
sq[11] = [[1, 3, 3, 5]]
sq[12] = [[0, 4, 4, 4], [2, 2, 2, 6]]
sq[13] = [[1, 1, 1, 7], [1, 1, 5, 5], [3, 3, 3, 5]]
sq[14] = [[0, 2, 4, 6]]
sq[15] = [[1, 1, 3, 7], [1, 3, 5, 5]]
sq[16] = [[0, 0, 0, 8], [4, 4, 4, 4]]
sq[17] = [[1, 3, 3, 7], [3, 3, 5, 5]]
sq[18] = [[0, 0, 6, 6], [0, 2, 2, 8], [2, 4, 4, 6]]
sq[19] = [[1, 1, 5, 7], [1, 5, 5, 5], [3, 3, 3, 7]]
sq[20] = [[0, 0, 4, 8], [2, 2, 6, 6]]
sq[21] = [[1, 1, 1, 9], [1, 3, 5, 7], [3, 5, 5, 5]]
sq[22] = [[0, 4, 6, 6], [2, 2, 4, 8]]
sq[23] = [[1, 1, 3, 9], [3, 3, 5, 7]]
sq[24] = [[0, 4, 4, 8]]
sq[25] = [[1, 1, 7, 7], [1, 3, 3, 9], [1, 5, 5, 7], [5, 5, 5, 5]]
sq[26] = [[0, 0, 2, 10], [0, 2, 6, 8], [4, 4, 6, 6]]
sq[27] = [[1, 1, 5, 9], [1, 3, 7, 7], [3, 3, 3, 9], [3, 5, 5, 7]]
sq[28] = [[2, 2, 2, 10], [2, 6, 6, 6], [4, 4, 4, 8]]
sq[29] = [[1, 3, 5, 9], [3, 3, 7, 7]]
sq[30] = [[0, 2, 4, 10], [2, 4, 6, 8]]
sq[31] = [[1, 1, 1, 11], [1, 5, 7, 7], [3, 3, 5, 9], [5, 5, 5, 7]]
sq[32] = [[0, 0, 8, 8]]
sq[33] = [[1, 1, 3, 11], [1, 1, 7, 9], [1, 5, 5, 9], [3, 5, 7, 7]]
sq[34] = [[0, 0, 6, 10], [0, 6, 6, 8], [2, 2, 8, 8], [2, 4, 4, 10]]
sq[35] = [[1, 3, 3, 11], [1, 3, 7, 9], [3, 5, 5, 9]]
sq[36] = [[0, 0, 0, 12], [0, 4, 8, 8], [2, 2, 6, 10], [6, 6, 6, 6]]
sq[37] = [[1, 1, 5, 11], [1, 7, 7, 7], [3, 3, 3, 11], [3, 3, 7, 9], [5, 5, 7, 7]]
sq[38] = [[0, 2, 2, 12], [0, 4, 6, 10], [4, 6, 6, 8]]
sq[39] = [[1, 3, 5, 11], [1, 5, 7, 9], [3, 7, 7, 7], [5, 5, 5, 9]]
sq[40] = [[0, 0, 4, 12], [4, 4, 8, 8]]
sq[41] = [[1, 1, 9, 9], [3, 3, 5, 11], [3, 5, 7, 9]]
sq[42] = [[0, 2, 8, 10], [2, 2, 4, 12], [2, 6, 8, 8], [4, 4, 6, 10]]
sq[43] = [[1, 1, 1, 13], [1, 1, 7, 11], [1, 3, 9, 9], [1, 5, 5, 11], [5, 7, 7, 7]]
sq[44] = [[0, 4, 4, 12], [2, 6, 6, 10]]
sq[45] = [[1, 1, 3, 13], [1, 3, 7, 11], [1, 7, 7, 9], [3, 3, 9, 9], [3, 5, 5, 11], [5, 5, 7, 9]]
sq[46] = [[0, 2, 6, 12], [2, 4, 8, 10]]
sq[47] = [[1, 3, 3, 13], [1, 5, 9, 9], [3, 3, 7, 11], [3, 7, 7, 9]]
sq[48] = [[0, 8, 8, 8], [4, 4, 4, 12]]
sq[49] = [[1, 1, 5, 13], [1, 5, 7, 11], [3, 3, 3, 13], [3, 5, 9, 9], [5, 5, 5, 11], [7, 7, 7, 7]]
sq[50] = [[0, 0, 2, 14], [0, 0, 10, 10], [0, 6, 8, 10], [2, 4, 6, 12], [6, 6, 8, 8]]
sq[51] = [[1, 1, 9, 11], [1, 3, 5, 13], [3, 5, 7, 11], [5, 7, 7, 9]]
sq[52] = [[0, 0, 8, 12], [2, 2, 2, 14], [2, 2, 10, 10], [4, 8, 8, 8], [6, 6, 6, 10]]
sq[53] = [[1, 3, 9, 11], [1, 7, 9, 9], [3, 3, 5, 13], [5, 5, 9, 9]]
sq[54] = [[0, 2, 4, 14], [0, 4, 10, 10], [0, 6, 6, 12], [2, 2, 8, 12], [4, 6, 8, 10]]
sq[55] = [[1, 1, 7, 13], [1, 5, 5, 13], [1, 7, 7, 11], [3, 3, 9, 11], [3, 7, 9, 9], [5, 5, 7, 11]]
sq[56] = [[0, 4, 8, 12]]
sq[57] = [[1, 1, 1, 15], [1, 3, 7, 13], [1, 5, 9, 11], [3, 5, 5, 13], [3, 7, 7, 11], [7, 7, 7, 9]]
sq[58] = [[0, 0, 6, 14], [2, 4, 4, 14], [2, 8, 8, 10], [4, 4, 10, 10], [4, 6, 6, 12]]
sq[59] = [[1, 1, 3, 15], [3, 3, 7, 13], [3, 5, 9, 11], [5, 7, 9, 9]]
sq[60] = [[2, 2, 6, 14], [2, 6, 10, 10], [4, 4, 8, 12]]
sq[61] = [[1, 1, 11, 11], [1, 3, 3, 15], [1, 5, 7, 13], [1, 9, 9, 9], [5, 5, 5, 13], [5, 7, 7, 11]]
sq[62] = [[0, 2, 10, 12], [0, 4, 6, 14], [2, 6, 8, 12]]
sq[63] = [[1, 1, 5, 15], [1, 1, 9, 13], [1, 3, 11, 11], [1, 7, 9, 11], [3, 3, 3, 15], [3, 5, 7, 13], [3, 9, 9, 9], [5, 5, 9, 11]]
sq[64] = [[0, 0, 0, 16], [8, 8, 8, 8]]
sq[65] = [[1, 3, 5, 15], [1, 3, 9, 13], [3, 3, 11, 11], [3, 7, 9, 11], [7, 7, 9, 9]]
sq[66] = [[0, 2, 2, 16], [0, 2, 8, 14], [0, 8, 10, 10], [2, 4, 10, 12], [4, 4, 6, 14], [6, 8, 8, 10]]
sq[67] = [[1, 5, 11, 11], [1, 7, 7, 13], [3, 3, 5, 15], [3, 3, 9, 13], [5, 5, 7, 13], [5, 9, 9, 9], [7, 7, 7, 11]]
sq[68] = [[0, 0, 4, 16], [0, 8, 8, 12], [2, 6, 6, 14], [6, 6, 10, 10]]
sq[69] = [[1, 1, 7, 15], [1, 5, 5, 15], [1, 5, 9, 13], [3, 5, 11, 11], [3, 7, 7, 13], [5, 7, 9, 11]]
sq[70] = [[0, 6, 10, 12], [2, 2, 4, 16], [2, 4, 8, 14], [4, 8, 10, 10], [6, 6, 8, 12]]
