#ifndef __AOC_DAY_4__
#define __AOC_DAY_4__

#include "aoc_day.h"

class AocDay4 : public AocDay
{
    private:
        vector<vector<char>> read_input(string filename);
        int count_horizontal(vector<vector<char>> data);
        int count_vertical(vector<vector<char>> data);
        int count_diagonal(vector<vector<char>> data);
        bool is_xmas(char c1, char c2, char c3, char c4);
    public:
        AocDay4();
        ~AocDay4();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
