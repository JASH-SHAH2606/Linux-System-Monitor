#include "utils.h"

bool read_process_stat(const string& pid, long long& cpu_time) {
    string path = "/proc/" + pid + "/stat";
    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    if (!getline(file, line)) return false;

    size_t r_par = line.rfind(')');
    if (r_par == string::npos) return false;

    string rest = line.substr(r_par + 2);
    stringstream ss(rest);

    string state;
    if (!(ss >> state)) return false;

    long long dummy;
    for (int i = 0; i < 10; i++) {
        ss >> dummy;
    }

    //Read utime (user time) and stime (kernel time)
    long long utime, stime;
    if (!(ss >> utime >> stime)) return false;

    cpu_time = utime + stime;
    return true;
}

unordered_map<string, long long> get_process_cpu_times() {
    unordered_map<string, long long> proc_times;

    DIR* dir = opendir("/proc");
    if (!dir) return proc_times;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;

        // Filtering numeric folders (PIDs)
        if (!all_of(name.begin(), name.end(), ::isdigit)) continue;

        long long cpu;
        if (read_process_stat(name, cpu)) {
            proc_times[name] = cpu;
        }
    }

    closedir(dir);
    return proc_times;
}