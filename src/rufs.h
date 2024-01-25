#include <string>
#include <vector>
#include <fstream>

struct Name
{
    char name[11];
};

struct File
{
    Name name;

    union Type
    {
        struct Text
        {
            int size;
            std::string contents;
        };

        struct Program
        {
            int cpuReq;
            int memReq;
        };
    };
};

struct Directory;

union DirContents
{
    File file;
    Directory dir;
};

struct Directory
{
    Name name;
    int numContents;
    std::vector<DirContents> contents;
};