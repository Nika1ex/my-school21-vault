#include <math.h>
#include <stdio.h>

double VA(double x);
double LB(double x);
double QH(double x);

int main(void) {
    int i;
    const double m_pi = 3.14159265358979323846;
    double abscissa_interval_value = (fabs(-m_pi) + m_pi) / 41;
    for (i = 0; i <= 41; i++) {
        double abscissa_value = -m_pi + abscissa_interval_value * i;
        if (LB(abscissa_value) != LB(abscissa_value)) {
            printf("%.7lf | %.7lf | - | %.7lf\n", abscissa_value, VA(abscissa_value), QH(abscissa_value));
        } else {
            printf("%.7lf | %.7lf | %.7lf | %.7lf\n", abscissa_value, VA(abscissa_value), LB(abscissa_value),
                   QH(abscissa_value));
        }
    }
    return 0;
}

double VA(double x) { return pow(1, 3) / (pow(1, 2) + pow(x, 2)); }
double LB(double x) { return sqrt(sqrt(pow(1, 4) + 4 * pow(x, 2) * pow(1, 2)) - pow(x, 2) - pow(1, 2)); }
double QH(double x) { return 1 / pow(x, 2); }