
#ifndef Return_Calculation_hpp
#define Return_Calculation_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include "Stock.hpp"
#include "Operator Overload.hpp"

// Given a Map, this function calculates the Abnomral Return & Cumulative Abnormal Return for each stock in the map
void CalculateAbRetAndCumAbRet(map<string, Stock> &myMap, vector<string> &tradingCalendar, map<string, double> &SPYData);

// Conduct Bootstrapping and calculate AAR & CAAR for each group
void AAR_and_CAAR (map<string, Stock> &myMap, vector<string> &stockList, vector<double> &AAR_Group, vector<double> &CAAR_Group);

#endif /* Return_Calculation_hpp */

