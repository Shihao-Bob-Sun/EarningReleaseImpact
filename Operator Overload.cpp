
#include "Operator Overload.hpp"

Vector operator*(const double& a, const Vector& V)
{
    unsigned long d = V.size();
    Vector U(d);
    for (int j=0; j<d; j++)
    {
        U[j] = a*V[j];
    }
    return U;
}


Vector operator/(const Vector& V, const double& a)
{
    unsigned long d = V.size();
    Vector U(d);
    for (int j=0; j<d; j++)
    {
        U[j] = V[j]/a;
    }
    return U;
}


Vector operator+(const Vector& V, const Vector& W)
{
    unsigned long v = V.size();
    unsigned long w = W.size();
    if (v<=w)
    {
        Vector U = W;
        for (int i = 0; i < v; i++)
        {
            U[i] = U[i] + V[i];
        }
        return U;
    } else
    {
        Vector U = V;
        for (int i = 0; i < w; i++)
        {
            U[i] = U[i] + W[i];
        }
        return U;
    }
}


ostream & operator<<(ostream & out, Vector & V)
{
    for (int i = 0; i < V.size(); i++)
    {
        if (i%10 == 0)
        {
            cout << endl;
        }
        
        cout << setw(13) << setfill(' ') << setiosflags(ios::left) << V[i];
    }
    return out;
}


ostream & operator<<(ostream & out, vector<string> & V)
{
    for (int i = 0; i < V.size(); i++)
    {
        if (i%20 == 0)
        {
            cout << endl;
        }
        out << setw(6) << setfill(' ') << setiosflags(ios::left) << V[i];
    }
    return out;
}

