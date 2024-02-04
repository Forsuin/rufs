#include <fstream>

#include "rufs.h"



void write_file(const std::string& fs_name, Filable file)
{
    std::ofstream fs(fs_name, std::ios::binary | std::ios::app);

    // shared between all 'file' types, no need to be in switch
    fs.write(file.name, sizeof(file.name));

    switch (file.type) {
        case Filable::Type::Text:
            fs.write(file.contents.text_data.c_str(), file.contents.text_data.length());
            break;
        case Filable::Type::Program:
            fs.write((char *)&file.contents.program.cpu_req, sizeof(int));
            fs.write((char *)&file.contents.program.mem_req, sizeof(int));
            break;
        case Filable::Type::Directory:
            fs.write((const char *)file.contents.dir_size, sizeof(file.contents.dir_size));
            break;
    }
}

void create_dir(std::string fs_name, std::string dir_name)
{
    Filable new_dir;
    new_dir.type = Filable::Type::Directory;

    for (int i = 0; i < 11; i++) {
        new_dir.name[i] = '\0';
    }

    for (int i = 0; i < dir_name.length(); i++) {
        new_dir.name[i] = dir_name[i];
    }

    new_dir.name[8] = '.';
    new_dir.name[9] = 'd';

    new_dir.contents.dir_size = 69;

    write_file(fs_name, new_dir);
}

void end_dir(std::string fs_name, std::string dir_name)
{
}
