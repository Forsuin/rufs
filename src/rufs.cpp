#include <fstream>

#include "rufs.h"

void create_file(std::string fs_name, Filable file)
{
    std::ofstream fs(fs_name, std::ios::binary | std::ios::app);
}

void create_dir(std::string fs_name)
{
}

void end_dir(std::string fs_name, std::string dir_name)
{
}
