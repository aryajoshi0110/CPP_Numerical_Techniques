#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

long double f ( long double x )
{
    return x - sin(2*x);
}
long double f_prime ( long double x )
{
    return 1 - 2*cos(2*x);
}

int main()
{
    // The equation is x - sin(2*x) = 0
    long double x_0 = 2 , x_1 = 0 ;
    x_1 = x_0 - f(x_0)/f_prime(x_0);
    long double epsilon = pow(10,-18);
    while ( abs(x_1 - x_0) > epsilon )
    {
        x_0 = x_1;
        x_1 = x_0 - f(x_0)/f_prime(x_0);
    }
    cout << fixed << setprecision(18);
    cout << "The length of chord AB is : " << 2*x_1 << endl;
    return 0;
}