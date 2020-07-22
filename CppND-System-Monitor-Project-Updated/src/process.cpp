#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>

#include "process.h"
#include "linux_parser.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() {
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    string filename, value;
    int counter=1;
    float utime, stime, cutime, cstime, starttime;
    float total_time, seconds, cpu_usage;

    float hertz = sysconf(_SC_CLK_TCK);

    std::ifstream file;
    file.open("/proc/"+to_string(pid_)+"/stat"); 
   
    while (file >> value) 
    { 
        if (counter==14)
            utime=std::stof(value);
        if (counter==15)
            stime=std::stof(value);
        if (counter==16)
            cutime=std::stof(value);
        if (counter==17)
            cstime=std::stof(value);
        if (counter==22)
            starttime=std::stof(value);
        counter++;
    }

    total_time = utime + stime + cutime + cstime;
    seconds = LinuxParser::UpTime()-(starttime / hertz);
    cpu_usage = (total_time / hertz) / seconds;
    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    string line, cmd;
    std::ifstream filestream ("/proc/"+to_string(pid_)+"/cmdline");

    if (filestream.is_open()) {
        std::getline(filestream,cmd);
        return cmd;
    }   
    return "";
 }

// TODO: Return this process's memory utilization
string Process::Ram() {
    string line, key;
    int value;
    std::ifstream filestream ("/proc/"+to_string(pid_)+"/status");
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "VmSize") {
                    value=value/1000;
                    return to_string(value);
                }
            }
        }
    }
    return to_string(value);
}

// TODO: Return the user (name) that generated this process
std::string Process::User() {
    string line,key, user, alphabet;
    int uid, number, value;
    std::ifstream filestream ("/proc/"+to_string(pid_)+"/status");
    std::ifstream filestream2 ("/etc/passwd");
    
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "Uid") {
                    uid = value;
                }
            }
        }
    }

    if (filestream2.is_open()) {
        while (std::getline(filestream2, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> user >> alphabet >> number) {
                if (number == uid) {
                    return user;
                }
            }
        }
    }
    return "";
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    int counter=0;
    string filename, value;
    long time;

    std::ifstream file;
    file.open("/proc/"+to_string(pid_)+"/stat"); 
   
    while (file >> value) 
    { 
        
        if (counter==21) {
            time = std::stoi(value);
        }
        counter++;
    }
    return LinuxParser::UpTime()-(time/sysconf(_SC_CLK_TCK));
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    return a.cpuUtilization_  < cpuUtilization_ ;
 }