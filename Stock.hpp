
#ifndef Stock_hpp
#define Stock_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Operator Overload.hpp"

using namespace std;

class Stock
{
private:
    string ticker;
    string day0;
    string EPSEstimate;
    string actualEarning;
    string surprise;
    string group;
    string startDate;
    string endDate;
    vector<double> price;
    vector<double> AbRet;
    vector<double> CumAbRet;

public:
    Stock() {}
    
    Stock (string ticker_, string day0_, string EPSEstimate_, string actualEarning_, string surprise_, string group_, vector<string> &tradingCalendar);
    
    vector<string> GetStartEndDates();
    
    void SetPrice (vector<double> &price_) { price = price_; }
    
    vector<double> GetAbRet() {return AbRet;}
    
    vector<double> GetCumAbRet() {return CumAbRet;}
    
    void GetStockInfo();
    
    int GetPriceSize() { return int(price.size()); }
    
    void CalculateAbRet(vector<string> &tradingCalendar, map<string, double> &SPYData);
    
    void CalculateCumAbRet();
    
};


#endif /* Stock_hpp */

