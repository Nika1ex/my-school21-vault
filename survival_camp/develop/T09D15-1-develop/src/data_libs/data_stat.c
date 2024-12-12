#include "data_stat.h"

double max(double *data, int n) {
    double max_v = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max_v) max_v = data[i];
    }
    return max_v;
}

double min(double *data, int n) {
    double min_v = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] < min_v) min_v = data[i];
    }
    return min_v;
}

double mean(double *data, int n) {
    double mean_v = 0;
    for (int i = 0; i < n; i++) {
        mean_v += data[i];
    }
    return mean_v / n;
}
double variance(double *data, int n) {
    double variance_v = 0;
    for (int i = 0; i < n; i++) {
        variance_v += (data[i] - mean(data, n)) * (data[i] - mean(data, n));
    }
    return variance_v / n;
}

void insert_sort(double *data, int n) {
    for (int i = 1; i < n; i++) {
        int k = i;
        while (k > 0 && data[k - 1] > data[k]) {
            int tmp = data[k - 1];
            data[k - 1] = data[k];
            data[k] = tmp;
            k -= 1;
        }
    }
}