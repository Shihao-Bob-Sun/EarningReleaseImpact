
#include <thread>
#include "Data Preparation.hpp"
#include "SimpleCurl.hpp"
#include "Return Calculation.hpp"
#include "Gnuplot.hpp"
#include <chrono>
#include <ctime>
#include <cstdlib>

using get_time = chrono::steady_clock;


int main()
{
    srand((unsigned int)time(NULL));
    
    vector<string> tradingCalendar;
    map<string, double> SPYData;
    
    ifstream myFile1("SPY.csv");
    GetSPYDataAndTradingCal(&myFile1, tradingCalendar, SPYData);
    
    // Creat maps for each group
    map<string, Stock> Beat, Meet, Miss;
    
    ifstream myFile2("Bloomberg_EPS.csv");
    PopulateMap(&myFile2, tradingCalendar, Beat, Meet, Miss);
    
    vector<string> symbolList;
    vector<string> BeatStock, MeetStock, MissStock;
    
    vector<double> AAR_Beat, AAR_Meet, AAR_Miss;
    vector<double> CAAR_Beat, CAAR_Meet, CAAR_Miss;
    
    // Creat result Matrix with rows being groups (Beat, Meet, Miss) and columns being AAR and CAAR
    vector<vector<vector<double>>> AAR_CAAR_Matrix(3);
 
    bool WantToExit = false;
    bool DataIsRetrived = false;
    
    int Option;
    
    do {
        cout << "====================== MENU of OPTIONS ======================" << endl << endl;
        cout << "1. Retrieve historical price data for all stocks" << endl;
        cout << "2. Pull information for one stock from one group" << endl;
        cout << "3. Show AAR or CAAR for one Group" << endl;
        cout << "4. Show the Gnuplot graph with CAAR for all 3 groups" << endl;
        cout << "5. Exit your program" << endl << endl;
        cout << "Please enter a number from 1 to 5: ";
        
        cin >> Option;
        
        if (cin.fail())
        {
            cout << endl;
            cout << "# Please enter a VALID number (from 1 to 5). #" << endl << endl;
            cin.clear(); cin.ignore(100, '\n');
            continue;
        }
        
        switch (Option)
        {
            case 1:
            {
                if (DataIsRetrived)
                {
                    cout << endl;
                    cout << "# Historical price data has already been retrieved. #" << endl << endl;
                    break;
                }
                else {
                    cout << "    ";
                    
                    auto start= get_time::now(); //use auto keyword to minimize typing strokes
                    
                  /*Code without using Multithread
                    GetPriceData_Libcurl(Beat, Beat.begin(), Beat.end());
                    GetPriceData_Libcurl(Meet, Meet.begin(), Meet.end());
                    GetPriceData_Libcurl(Miss, Miss.begin(), Miss.end());
                   */
                    
                    // Multithreading (Fetch data from Yahoo Finance)
                    thread BeatMap(GetPriceData_Libcurl, ref(Beat), Beat.begin(), Beat.end());
                    thread MeetMap(GetPriceData_Libcurl, ref(Meet), Meet.begin(), Meet.end());
                    thread MissMap(GetPriceData_Libcurl, ref(Miss), Miss.begin(), Miss.end());
                    
                    BeatMap.join();
                    MeetMap.join();
                    MissMap.join();
                    
                    auto end = get_time::now();
                    auto diff = end - start;
                    
                    cout << endl << endl;
                    cout << "# Historical Data Retrieve Done. #" << endl << endl;
                    cout<< "# Elapsed time is: "<< chrono::duration_cast<std::chrono::seconds>(diff).count()<<" sec #"<< endl << endl;
                    
                    DataIsRetrived = true;
                    
                    // Remove the stock with less than 121 days price data
                    CleanMap(Beat, Meet, Miss, BeatStock, MeetStock, MissStock, symbolList);
                    
                    // Calculate daily abnormal return and cumulative abnormal return for each stock
                    CalculateAbRetAndCumAbRet(Beat, tradingCalendar, SPYData);
                    CalculateAbRetAndCumAbRet(Meet, tradingCalendar, SPYData);
                    CalculateAbRetAndCumAbRet(Miss, tradingCalendar, SPYData);
                    
                    // Conduct Bootstrapping to calculate AAR & CAAR for each group
                    AAR_and_CAAR (Beat, BeatStock, AAR_Beat, CAAR_Beat);
                    AAR_and_CAAR (Meet, MeetStock, AAR_Meet, CAAR_Meet);
                    AAR_and_CAAR (Miss, MissStock, AAR_Miss, CAAR_Miss);
                    
                    // Populate Result Matrix with rows being groups (Beat, Meet, Miss) and colums being AAR and CAAR
                    AAR_CAAR_Matrix[0].push_back(AAR_Beat);
                    AAR_CAAR_Matrix[0].push_back(CAAR_Beat);
                    AAR_CAAR_Matrix[1].push_back(AAR_Meet);
                    AAR_CAAR_Matrix[1].push_back(CAAR_Meet);
                    AAR_CAAR_Matrix[2].push_back(AAR_Miss);
                    AAR_CAAR_Matrix[2].push_back(CAAR_Miss);
                    
                    break;
                }
            }
            
    
            case 2:
            {
                cout << endl;
                string stockChoice;
                map<string, Stock>::iterator itr;
                
                if (!DataIsRetrived)
                {
                    cout << "# You have to retrieve historical data FIRST. Please enter 1. #" << endl << endl;
                    break;
                }
                else {
                    cout << "Please enter a stock ticker: ";
                    cin >> stockChoice;
                    
                    while (find(symbolList.begin(), symbolList.end(), stockChoice) == symbolList.end())
                    {
                        cout << endl;
                        cout << "# Stock not found. #" << endl << endl;
                        cout << "Please pick a stock ticker from following tickers: " << endl;
                        cout << symbolList << endl << endl;
                        cout << "Please enter a stock ticker: ";
                        cin >> stockChoice;
                    }
                    
                    // Find which group the stock lies in and print the stock info
                    if (Beat.find(stockChoice) != Beat.end()) {Beat[stockChoice].GetStockInfo(); break;}
                    if (Meet.find(stockChoice) != Meet.end()) {Meet[stockChoice].GetStockInfo(); break;}
                    if (Miss.find(stockChoice) != Miss.end()) {Miss[stockChoice].GetStockInfo(); break;}
                }
            }
                
            
            case 3:
            {
                cout << endl;
                if (!DataIsRetrived)
                {
                    cout << "# You have to retrieve historical data FIRST. Please enter 1. #" << endl << endl;
                    break;
                }
                else {
                    int group;
                    int AAR_or_CAAR;
                    
                    cout << "Please choice a group (1 for Beat, 2 for Meet, 3 for Miss): ";
                    cin >> group;
                    while (((group != 1) and (group != 2) and (group != 3)) or (cin.fail()))
                    {
                        cout << endl;
                        cout << "# Please enter a VALID number. #" << endl << endl;
                        cout << "Please choice a group (1 for Beat, 2 for Meet, 3 for Miss): ";
                        cin.clear(); cin.ignore(100, '\n');
                        cin >> group;
                    }
                    
                    cout << endl;
                    cout << "Please choice AAR or CAAR (1 for AAR, 2 for CAAR): ";
                    cin >> AAR_or_CAAR;
                    while (((AAR_or_CAAR != 1) and (AAR_or_CAAR != 2)) or (cin.fail()))
                    {
                        cout << endl;
                        cout << "# Please enter a VALID number. #" << endl << endl;
                        cout << "Please choice AAR or CAAR (1 for AAR, 2 for CAAR): ";
                        cin.clear(); cin.ignore(100, '\n');
                        cin >> AAR_or_CAAR;
                    }
                    
                    // Print the corresponding AAR or CAAR
                    cout << AAR_CAAR_Matrix[group-1][AAR_or_CAAR-1] << endl << endl;
                    break;
                }
            }
                
                
            case 4:
            {
                if (!DataIsRetrived)
                {
                    cout << endl;
                    cout << "# You have to retrieve historical data FIRST. Please enter 1. #" << endl << endl;
                    break;
                }
                else {
                    // Plot the result
                    PlotResults(CAAR_Beat, CAAR_Meet, CAAR_Miss);
                    cout << endl;
                    break;
                }
            }
            
            
            case 5:
            {
                WantToExit = true;
                break;
            }
                
                
            default:
            {
                cout << endl;
                cout << "# Please enter a VALID number (from 1 to 5). #" << endl << endl;
                break;
            }
        }
        
    } while (!WantToExit);
    
    cout << endl;
    cout << "# Thank You! #" << endl << endl;
    
    return 0;
}
