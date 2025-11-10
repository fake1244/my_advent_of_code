#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_2.h"
#include "file_utils.h"

using namespace std;

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

vector<vector<int>> AocDay2::read_input(string filename)
{
    FileUtils fileutils;
    vector<vector<string>> raw_lines;
    vector<vector<int>> reports;
    if (!fileutils.read_as_list_of_split_strings(filename, raw_lines, ' ', '"', '#'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return reports;
    }

    for (auto raw_line : raw_lines){
        vector<int> line;

        for (auto raw_value : raw_line)
            line.push_back(stoi(raw_value));
        
        reports.push_back(line);
    }

    return reports;
}

bool AocDay2::is_report_safe(vector<int> report){
    bool increasing { report[0] < report[1] };
    int previous_level { report[0] };

    for (auto it = report.begin() + 1; it != report.end(); ++it){
        auto level = *it;
        auto difference = abs(level - previous_level);

        if(difference == 0 || difference > 3)
            return false;

        if(increasing && level < previous_level)
            return false;

        if(!increasing && level > previous_level)
            return false;

        previous_level = level;
    }
    return true;
}

string AocDay2::part1(string filename, vector<string> extra_args)
{
    vector<vector<int>> data = read_input(filename);
    int safe_reports { 0 };

    for(auto report : data){
        bool is_safe = is_report_safe(report);

        if (is_safe)
            ++safe_reports;
    }

    return to_string(safe_reports);
}

string AocDay2::part2(string filename, vector<string> extra_args)
{
    vector<vector<int>> data = read_input(filename);
    int safe_reports { 0 };

    for(auto report : data){
        bool is_safe = is_report_safe(report);

        if (is_safe){
            ++safe_reports;
            continue;
        }

        for(size_t i {}; i < report.size(); ++i){
            vector<int> modified_report = report;
            modified_report.erase(modified_report.begin() + i);

            if (is_report_safe(modified_report)){
                ++safe_reports;
                break;
            }
        }
    }

    return to_string(safe_reports);
}
