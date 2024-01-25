#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: rufs [filename]" << std::endl;
        return 1;
    }

    // create file if doesn't already exist
    if (!std::ifstream(std::string(argv[1]) + ".dat").good())
    {
        std::ofstream(std::string(argv[1]) + ".dat").close();
        std::cout << "created file" << std::endl;
    }

    std::fstream fs(argv[1], std::ios::in | std::ios::out | std::ios::binary);

    fs.write("root\0\0\0\0.d\0", 11);
}