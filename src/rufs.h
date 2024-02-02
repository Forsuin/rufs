#include <string>

struct Filable
{
    enum Type
    {
        Text,
        Program,
        Directory
    };
    Type type;

    char name[11];

    union Contents
    {
        struct Text
        {
            std::string text_data;
        } text;

        struct Program
        {
            int cpu_req;
            int mem_req;
        } program;

        struct Directory
        {
            int size;
        } dir;
    } contents;
};

/*
    Writes a file into filesystem
*/
void create_file(std::string fs_name, Filable file);

/*
    Creates a new directory of the filesystem
*/
void create_dir(std::string fs_name);

/*
    Closes a directory
*/
void end_dir(std::string fs_name, std::string dir_name);