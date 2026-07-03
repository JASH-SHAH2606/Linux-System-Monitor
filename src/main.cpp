#include "utils.h"
#include <iomanip>

struct ProcessInfo {
    string pid;
    double cpu_usage;
};

void print_dashboard(double cpu_usage, double mem_usage, const vector<ProcessInfo>& processes) {
    cout << "\033[1;1H";

    cout << fixed << setprecision(2);
    cout << "=====================================\n";
    cout << "      JASH LINUX SYSTEM MONITOR     \n";
    cout << "=====================================\n";
    cout << "CPU Usage:    " << cpu_usage << " %\n";
    cout << "Memory Usage: " << mem_usage << " %\n";
    cout << "-------------------------------------\n";
    cout << "TOP PROCESSES (Active):\n";

    int limit = min(5, (int)processes.size());
    for (int i = 0; i < limit; i++) {
        cout << i + 1 << ". PID " << processes[i].pid 
             << "   CPU " << processes[i].cpu_usage << " %\n";
    }

    for (int i = limit; i < 5; i++) {
        cout << "                                     \n";
    }

    if (processes.empty()) {
        cout << "(No significant load detected)       \n";
    }
    cout << "=====================================\n";
}

int main() {
    cout << "\033[2J";

    while (true) {
        // Snapshot 1
        vector<long long> cpu1 = read_cpu_times();
        auto proc1 = get_process_cpu_times();

        sleep(1);

        // Snapshot 2
        vector<long long> cpu2 = read_cpu_times();
        auto proc2 = get_process_cpu_times();

        // Calculate System CPU
        long long total1 = 0, total2 = 0;
        for (long long v : cpu1) total1 += v;
        for (long long v : cpu2) total2 += v;

        long long idle1 = (cpu1.size() > 4) ? cpu1[3] + cpu1[4] : 0;
        long long idle2 = (cpu2.size() > 4) ? cpu2[3] + cpu2[4] : 0;

        long long delta_total = total2 - total1;
        long long delta_idle = idle2 - idle1;
        
        if (delta_total == 0) delta_total = 1; 

        double cpu_percent = (double)(delta_total - delta_idle) / delta_total * 100.0;
        double mem_percent = get_memory_usage();

        // Calculate Process CPU
        vector<ProcessInfo> active_procs;
        for (auto& p : proc2) {
            if (proc1.count(p.first)) {
                long long delta_proc = p.second - proc1[p.first];
                double usage = (double)delta_proc / delta_total * 100.0;

                if (usage >= 0.0) {
                    active_procs.push_back({p.first, usage});
                }
            }
        }

        sort(active_procs.begin(), active_procs.end(), 
            [](const ProcessInfo& a, const ProcessInfo& b) {
                return a.cpu_usage > b.cpu_usage;
            });

        print_dashboard(cpu_percent, mem_percent, active_procs);
    }
    return 0;
}