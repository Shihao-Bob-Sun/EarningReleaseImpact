
#include "Data Preparation.hpp"

// Load trading calendar from .csv file and populate the date-return map for SPY
int GetSPYDataAndTradingCal (ifstream *File, vector<string>& tradingCalendar, map<string, double>& SPYData)
{
    string line;
    string date;
    string return_str;
    double return_double;
    
    while((*File).good())
    {
        getline(*File, line);
        
        line = line.erase(line.size()-1);
        date = line.substr(0,line.find_first_of(','));
        return_str = line.substr(line.find_last_of(',')+1);
        
        try {
            return_double = stod(return_str);
        }
        catch (...) {
            continue;
        }
        
        tradingCalendar.push_back(date);
        SPYData[date] = return_double;
    }
    return 1;
}


// Populate the map for Beat, Meet, and Miss group
int PopulateMap (ifstream *File, vector<string> &tradingCalendar, map<string,Stock>& Beat, map<string,Stock>& Meet, map<string,Stock>& Miss)
{
    string line;
    string ticker;
    string group;
    string day0;
    string EPSEstimate;
    string actualEarning;
    string surprise;
    
    while((*File).good())
    {
        getline(*File, line);
        line = line.erase(line.size()-1);
        line = line.substr(line.find_first_of(',')+1);
        ticker = line.substr(0, line.find_first_of(','));
        
        line = line.substr(line.find_first_of(',')+1);
        
        day0 = line.substr(0, line.find_first_of(','));
        group = line.substr(line.find_last_of(',')+1);
        
        line = line.substr(line.find_first_of(',')+1);
        actualEarning = line.substr(0, line.find_first_of(','));
        
        line = line.substr(line.find_first_of(',')+1);
        EPSEstimate = line.substr(0, line.find_first_of(','));
        
        line = line.substr(line.find_first_of(',')+1);
        surprise = line.substr(0, line.find_first_of(','));
        
        if (group == "Group")
        {
            continue;
        }
        
        if (group == "Beat")
        {
            Beat[ticker] = Stock(ticker, day0, EPSEstimate, actualEarning, surprise, group, tradingCalendar);
        }
        
        if (group == "Meet")
        {
            Meet[ticker] = Stock(ticker, day0, EPSEstimate, actualEarning, surprise, group, tradingCalendar);
        }
        
        if (group == "Miss")
        {
            Miss[ticker] = Stock(ticker, day0, EPSEstimate, actualEarning, surprise, group, tradingCalendar);
        }
        
    }
    
    return 1;
}


// Clean the map by removing the stock with less than 121 days price data
void CleanMap (map<string, Stock> &Beat, map<string, Stock> &Meet, map<string, Stock> &Miss,
               vector<string> &BeatStock, vector<string> &MeetStock, vector<string> &MissStock, vector<string> &symbolList)
{
    vector<string> deletList;
    
    for (map<string, Stock>::iterator itr = Beat.begin(); itr != Beat.end(); itr++)
    {
        if (itr->second.GetPriceSize() < 121)
        {
            deletList.push_back(itr->first);
        } else
        {
            BeatStock.push_back(itr->first);
            symbolList.push_back(itr->first);
        }
    }
    for (int i = 0; i < deletList.size(); i++)
    {
        Beat.erase(deletList[i]);
    }
    
    
    deletList.clear();
    for (map<string, Stock>::iterator itr = Meet.begin(); itr != Meet.end(); itr++)
    {
        if (itr->second.GetPriceSize() < 121)
        {
            deletList.push_back(itr->first);
        } else
        {
            MeetStock.push_back(itr->first);
            symbolList.push_back(itr->first);
        }
    }
    for (int i = 0; i < deletList.size(); i++)
    {
        Meet.erase(deletList[i]);
    }
    
    
    deletList.clear();
    for (map<string, Stock>::iterator itr = Miss.begin(); itr != Miss.end(); itr++)
    {
        if (itr->second.GetPriceSize() < 121)
        {
            deletList.push_back(itr->first);
        } else
        {
            MissStock.push_back(itr->first);
            symbolList.push_back(itr->first);
        }
    }
    for (int i = 0; i < deletList.size(); i++)
    {
        Miss.erase(deletList[i]);
    }
    
}
