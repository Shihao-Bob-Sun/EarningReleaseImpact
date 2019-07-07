
#include "Stock.hpp"

// Constructor with parameter
Stock:: Stock(string ticker_, string day0_, string EPSEstimate_, string actualEarning_, string surprise_, string group_, vector<string> &tradingCalendar)
{
    ticker = ticker_;
    day0 = day0_;
    EPSEstimate = EPSEstimate_;
    actualEarning = actualEarning_;
    surprise = surprise_;
    group = group_;
    
    auto it = find(tradingCalendar.begin(), tradingCalendar.end(), day0);
    if (it != tradingCalendar.end())
    {
        it -= 60;
    }
    else {
        cout << "Cannot find Day 0 in the calendar.";
    }
    startDate = *it;
    
    it = find(tradingCalendar.begin(), tradingCalendar.end(), day0);
    it += 60;
    endDate = *it;
}


vector<string> Stock:: GetStartEndDates ()
{
    vector<string> startEndDates;
    startEndDates.push_back(startDate);
    startEndDates.push_back(endDate);
    return startEndDates;
}


// Calculate daily Abnormal Return
void Stock:: CalculateAbRet(vector<string> &tradingCalendar, map<string, double> &SPYData)
{
    auto it = find(tradingCalendar.begin(), tradingCalendar.end(), startDate);
    it++;
    
    string date;
    
    double dailyReturn;
    double abnormalReturn;
    
    for (int i = 1; i < price.size(); i++)
    {
        date = *it;
        dailyReturn = (price[i]-price[i-1])/(price[i-1])*100;
        abnormalReturn = (dailyReturn - SPYData[date])/100.0;
        
        AbRet.push_back(abnormalReturn);
        
        it++;
    }
}


// Calculate daily Cumulative Abnormal Return
void Stock:: CalculateCumAbRet()
{
    double CummulativeAbRet = AbRet[0];
    CumAbRet.push_back(CummulativeAbRet);
    
    for (int i = 1; i < AbRet.size(); i++)
    {
        CummulativeAbRet += AbRet[i];
        CumAbRet.push_back(CummulativeAbRet);
    }
}


// Print stock information
void Stock:: GetStockInfo()
{
    cout << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Below is the Stock Info:" << endl << endl;
    cout << "Ticker:         " << ticker << endl;
    cout << "Group:          " << group << endl << endl;
    cout << "Actual Earning: " << actualEarning << endl;
    cout << "EPS Estimate:   " << EPSEstimate << endl;
    cout << "Surprise:       " << surprise << endl << endl;
    cout << "Day 0:                     " << day0 << endl;
    cout << "Start of 121 Trading Days: " << startDate << endl;
    cout << "End of 121 Trading Days:   " << endDate << endl << endl;
    cout << "121-Day Prices: " << endl << price << endl << endl;
    cout << "120-Day Daily Abnormal Return: " << endl << AbRet << endl << endl;
    cout << "120-Day Daily Cummulative Abnormal Return: " << endl << CumAbRet << endl << endl;
}

