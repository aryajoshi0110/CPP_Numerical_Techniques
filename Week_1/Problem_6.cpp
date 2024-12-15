#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

float diff_btw_vectors ( int n , float a[] , float b[] )
{
    float sum_of_sq = 0 ;
    for (int i = 0; i < n; i++)
    {
        sum_of_sq += pow(a[i]-b[i],2) ;
    }
    return pow(sum_of_sq,0.5) ;
}

int main()
{
    // 4x-y-z = 3
    // -2x+6y+z = 9
    // -x+y+7z = -6

    int n;
    cin >> n ;

    float A[n][n] , B[n] ;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j] ;
        }
        cin >> B[i] ;
    }
    
    cout << "INPUT TAKEN" << endl ;

    float x0[n];
    for (int i = 0; i < n; i++) x0[i] = 0 ;

    float x[n] ;
    int k = 0 ;
    float tolerance = pow(10,-6) ;

    float xk[n] , xk1[n] ;
    for (int i = 0; i < n; i++) xk[i] = x0[i] ;

    cout << "Jacobi Method" << endl ;

    for (int i = 0; i < n; i++)
        {
            float sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != i) sum += A[i][j]*xk[j] ;
            }
            xk1[i] = ( B[i] - sum )/A[i][i] ;
        }

    while ( k < 100 and diff_btw_vectors(n , xk , xk1) >= tolerance )
    {   
        // cout << k << endl ;
        for (int i = 0; i < n; i++) xk[i] = xk1[i] ; 
        for (int i = 0; i < n; i++)
        {
            float sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != i) sum += A[i][j]*xk[j] ;
            }
            xk1[i] = ( B[i] - sum )/A[i][i] ;
        }
        k++ ;
    } 

    cout << fixed << setprecision(3) ;
    cout << "Number of Iterations = " << k << endl ;
    cout << "The solution of the system of equations is: (" ;
    for ( int i = 0 ; i < n ; i++ ) 
    {
        if (i < n-1) cout << xk1[i] << "," ;
        else cout << xk1[i] ;
    }
    cout << ")" << endl ;

    for (int i = 0; i < n; i++)
    {
        xk[i] = x0[i] ;
        xk1[i] = 0 ;
    }

    cout << "Gauss-Siedel Method" << endl ;
    k=0;

    for (int i = 0; i < n; i++)
        {
            float sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum += A[i][j]*xk1[j] ;
            }
            for (int j = i+1; j < n; j++)
            {
                sum += A[i][j]*xk[j] ;
            }
            
            xk1[i] = ( B[i] - sum )/A[i][i] ;
        }

    while ( k < 100 and diff_btw_vectors(n , xk , xk1) >= tolerance )
    {   
        // cout << k << endl ;
        for (int i = 0; i < n; i++) xk[i] = xk1[i] ; 
        for (int i = 0; i < n; i++)
        {
            float sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum += A[i][j]*xk1[j] ;
            }
            for (int j = i+1; j < n; j++)
            {
                sum += A[i][j]*xk[j] ;
            }
            
            xk1[i] = ( B[i] - sum )/A[i][i] ;
        }
        k++ ;
    } 

    cout << fixed << setprecision(3) ;
    cout << "Number of Iterations = " << k << endl ;
    cout << "The solution of the system of equations is: (" ;
    for ( int i = 0 ; i < n ; i++ ) 
    {
        if (i < n-1) cout << xk1[i] << "," ;
        else cout << xk1[i] ;
    }
    cout << ")" << endl ;
    

    return 0;
}