#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

string GetStdoutFromCommand(string cmd) 
{

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
    return data;
}

int const compare_videos(char* file1, char* file2)
{
    int result_value = 0;
    string command_str = "./generate "+string(file1)+" "+string(file2);
    string output = GetStdoutFromCommand(command_str);
    string word = "Detected";
    if (output.find(word) != std::string::npos) {
        result_value = 1;
    }
    else
    {
        result_value = 0;
    }
    return result_value;
}


#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(compare_videos)
{
    def("compare_videos", compare_videos, "compare videos");
}
