#include "include/FileDump.h"
#include <ctime>
#include <sstream>
std::string FileDump::_fileName = "dump.txt";

FileDump::FileDump()
{
    //ctor
}

FileDump::~FileDump()
{
    //dtor
}
void FileDump::OpenFile(std::ofstream& myFile, std::ios::openmode fileMode)
{
    myFile.open (_fileName, fileMode);
}

void FileDump::CloseFile(std::ofstream& myFile)
{
    myFile.close();
}

void FileDump::WriteLine(std::string content)
{
    std::ofstream myfile;
    OpenFile(myfile);
    //std::time_t now = std::time(nullptr);
    //std::tm * localTime = localtime(&now);
    myfile << GetTimeStamp() << " -> " << content << std::endl;
    CloseFile(myfile);

}


std::string FileDump::GetTimeStamp()
{
    std::stringstream ss;
    std::time_t now = std::time(nullptr);
    std::tm * localTime = localtime(&now);
    ss << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec;
    return ss.str();
}

void FileDump::ClearFile()
{
    std::ofstream myfile;
    OpenFile(myfile, std::ios_base::out);
    myfile << "";
    myfile.close();
}

void FileDump::SetFileToError()
{
    _fileName = "dump.txt";
}

void FileDump::SetFileToTrajectory()
{
    _fileName = "trajectory.txt";
}
