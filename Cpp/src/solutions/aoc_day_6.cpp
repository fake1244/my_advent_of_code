#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_6.h"
#include "file_utils.h"

using namespace std;

AocDay6::AocDay6():AocDay(0)
{
}

AocDay6::~AocDay6()
{
}

vector<vector<char>> AocDay6::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<vector<char>> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        vector<char> line;
        for(char c : *iter)
            line.push_back(c);

        data.push_back(line);
    }
    return data;
}

pair<size_t, size_t> getStartPoint(vector<vector<char>>& data){
    for(auto i { 0 }; i < data.size(); ++i)
        for(auto j { 0 }; j < data[0].size(); ++j)
            if(data[i][j] == '^'){
                data[i][j] = 'X';
                return {i, j};
            }

    return {-1, -1};
}

bool fillPath(vector<vector<char>>& data, int startRow, int startCol, int dr, int dc){
    bool change { false };
    auto i { startRow };
    auto j { startCol };
    auto c { 0 };
    while(0 <= i + dr && i + dr < data.size() && 0 <= j + dc && j + dc < data[0].size())
    {
        if(c > 9999)
            return true;

        if(data[i + dr][j + dc] == '#' || data[i + dr][j + dc] == 'O'){
            // cout << "Print: \n";
            // for(auto i { 0 }; i < data.size(); ++i){
            //     for(auto j { 0 }; j < data[0].size(); ++j)
            //         cout << data[i][j];        
            //     cout << '\n';
            // }
            // if(change)
            //     return fillPath(data, i, j, dc , -dr);
            
            // if(startRow == i && startCol == j)
            //     return fillPath(data, i, j, dc , -dr);
            // return true;
            if(change){
                auto oldDr = dr;
                dr = dc;
                dc = -oldDr;
                continue;
            }
        }
        
        if(data[i + dr][j + dc] == '.'){
            change = true;
            data[i + dr][j + dc] = 'X';
        }

        i += dr;
        j += dc;
        ++c;
    }

    return false;
}

int countData(vector<vector<char>>& data){
    int sum { 0 };

    for(auto i { 0 }; i < data.size(); ++i)
        for(auto j { 0 }; j < data[0].size(); ++j)
            if(data[i][j] == 'X')
                ++sum;
    return sum;
}

string AocDay6::part1(string filename, vector<string> extra_args)
{
    vector<vector<char>> data = read_input(filename);
    pair<size_t, size_t> startPoint = getStartPoint(data);

    fillPath(data, startPoint.first, startPoint.second, -1, 0);

    // cout << "Print: \n";
    // for(auto i { 0 }; i < data.size(); ++i){
    //     for(auto j { 0 }; j < data[0].size(); ++j)
    //         cout << data[i][j];        
    //     cout << '\n';
    // }

    return std::to_string(countData(data));
}

string AocDay6::part2(string filename, vector<string> extra_args)
{
    vector<vector<char>> data = read_input(filename);
    pair<size_t, size_t> startPoint = getStartPoint(data);

    int possibleLoops { 0 };

    for(auto i { 0 }; i < data.size(); ++i)
        for(auto j { 0 }; j < data[0].size(); ++j){
            if(data[i][j] == '#' || (i == startPoint.first && j == startPoint.second))
                continue;
            
                auto newData = data;
            newData[i][j] = 'O';

            auto inLoop = fillPath(newData, startPoint.first, startPoint.second, -1, 0);

            if(inLoop){
                // cout << "Print: " << inLoop << "\n";
                // for(auto i { 0 }; i < newData.size(); ++i){
                //     for(auto j { 0 }; j < newData[0].size(); ++j)
                //         cout << newData[i][j];        
                //     cout << '\n';
                // }
                ++possibleLoops;
            }
        }

    // cout << "Print: \n";
    // for(auto i { 0 }; i < data.size(); ++i){
    //     for(auto j { 0 }; j < data[0].size(); ++j)
    //         cout << data[i][j];        
    //     cout << '\n';
    // }

    return std::to_string(possibleLoops);
}
