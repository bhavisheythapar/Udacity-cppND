#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <fstream>
#include <vector>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    float prevNonIdle, nonIdle, prevTotal, total, totald, idled, cpu_percentage;
    std::string key;    
    std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);

    if (filestream.is_open()) {
        while (filestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) 
        {
            break;
        }
    }

    std::vector<float> current = {user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice};

    prev_idle = prev_idle + prev_iowait;
    idle = idle + iowait;

    prevNonIdle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
    nonIdle = user + nice + system + irq + softirq + steal;

    prevTotal = prev_idle + prevNonIdle;
    total = idle + nonIdle;

    totald = total - prevTotal;
    idled = idle - prev_idle;

    cpu_percentage = (totald - idled)/totald;

    Processor::previous(current);
    return cpu_percentage;
}

void Processor::previous (std::vector<float> current) {
    Processor::prev_user = current[0];
    Processor::prev_nice = current[1];
    Processor::prev_system = current[2];
    Processor::prev_idle = current[3];
    Processor::prev_iowait = current[4];
    Processor::prev_irq = current[5];
    Processor::prev_softirq = current[6];
    Processor::prev_steal = current[7];
    Processor::prev_guest = current[8];
    Processor::prev_guest_nice = current[9];
}