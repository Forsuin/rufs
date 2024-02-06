#include <fstream>
#include <stack>

#include <variant>

#include "rufs.h"

std::stack<Filable> dirStack;

// Will replace once working, only temporary
#define text_data get<TextFile>().data
#define program get<ProgramFile>()
#define dir_size get<Directory>().size

void write_file(const std::string &fs_name, Filable &file)
{
    std::ofstream fs(fs_name, std::ios::binary | std::ios::app);

    // shared between all 'file' types, no need to be in switch
    fs.write(file.name, sizeof(file.name));

    if (file.contents.is<TextFile>())
    {
        fs.write(file.contents.text_data.c_str(), file.contents.text_data.length());
    }
    else if (file.contents.is<ProgramFile>())
    {
        fs.write((char *)&file.contents.program.cpu_req, sizeof(int));
        fs.write((char *)&file.contents.program.mem_req, sizeof(int));
    }
    else
    {
        fs.write((char *)&file.contents.dir_size, sizeof(file.contents.dir_size));
    }
}

void create_dir(const std::string &fs_name, std::string dir_name)
{
    Filable new_dir;

    for (char &i : new_dir.name)
    {
        i = '\0';
    }

    for (unsigned int i = 0; i < dir_name.length(); i++)
    {
        new_dir.name[i] = dir_name[i];
    }

    new_dir.name[8] = '.';
    new_dir.name[9] = 'd';
    new_dir.name[10] = '\0';

    new_dir.contents.set<Directory>(Directory{69});

    write_file(fs_name, new_dir);
}

void end_dir(const std::string &fs_name, const std::string &dir_name)
{
}
