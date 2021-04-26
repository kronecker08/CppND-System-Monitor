#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;
Process::Process(int pid):pid_(pid){
 foldername_ = LinuxParser::kProcDirectory + std::to_string(pid_)+"/";
}


// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<long int> vec{};
    long int v;
    string line, parse,a2,a3;
    int  v_check = 1 , a1;
    float value;

    std::ifstream stream(foldername_ + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream>>a1>>a2>>a3;
        while(linestream>>v){
            vec.push_back(v);
        }
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
            if (VmSize == "VmSize"){
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
    string line, user;
    std::ifstream stream(foldername_ + LinuxParser::kStatusFilename);
    if (stream.is_open()) {
        while(std::getline(stream, line)){
            std::istringstream linestream(line);
            linestream >> Uid >> value;
            if (Uid == "Uid"){
                 break;
            }
        }
    }
    std::ifstream stream2 (LinuxParser::kPasswordPath);
    if (stream2.is_open()) {
        while(std::getline(stream2, line)){
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream2(line);
            linestream2 >> user >> value_pass;
            if (value_pass == value){
                 return user;
            }
        }
    }
    return string(); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    string line, parse;
    int  v_check = 1 ;
    long int value;
    std::ifstream stream(foldername_ + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        while(linestream>>parse){
            v_check++;
            if  (v_check==22){
            break;
            }
        }
    }
    std::stringstream g(parse);
    g>>value;
    value = value / sysconf(_SC_CLK_TCK);
    return value;
 }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }