#include <iostream>
#include <cmath>
#include <fstream>
#include <windows.h>

using namespace std;

double f(long double x, long double p)
{
    return atan(x) + p * (3 * x + 1);
}

double chord_method(long double a, long double b, long double p, long double eps)
{
    double x = a;

    while (fabs(f(x, p)) > eps)
    {
        x = b - (f(b, p) * (b - a)) / (f(b, p) - f(a, p));
        a = b;
        b = x;
    }

    return x;
}

void find_interval(long double& a, long double& b, long double p)
{
    while (f(a, p) * f(b, p) > 0)
    {
        a -= 1;
        b += 1;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    long double c = 0;
	long double d = 2;
    unsigned long int n = 30;
    long double h = (d - c) / n;
    long double eps = 0.001;

    ofstream results("results.csv");
    results << "a,b,p,корень\n";

    for (unsigned long int i = 0; i <= n; i++)
    {
        long double p = c + i * h;
        long double a = 0;
    	long double b = 1;
        find_interval(a, b, p);
        long double root = chord_method(a, b, p, eps);
        cout << "Корень при p = " << p << " равен " << root << " в интервале [" << a << ", " << b << "]" << endl;
        results << a << "," << b << "," << p << "," << root << "\n";
    }

    results.close();

    return 0;
}
