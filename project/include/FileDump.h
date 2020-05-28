#ifndef FILEDUMP_H
#define FILEDUMP_H

#include <string>
#include <fstream>
#include <QString>

class FileDump
{
    public:

        virtual ~FileDump();

        static void WriteLine(std::string);

        static void ClearFile();

        static void SetFileToError();
        static void SetFileToTrajectory();

    protected:
        FileDump();


    private:
        static std::string _fileName;
        static void OpenFile(std::ofstream&, std::ios::openmode=std::ios::app);
        static void CloseFile(std::ofstream&);
        static std::string GetTimeStamp();

};

#endif // FILEDUMP_H
