#ifndef __AOC_DAY_5__
#define __AOC_DAY_5__

#include "aoc_day.h"

class AocDay5 : public AocDay
{
    private:
        pair<map<int, vector<int>>, vector<vector<int>>> read_input(string filename);
        vector<int> split_to_int(const string& s, const string& delimiter);
    public:
        AocDay5();
        ~AocDay5();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
