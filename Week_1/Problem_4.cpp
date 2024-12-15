#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double f(double x, double y)
{
    return x*x*x*exp(-2*x) - 2*y;
}
double given_f (double x)
{
    return 0.25*exp(-2*x)*(pow(x,4)+4);
}

int main()
{
    // y' + 2y = x**3 * e**(-2x) , y(0) = 1
    // Euler's method
    double x0 = 0, y0 = 1, h = 0.025;
    int n = 1/h + 1;
    double x[n] , y[n], y_actual[n];
    x[0] = x0;
    y[0] = y0;
    for (int i = 0; i < n; i++)
    {
        x[i+1] = x[i] + h;
        y[i+1] = y[i] + h*f(x[i], y[i]);
    }
    for (int i = 0; i < n; i++)
    {
        y_actual[i] = given_f(x[i]);
    }

    cout << "#x y y_actual" << endl;
    cout << fixed << setprecision(6);

    for (int i = 0; i < n; i++)
    {
        cout << x[i] << " " << y[i] << " " << y_actual[i] << endl;
    }

    // for (int i = 0; i < n; i++)
    // {
    //     cout << x[i] << ", " ;
    // }
    // cout << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << y[i] << ", " ;
    // }
    // cout << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << y_actual[i] << ", " ;
    // }
    

    return 0;
}