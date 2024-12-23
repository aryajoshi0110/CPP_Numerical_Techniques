#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

double y_ ( double x , double y , double z )
{
    return z ;
}
double z_ ( double x , double y , double z )
{
    return sin(x) + 2*cos(x) - 3*y - 4*z ;
}
void Actual (double x[], double y[] , int n)
{
    for (int i = 0; i < n; i++)
    {
        y[i] = exp(-x[i])*0.75 + exp(-3*x[i])*0.25 + sin(x[i])*0.5 ;
    }

}
void Euler ( double x[], double y[] , double z[] ,  int n, double h)
{
    for (int i = 0; i < n; i++)
    {
        y[i+1] = y[i] + y_(x[i],y[i],z[i])*h ;
        z[i+1] = z[i] + z_(x[i],y[i],z[i])*h ;
    }
}
void RK4 (double x[] , double y[], double z[] , int n , double h)
{
    for (int i = 0; i < n; i++)
    {
        x[i+1] = x[i] + h;
        double y1 = y_(x[i] , y[i] , z[i]) ;
        double z1 = z_(x[i] , y[i] , z[i]) ;
        double y2 = y_(x[i] + h/2, y[i] + h*y1/2, z[i] + h*z1/2);
        double z2 = z_(x[i] + h/2, y[i] + h*y1/2, z[i] + h*z1/2);
        double y3 = y_(x[i] + h/2, y[i] + h*y2/2, z[i] + h*z2/2);
        double z3 = z_(x[i] + h/2, y[i] + h*y2/2, z[i] + h*z2/2);
        double y4 = y_(x[i] + h, y[i] + h*y3, z[i] + h*z3);
        double z4 = z_(x[i] + h, y[i] + h*y3, z[i] + h*z3);

        y[i+1] = y[i] + h*(y1+2*y2+2*y3+y4)/6;
        z[i+1] = z[i] + h*(z1+2*z2+2*z3+z4)/6;
    }
}
void plotWithGnuplot(double x[] , double y1[] , double y2[] , double y_actual[] , int n) {
    // Open a pipe to Gnuplot
    FILE* gnuplotPipe = popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error: Could not open pipe to Gnuplot.\n";
        return;
    }

    // Send commands to Gnuplot
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Second Order Differential Equation'\n");
    fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
    fprintf(gnuplotPipe, "plot '-' title 'Euler Approximation' with lines,'-' title 'RK4 Approximation' with lines,'-' title 'Actual Function' with lines\n");
    
    // Send data to Gnuplot
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", x[i], y1[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of data
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", x[i], y2[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of data
    for (int i = 0; i < n; i++) {
        fprintf(gnuplotPipe, "%f %f\n", x[i], y_actual[i]);
    }
    fprintf(gnuplotPipe, "e\n");  // End of data

    // Close the pipe
    pclose(gnuplotPipe);
}

int main()
{
    // y" + 4y' + 3y = sinx + 2cosx
    // y(0) = 1, y'(0) = -1
    // y' = z
    // z' = sinx + 2cosx - 3y - 4z

    double h = 0.1 ;
    int n = 10/h + 1 ;
    double x[n] , y_euler[n] , z_euler[n] , y_rk4[n] , z_rk4[n] ,y_actual[n] ;
    x[0] = 0 , y_euler[0] = 1 , z_euler[0] = -1 , y_rk4[0] = 1 , z_rk4[0] = -1 ;
    for (int i = 0; i < n-1; i++) x[i+1] = x[i] + h ;

    Euler(x , y_euler , z_euler , n , h) ;
    RK4(x , y_rk4 , z_rk4  , n , h) ;
    Actual(x , y_actual , n) ;

    plotWithGnuplot(x , y_euler , y_rk4 , y_actual , n);

    return 0;
}