#include <fstream>

#include "rufs.h"

// Will replace once working, only temporary
#define text_data get<TextFile>().data
#define program get<ProgramFile>()
#define dir_size get<Directory>().size

void Filesystem::write_file(Filable &file)
{
    std::ofstream fs(name, std::ios::binary | std::ios::app);
    // fs.seekp(std::ios::end); // make sure we're at end

    // shared between all 'file' types, no need to be in switch
    fs.write(file.name, sizeof(file.name));

    if (file.contents.is<TextFile>())
    {
        dirStack.top().dir.contents.set<Directory>(Directory{dirStack.top().dir.contents.dir_size + 1});
        fs.write(file.contents.text_data.c_str(), file.contents.text_data.length());
        fs.write("\0", 1);
    }
    else if (file.contents.is<ProgramFile>())
    {
        dirStack.top().dir.contents.set<Directory>(Directory{dirStack.top().dir.contents.dir_size + 1});
        fs.write((char *)&file.contents.program.cpu_req, sizeof(int));
        fs.write((char *)&file.contents.program.mem_req, sizeof(int));
    }
    else
    {
        dirStack.push({file, fs.tellp()});
        fs.write((char *)&file.contents.dir_size, sizeof(file.contents.dir_size));
    }
}

void Filesystem::create_dir(const std::string &dir_name)
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

    new_dir.contents.set<Directory>(Directory{0});

    write_file(new_dir);
}

void Filesystem::end_dir()
{
    std::fstream fs(name, std::ios::binary | std::ios::out | std::ios::in | std::ios_base::ate);
    int num_contents_loc = dirStack.top().index;
    int num_contents = dirStack.top().dir.contents.dir_size;
    std::string end_name = "End" + std::string(dirStack.top().dir.name) + ".d";

    fs.seekp(num_contents_loc);
    fs.write((char *)&num_contents, sizeof(int));

    fs.seekg(0, std::ios::end);
    fs.write((char *)end_name.c_str(), end_name.length());

    dirStack.pop();
}

void Filesystem::close_dirs()
{
    while (!dirStack.empty())
    {
        end_dir();
    }
}
