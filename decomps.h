#ifndef DECOMPS_H
#define DECOMPS_H

const int decomps_len[] = {0, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 1, 1, 3, 2, 2, 2, 2, 1, 1, 3, 2, 2, 2, 1, 2, 2, 1, 3, 4, 2, 3, 2, 2, 2, 1, 1, 3, 4, 2, 3, 2, 2, 1, 2, 4, 2, 3, 2, 4, 3, 1, 3, 3, 1, 2, 4, 3, 4, 1, 2, 4, 2, 3, 3, 3, 2, 2, 3, 4, 4, 3, 2, 3, 3, 1, 3, 5, 2, 3, 4, 3, 3, 1, 2, 6, 4, 1, 4, 3, 2, 1, 4, 4, 4, 5};
const int decomps[101][6][4] = {{},
{{1, 1, 1, 1}}, // 1
{{0, 0, 2, 2}}, // 2
{{1, 1, 1, 3}}, // 3
{{0, 0, 0, 4}, {2, 2, 2, 2}}, // 4
{{1, 1, 3, 3}}, // 5
{{0, 2, 2, 4}}, // 6
{{1, 1, 1, 5}, {1, 3, 3, 3}}, // 7
{{0, 0, 4, 4}}, // 8
{{1, 1, 3, 5}}, // 9
{{0, 0, 2, 6}, {2, 2, 4, 4}}, // 10
{{1, 3, 3, 5}}, // 11
{{0, 4, 4, 4}, {2, 2, 2, 6}}, // 12
{{1, 1, 1, 7}, {1, 1, 5, 5}}, // 13
{{0, 2, 4, 6}}, // 14
{{1, 1, 3, 7}, {1, 3, 5, 5}}, // 15
{{0, 0, 0, 8}}, // 16
{{1, 3, 3, 7}}, // 17
{{0, 0, 6, 6}, {0, 2, 2, 8}, {2, 4, 4, 6}}, // 18
{{1, 1, 5, 7}, {1, 5, 5, 5}}, // 19
{{0, 0, 4, 8}, {2, 2, 6, 6}}, // 20
{{1, 1, 1, 9}, {1, 3, 5, 7}}, // 21
{{0, 4, 6, 6}, {2, 2, 4, 8}}, // 22
{{1, 1, 3, 9}}, // 23
{{0, 4, 4, 8}}, // 24
{{1, 1, 7, 7}, {1, 3, 3, 9}, {1, 5, 5, 7}}, // 25
{{0, 0, 2, 10}, {0, 2, 6, 8}}, // 26
{{1, 1, 5, 9}, {1, 3, 7, 7}}, // 27
{{2, 2, 2, 10}, {2, 6, 6, 6}}, // 28
{{1, 3, 5, 9}}, // 29
{{0, 2, 4, 10}, {2, 4, 6, 8}}, // 30
{{1, 1, 1, 11}, {1, 5, 7, 7}}, // 31
{{0, 0, 8, 8}}, // 32
{{1, 1, 3, 11}, {1, 1, 7, 9}, {1, 5, 5, 9}}, // 33
{{0, 0, 6, 10}, {0, 6, 6, 8}, {2, 2, 8, 8}, {2, 4, 4, 10}}, // 34
{{1, 3, 3, 11}, {1, 3, 7, 9}}, // 35
{{0, 0, 0, 12}, {0, 4, 8, 8}, {2, 2, 6, 10}}, // 36
{{1, 1, 5, 11}, {1, 7, 7, 7}}, // 37
{{0, 2, 2, 12}, {0, 4, 6, 10}}, // 38
{{1, 3, 5, 11}, {1, 5, 7, 9}}, // 39
{{0, 0, 4, 12}}, // 40
{{1, 1, 9, 9}}, // 41
{{0, 2, 8, 10}, {2, 2, 4, 12}, {2, 6, 8, 8}}, // 42
{{1, 1, 1, 13}, {1, 1, 7, 11}, {1, 3, 9, 9}, {1, 5, 5, 11}}, // 43
{{0, 4, 4, 12}, {2, 6, 6, 10}}, // 44
{{1, 1, 3, 13}, {1, 3, 7, 11}, {1, 7, 7, 9}}, // 45
{{0, 2, 6, 12}, {2, 4, 8, 10}}, // 46
{{1, 3, 3, 13}, {1, 5, 9, 9}}, // 47
{{0, 8, 8, 8}}, // 48
{{1, 1, 5, 13}, {1, 5, 7, 11}}, // 49
{{0, 0, 2, 14}, {0, 0, 10, 10}, {0, 6, 8, 10}, {2, 4, 6, 12}}, // 50
{{1, 1, 9, 11}, {1, 3, 5, 13}}, // 51
{{0, 0, 8, 12}, {2, 2, 2, 14}, {2, 2, 10, 10}}, // 52
{{1, 3, 9, 11}, {1, 7, 9, 9}}, // 53
{{0, 2, 4, 14}, {0, 4, 10, 10}, {0, 6, 6, 12}, {2, 2, 8, 12}}, // 54
{{1, 1, 7, 13}, {1, 5, 5, 13}, {1, 7, 7, 11}}, // 55
{{0, 4, 8, 12}}, // 56
{{1, 1, 1, 15}, {1, 3, 7, 13}, {1, 5, 9, 11}}, // 57
{{0, 0, 6, 14}, {2, 4, 4, 14}, {2, 8, 8, 10}}, // 58
{{1, 1, 3, 15}}, // 59
{{2, 2, 6, 14}, {2, 6, 10, 10}}, // 60
{{1, 1, 11, 11}, {1, 3, 3, 15}, {1, 5, 7, 13}, {1, 9, 9, 9}}, // 61
{{0, 2, 10, 12}, {0, 4, 6, 14}, {2, 6, 8, 12}}, // 62
{{1, 1, 5, 15}, {1, 1, 9, 13}, {1, 3, 11, 11}, {1, 7, 9, 11}}, // 63
{{0, 0, 0, 16}}, // 64
{{1, 3, 5, 15}, {1, 3, 9, 13}}, // 65
{{0, 2, 2, 16}, {0, 2, 8, 14}, {0, 8, 10, 10}, {2, 4, 10, 12}}, // 66
{{1, 5, 11, 11}, {1, 7, 7, 13}}, // 67
{{0, 0, 4, 16}, {0, 8, 8, 12}, {2, 6, 6, 14}}, // 68
{{1, 1, 7, 15}, {1, 5, 5, 15}, {1, 5, 9, 13}}, // 69
{{0, 6, 10, 12}, {2, 2, 4, 16}, {2, 4, 8, 14}}, // 70
{{1, 3, 7, 15}, {1, 9, 9, 11}}, // 71
{{0, 0, 12, 12}, {0, 4, 4, 16}}, // 72
{{1, 1, 1, 17}, {1, 1, 11, 13}, {1, 7, 11, 11}}, // 73
{{0, 0, 10, 14}, {0, 2, 6, 16}, {0, 6, 8, 14}, {2, 2, 12, 12}}, // 74
{{1, 1, 3, 17}, {1, 3, 11, 13}, {1, 5, 7, 15}, {1, 7, 9, 13}}, // 75
{{0, 4, 12, 12}, {2, 2, 10, 14}, {2, 10, 10, 10}}, // 76
{{1, 1, 9, 15}, {1, 3, 3, 17}}, // 77
{{0, 4, 10, 14}, {2, 4, 6, 16}, {2, 8, 10, 12}}, // 78
{{1, 1, 5, 17}, {1, 3, 9, 15}, {1, 5, 11, 13}}, // 79
{{0, 0, 8, 16}}, // 80
{{1, 3, 5, 17}, {1, 7, 7, 15}, {1, 9, 11, 11}}, // 81
{{0, 0, 2, 18}, {0, 6, 6, 16}, {2, 2, 8, 16}, {2, 6, 12, 12}, {2, 8, 8, 14}}, // 82
{{1, 5, 9, 15}, {1, 9, 9, 13}}, // 83
{{0, 4, 8, 16}, {2, 2, 2, 18}, {2, 6, 10, 14}}, // 84
{{1, 1, 7, 17}, {1, 1, 13, 13}, {1, 5, 5, 17}, {1, 7, 11, 13}}, // 85
{{0, 2, 4, 18}, {0, 2, 12, 14}, {0, 10, 10, 12}}, // 86
{{1, 1, 11, 15}, {1, 3, 7, 17}, {1, 3, 13, 13}}, // 87
{{0, 8, 12, 12}}, // 88
{{1, 3, 11, 15}, {1, 7, 9, 15}}, // 89
{{0, 0, 6, 18}, {0, 2, 10, 16}, {0, 8, 10, 14}, {2, 4, 4, 18}, {2, 4, 12, 14}, {2, 6, 8, 16}}, // 90
{{1, 1, 1, 19}, {1, 5, 7, 17}, {1, 5, 13, 13}, {1, 11, 11, 11}}, // 91
{{2, 2, 6, 18}}, // 92
{{1, 1, 3, 19}, {1, 1, 9, 17}, {1, 5, 11, 15}, {1, 9, 11, 13}}, // 93
{{0, 4, 6, 18}, {0, 6, 12, 14}, {2, 4, 10, 16}}, // 94
{{1, 3, 3, 19}, {1, 3, 9, 17}}, // 95
{{0, 8, 8, 16}}, // 96
{{1, 1, 5, 19}, {1, 7, 7, 17}, {1, 7, 13, 13}, {1, 9, 9, 15}}, // 97
{{0, 0, 14, 14}, {0, 2, 8, 18}, {0, 6, 10, 16}, {2, 10, 12, 12}}, // 98
{{1, 1, 13, 15}, {1, 3, 5, 19}, {1, 5, 9, 17}, {1, 7, 11, 15}}, // 99
{{0, 0, 0, 20}, {0, 0, 12, 16}, {2, 2, 14, 14}, {2, 6, 6, 18}, {2, 10, 10, 14}} // 100
};

#endif