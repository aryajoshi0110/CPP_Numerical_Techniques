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
    // Runge Kutta 4 Method
    double x0 = 0 , y0 = 1 , h = 0.1;
    int n = 1/h + 1;
    double x[n] , y[n], y_actual[n];
    x[0] = x0;
    y[0] = y0;
    for (int i = 0; i < n; i++)
    {
        x[i+1] = x[i] + h;
        double k1 = f(x[i], y[i]);
        double k2 = f(x[i] + h/2, y[i] + h*k1/2);
        double k3 = f(x[i] + h/2, y[i] + h*k2/2);
        double k4 = f(x[i] + h, y[i] + h*k3);
        y[i+1] = y[i] + h*(k1+2*k2+2*k3+k4)/6;
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
    
    return 0;
}