#include <string>

/*
 * In Rust I would have made this an enum and added a write member function
 *
 * I was going to write a c++11 implementation of std::variant but that
 * didn't work out since c++11 doesn't support template initializer lists or
 * something like that and this was easier since I'm only going to have 3
 * things that can get written to disk
*/
struct Filable
{
    enum class Type
    {
        Text,
        Program,
        Directory
    };
    Type type;

    char name[11];

    union Contents
    {
        std::string text_data;

        struct ProgramData
        {
            int cpu_req;
            int mem_req;
        } program;

        int dir_size;

        Contents() {}
        Contents(const Filable::Contents& content) {}
        ~Contents() {}
    } contents;

    Filable(){}
    Filable(const Filable& filable): type(filable.type), contents(filable.contents){
        for(int i = 0; i < 11; i++) {
            name[i] = filable.name[i];
        }
    }
    ~Filable(){}
};

/*
    Writes a file into filesystem
*/
void write_file(const std::string& fs_name, Filable file);

/*
    Creates a new directory of the filesystem
*/
void create_dir(std::string fs_name, std::string dir_name);

/*
    Closes a directory
*/
void end_dir(std::string fs_name, std::string dir_name);