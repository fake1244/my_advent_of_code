#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

class AocDay2 : public AocDay
{
    private:
        vector<vector<int>> read_input(string filename);
        bool is_report_safe(vector<int> report);
    public:
        AocDay2();
        ~AocDay2();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
