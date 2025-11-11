#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <regex>
#include <map>

#include "aoc_day_5.h"
#include "file_utils.h"

using namespace std;

AocDay5::AocDay5():AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

vector<int> AocDay5::split_to_int(const string& s, const string& delimiter) {
    vector<int> tokens;
    size_t last = 0; size_t next = 0; 
    while ((next = s.find(delimiter, last)) != string::npos) {  
        tokens.push_back(stoi(s.substr(last, next-last)));
        last = next + 1; 
    } 
    tokens.push_back(stoi(s.substr(last)));

    return tokens;
}

pair<map<int, vector<int>>, vector<vector<int>>> AocDay5::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    pair<map<int, vector<int>>, vector<vector<int>>> rules_and_reports {};
    map<int, vector<int>> rules {};
    vector<vector<int>> reports {};

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return rules_and_reports;
    }

    bool reading_rules { true };
    for (auto raw_line : raw_lines){
        if(raw_line.empty()){
            reading_rules = false;
            continue;
        }

        if(reading_rules){
            std::regex rule_regex(R"((\d+)\|(\d+))");
            auto rules_begin = std::sregex_iterator(raw_line.begin(), raw_line.end(), rule_regex);
            std::smatch match = *rules_begin;
            
            auto n1 = stoi(match[1].str());
            auto n2 = stoi(match[2].str());

            if(rules.find(n2) == rules.end())
                rules[n2] = vector<int> {};

            rules[n2].push_back(n1);
        }
        else{
            reports.push_back(split_to_int(raw_line, ","));
        }

    }

    rules_and_reports.first = rules;
    rules_and_reports.second = reports;
    return rules_and_reports;
}

bool is_valid(const vector<int>& report, const map<int, vector<int>>& rules)
{
    for(size_t i { }; i < report.size(); ++i){
        if(rules.find(report[i]) == rules.end())
            continue;

        auto numbers_before = rules.at(report[i]);
        for(auto n: numbers_before){
            auto it = find(report.begin(), report.end(), n);
            if (it == report.end()) 
                continue;

            int index_n = static_cast<int>(std::distance(report.begin(), it));

            if(index_n > i)
                return false;
        }
    }

    return true;
}

string AocDay5::part1(string filename, vector<string> extra_args)
{
    auto data = read_input(filename);
    auto rules = data.first;
    auto reports = data.second;
    auto sum { 0 };

    for(auto report : reports){
        if(is_valid(report, rules)){
            auto middle = report[report.size() / 2];
            sum += middle;
        }
    }

    return std::to_string(sum);
}

void fix_report(vector<int>& report, map<int, vector<int>>& rules){
    for(size_t i {}; i < report.size(); ++i){
        if(rules.find(report[i]) == rules.end())
            continue;

        auto numbers_before = rules.at(report[i]);
        for(auto n: numbers_before){
            auto it = find(report.begin(), report.end(), n);
            if (it == report.end()) 
                continue;

            int index_n = static_cast<int>(std::distance(report.begin(), it));

            if(index_n > i){
                std::swap(report[index_n], report[i]);
                return fix_report(report, rules);
            }
        }
    }
}

string AocDay5::part2(string filename, vector<string> extra_args)
{
    auto data = read_input(filename);
    auto rules = data.first;
    auto reports = data.second;
    auto sum { 0 };

    for(auto report : reports){
        if(!is_valid(report, rules)){
            cout << "Report: ";
            for(auto n: report)
                cout << to_string(n) << ", ";
            cout << endl;

            fix_report(report, rules);

            cout << "Fixed:  ";
            for(auto n: report)
                cout << to_string(n) << ", ";
            cout << endl;
            auto middle = report[report.size() / 2];
            sum += middle;
        }
    }

    return std::to_string(sum);
}
