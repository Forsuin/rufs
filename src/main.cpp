#include <iostream>
#include <fstream>

#include "rufs.h"

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

        // make sure root exists in new file
        std::fstream fs(std::string(argv[1]) + ".dat", std::ios::in | std::ios::out | std::ios::binary);

        fs.write("root\0\0\0\0.d\0", 11);
        fs.close();
    }

    std::cout << "Welcome to RUFS. Enter one of the following commands: " << std::endl;
    std::cout << "CreateDir, CreateFile, EndDir, or quit" << std::endl;

    bool close = false;

    std::string input;
    while (!close)
    {
        std::cout << "Command> ";
        std::cin >> input;

        if (input == "CreateDir")
        {
            std::cout << "Enter directory name: ";
            std::cin >> input;
            create_dir(input);
        }
        else if (input == "CreateFile")
        {
            bool bad_filename = false;
            while (bad_filename)
            {
                bad_filename = false;

                std::cout << "Enter filename: ";
                std::cin >> input;

                if (input.length() > 10)
                {
                    std::cout << "Invalid filename" << std::endl;
                    bad_filename = true;
                }

                if (input.back() != 't' || input.back() != 'p')
                {
                    std::cout << "Invalid file extension" << std::endl;
                    bad_filename = true;
                }
            }

            // Good filename now

            Filable::Type fileType = input.back() == 't' ? Filable::Type::Text : Filable::Type::Program;

            Filable file();
            file.type = fileType;

            for (int i = 0; i < 8; i++)
            {
                file.name[i] = '\0';
            }

            for (int i = 0;; i++)
            {
                if (input[i] == '.')
                {
                    break;
                }
                file.name[i] = input[i];
            }

            Filable::Contents contents();
        }
        else if (input == "EndDir")
        {
        }
        else if (input == "quit")
        {
        }
        else
        {
            std::cout << "Invalid command" << std::endl;
        }
    }
}