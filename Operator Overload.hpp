
#ifndef Operator_Overload_hpp
#define Operator_Overload_hpp

#include <vector>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

typedef vector<double> Vector;

Vector operator*(const double& a, const Vector& V);

Vector operator/(const Vector& V, const double& a);

Vector operator+(const Vector& V, const Vector& W);

ostream & operator<<(ostream & out, Vector & V);

ostream & operator<<(ostream & out, vector<string> & V);


#endif /* Operator_Overload_hpp */

