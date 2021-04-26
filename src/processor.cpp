#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::string cpu;
    int value;
    std::vector<int> values{};
    std::string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream>>cpu;
    if (cpu == "cpu"){
        while (linestream>>value){
            values.push_back(value);
        }   
    }
    }
    int idle = values[3];
    int total = (values[0] + values[1] + values[2] + values[3]);
    float cpu_usg = (100.0*((total - prevtotal) - (idle - previdle)))/ (total - prevtotal);
    prevtotal = total;
    previdle = idle;
    return (cpu_usg/100); 
}

    
    
    