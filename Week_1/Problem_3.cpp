#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f ( double x )
{
    return pow(M_E,2*x) + x - 5;
}

int main()
{
    // Secant Method
    double x_0 = 0 , x_1 = 1 ;
    double eps = 0.000001;
    while ( abs(x_1-x_0) > eps)
    {
        double x_temp = x_1 - f(x_1)*(x_1-x_0)/(f(x_1)-f(x_0));
        x_0 = x_1;
        x_1 = x_temp;
    }
    cout << fixed << setprecision(10);
    cout << "The root of the equation is : " << x_1 << endl;
    return 0;
}