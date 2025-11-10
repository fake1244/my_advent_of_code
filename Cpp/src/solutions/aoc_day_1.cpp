#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_1.h"
#include "file_utils.h"

using namespace std;

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

vector<vector<int>> AocDay1::read_input(string filename)
{
    FileUtils fileutils;
    vector<vector<string>> raw_lines;
    vector<vector<int>> columns;
    if (!fileutils.read_as_list_of_split_strings(filename, raw_lines, ' ', '"', '#'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return columns;
    }

    vector<int> c1;
    vector<int> c2;
    for (auto line: raw_lines)
    {
        c1.push_back(stoi(line[0]));
        c2.push_back(stoi(line[3]));
    }

    columns.push_back(c1);
    columns.push_back(c2);
    
    return columns;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
    vector<vector<int>> data = read_input(filename);
    long difference = 0;

    sort(data[0].begin(), data[0].end());
    sort(data[1].begin(), data[1].end());

    for(size_t i {}; i < data[0].size() && i < data[1].size(); ++i){
        difference += abs(data[0][i] - data[1][i]);
    }

    return to_string(difference);
}

string AocDay1::part2(string filename, vector<string> extra_args)
{
    vector<vector<int>> data = read_input(filename);
    long sim_score = 0;

    for(auto n : data[0]){
        sim_score += n * count(data[1].begin(), data[1].end(), n);
    }

    return to_string(sim_score);
}
