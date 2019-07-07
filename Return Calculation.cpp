
#include "Return Calculation.hpp"

// Given a Map, this function calculates the Abnomral Return & Cumulative Abnormal Return for each stock in the map
void CalculateAbRetAndCumAbRet (map<string, Stock> &myMap, vector<string> &tradingCalendar, map<string, double> &SPYData)
{
    map<string, Stock>::iterator itr = myMap.begin();
    
    for (; itr != myMap.end(); itr++)
    {
        (itr->second).CalculateAbRet(tradingCalendar, SPYData);
        (itr->second).CalculateCumAbRet();
    }
    
}


// Conduct Bootstrapping and calculate AAR & CAAR for each group
void AAR_and_CAAR (map<string, Stock> &myMap, vector<string> &stockList, vector<double> &AAR_Group, vector<double> &CAAR_Group)
{
    //srand((unsigned int)time(NULL));
    
    vector<double> AAR, CAAR;
    
    vector<int> sampleList;
    int index;
    
    // Bootstrapping for 30 times
    for (int i = 0; i < 30; i++)
    {
        // Randomly pick 30 stocks from the group
        for (int j = 0; j < 30; )
        {
            index = rand()%stockList.size();
            
            if (find(sampleList.begin(), sampleList.end(), index) == sampleList.end())
            {
                sampleList.push_back(index);
                j++;
            }
        }
        
        // Compute the AAR for this sample (30 randomly picked stocks)
        for (int k = 0; k < sampleList.size(); k++)
        {
            AAR = k/(k+1.0) * AAR + myMap[stockList[sampleList[k]]].GetAbRet()/(k+1.0);
            CAAR = k/(k+1.0) * CAAR + myMap[stockList[sampleList[k]]].GetCumAbRet()/(k+1.0);
        }
        
        AAR_Group = i/(i+1.0) * AAR_Group + 1/(i+1.0) * AAR;
        CAAR_Group = i/(i+1.0) * CAAR_Group + 1/(i+1.0) * CAAR;
        
        AAR.clear();
        CAAR.clear();
        sampleList.clear();
        
    }
    
}

