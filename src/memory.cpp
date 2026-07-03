#include "utils.h"

double get_memory_usage() {
    ifstream file("/proc/meminfo");
    if (!file.is_open()) return 0.0;

    long long total = 0;
    long long available = 0;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string key, unit;
        long long value;

        ss >> key >> value >> unit;

        if (key == "MemTotal:") {
            total = value;
        } else if (key == "MemAvailable:") {
            available = value;
        }

        if (total > 0 && available > 0) break; 
    }

    if (total == 0) return 0.0;

    long long used = total - available;
    return (double)used / total * 100.0;
}