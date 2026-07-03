#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>

using namespace std;

// CPU Functions
vector<long long> read_cpu_times();

// Memory Functions
double get_memory_usage();

// Process Functions
bool read_process_stat(const string& pid, long long& cpu_time);
unordered_map<string, long long> get_process_cpu_times();

#endif