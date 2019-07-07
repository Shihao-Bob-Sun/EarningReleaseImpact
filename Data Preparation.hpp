
#ifndef Data_Preparation_hpp
#define Data_Preparation_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Stock.hpp"

using namespace std;

// Load trading calendar from .csv file and populate the date-return map for SPY
int GetSPYDataAndTradingCal(ifstream *File, vector<string>& tradingCalendar, map<string, double>& SPYData);

// Populate the map for Beat, Meet, and Miss group
int PopulateMap (ifstream *File, vector<string> &tradingCalendar, map<string,Stock>& Beat, map<string,Stock>& Meet, map<string,Stock>& Miss);

// Clean the map by removing the stock with less than 121 days price data
void CleanMap (map<string, Stock> &Beat, map<string, Stock> &Meet, map<string, Stock> &Miss,
               vector<string> &BeatStock, vector<string> &MeetStock, vector<string> &MissStock, vector<string> &symbolList);

#endif /* Data_Preparation_hpp */


