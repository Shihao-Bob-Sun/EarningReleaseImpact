
#ifndef LibCurl_hpp
#define LibCurl_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include "curl/curl.h"
#include <map>
#include "Stock.hpp"

using namespace std;

size_t write_data(void *ptr, int size, int nmemb, FILE *stream);

struct MemoryStruct {
    char *memory;
    size_t size;
};

void *myrealloc(void *ptr, size_t size);

size_t write_data2(void *ptr, size_t size, size_t nmemb, void *data);

string getTimeinSeconds(string Time);

// Fetch historical price data from Yahoo Finance
int GetPriceData_Libcurl(map<string, Stock> &myMap, map<string,Stock>::iterator start, map<string,Stock>::iterator end);

#endif /* LibCurl_hpp */

