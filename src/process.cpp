#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid):pid_(pid){
 foldername_ = LinuxParser::kProcDirectory + std::to_string(pid_)+"/";
//  Process::CpuUtilization();
 Process::UpTime();
//  std::cout<<this->cpu_usage_;
    // std::cout<<pid_;
}


// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<string> vec{};
    string line, word;
    long uptime = LinuxParser::UpTime(); // this is the uptime of the system

    std::ifstream stream(foldername_ + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        while(linestream>>word){
            vec.push_back(word);
        }
    }
    try{
    float total_time = (std::stof(vec[13]) + std::stof(vec[14]) + std::stof(vec[15]) + std::stof(vec[16]))/ ((float) sysconf(_SC_CLK_TCK));
    float seconds = (float) uptime - ((std::stof(vec[21])/(float) sysconf(_SC_CLK_TCK)));
    cpu_usage_ = total_time /seconds;
    return cpu_usage_;
    }
    catch(...){
        return 0.0;
    }
}

    

// TODO: Return the command that generated this process
string Process::Command() { 
    string command;
    std::ifstream stream(foldername_ + LinuxParser::kCmdlineFilename);
    if (stream.is_open()){
        std::getline(stream, command);
    }
    return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    string VmSize;
    int value;
    string line;
    std::ifstream stream(foldername_ + LinuxParser::kStatusFilename);
    if (stream.is_open()) {
        while(std::getline(stream, line)){
            std::istringstream linestream(line);
            linestream >> VmSize >> value;
            if (VmSize == "VmSize:"){
                // std::cout<<value<<"\n";
                value = value/1000;
                return std::to_string (value);
            }
        }
    }
    return string();
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    string Uid;
    int value, value_pass;
    string line, user, st;
    std::ifstream stream(foldername_ + LinuxParser::kStatusFilename);
    if (stream.is_open()) {
        while(std::getline(stream, line)){
            std::istringstream linestream(line);
            linestream >> Uid >> value;
            if (Uid == "Uid:"){
                 break;
            }
        }
    }
    std::ifstream stream2 (LinuxParser::kPasswordPath);
    if (stream2.is_open()) {
        while(std::getline(stream2, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream2(line);
            linestream2 >> user >> st >> value_pass;
            if (value_pass == value){
                 return user;
            }
        }
    }
    return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    string line, word;
    long int value;
    std::ifstream stream(foldername_ + LinuxParser::kStatFilename);
    if (stream.is_open()) {

        std::getline(stream, line);
        std::istringstream linestream(line);
        for (int i =0; i<22; i++){
            linestream>>word;
        }
    }
    try{
    value = std::stol(word);
    value = value / sysconf(_SC_CLK_TCK);
    // std::cout<<"from here2";

    return value;}
    catch(...){
        // std::cout<<"from here";
        return 0;
    }
 }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function

bool Process::operator<(Process  & a) { 
    float const cpu_usage_self = this->CpuUtilization();
    float const cpu_usage_compare = a.CpuUtilization();
    return cpu_usage_compare< cpu_usage_self;
}