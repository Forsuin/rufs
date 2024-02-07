

#include <string>
#include <stack>

#include "variant.h"

/*
 * In Rust I would have made this an enum and added a write member function
 *
 * I was going to write a c++11 implementation of std::variant but that
 * didn't work out since c++11 doesn't support template initializer lists or
 * something like that and this was easier since I'm only going to have 3
 * things that can get written to disk
 */

struct ProgramFile
{
    int cpu_req;
    int mem_req;
};

struct TextFile
{
    std::string data;
};

struct Directory
{
    int size;
};

struct Filable
{
    char name[11];

    variant<ProgramFile, TextFile, Directory> contents;
};

struct DirIndexPair
{
    Filable dir;
    int index;
};

struct Filesystem
{
private:
    std::stack<DirIndexPair> dirStack;

public:
    std::string name;

    /*
    Writes a file into filesystem
*/
    void write_file(Filable &file);

    /*
        Creates a new directory of the filesystem
    */
    void create_dir(const std::string &dir_name);

    /*
        Closes most recent directory
    */
    void end_dir();

    /*
        Closes any directories that are still open
    */
    void close_dirs();

    Filesystem(const std::string &name) : name(name) {}
};