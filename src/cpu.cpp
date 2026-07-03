#include "utils.h"

vector<long long> read_cpu_times() {
    ifstream file("/proc/stat");
    if (!file.is_open()) return {};

    string line;
    if (!getline(file, line)) return {};

    string cpu_label;
    vector<long long> times;
    stringstream ss(line);
    
    ss >> cpu_label;

    long long val;
    while (ss >> val) {
        times.push_back(val);
    }

    return times;
}