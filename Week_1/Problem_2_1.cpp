#include<iostream>
using namespace std;

double f ( double x )
{
    return x*x - 8*x + 11;
}
double f_prime ( double x )
{
    return 2*x - 8;
}

int main()
{
    double x_0 = 6 , x_1 = 0 ;
    x_1 = x_0 - f(x_0)/f_prime(x_0);
    double epsilon = 0.000001;
    while ( abs(x_1 - x_0) > epsilon )
    {
        x_0 = x_1;
        x_1 = x_0 - f(x_0)/f_prime(x_0);
    } 

    cout << "The root of the equation is : " << x_1 << endl;
    return 0;
}