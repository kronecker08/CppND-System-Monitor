#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;
bool Compare(Process P1, Process P2){
    try{
        bool v = (P1<P2);
        bool v2 = ~v;
    return v;
    }
    catch(...){
        return false;
    }
}
void sorter(vector<Process> *p){
    sort(p->begin(), p->end(), Compare);
}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> pid_vec = LinuxParser::Pids();
    vector<Process> process_vec{};
    for(auto pid : pid_vec){
        Process p{pid};
        processes_.push_back(p);
    }
    // Process p1 = processes_[0];
    // std::cout<<"this is from"<<p1.CpuUtilization()<<"\n";
    // Process p2 = processes_[1];
    // std::cout<<"this is from2"<<p2.CpuUtilization()<<"\n";
    // bool t = Compare(p1, p2);

    // std::cout<<"this is from bool"<<t<<"\n";

    // process_vec = processes_;
    // sorter(&process_vec);
    // for (auto i : processes_){
    //     std::cout<<i.cpu_usage_;
    // } 

    


    // Process
    
    sort(processes_.begin(), processes_.end(), Compare);

    
    
    
    
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    std::string os = LinuxParser::OperatingSystem();
    return os; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
    }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }