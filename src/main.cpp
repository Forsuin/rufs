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

    std::string fs_name = std::string(argv[1]) + ".dat";

    // create file if it doesn't already exist
    if (!std::ifstream(fs_name).good())
    {
        std::ofstream(fs_name).close();


        std::string root = "root\0\0\0\0";
        create_dir(fs_name, root);
    }

    std::cout << "Welcome to RUFS. Enter one of the following commands: " << std::endl;
    std::cout << "CreateDir, CreateFile, EndDir, or quit" << std::endl;

    bool close = false;

    std::string input;
    while (!close) {
        std::cout << "Command> ";
        std::cin >> input;

        if (input == "CreateDir") {
            std::cout << "Enter directory name: ";
            std::cin >> input;

            bool bad_dirname = false;

            do {
                //reset each loop
                bad_dirname = false;

                if (input.length() > 8) {
                    std::cout << "Invalid directory, can only be 8 characters long" << std::endl;
                    bad_dirname = true;

                    std::cout << "Enter filename: ";
                    std::cin >> input;
                }
            } while (bad_dirname);

            create_dir(fs_name, input);
        } else if (input == "CreateFile") {
            bool bad_filename = false;

            do {
                // reset each loop
                bad_filename = false;

                std::cout << "Enter filename: ";
                std::cin >> input;

                if (input.length() > 8) {
                    std::cout << "Invalid filename, must be 11 characters long or less" << std::endl;
                    bad_filename = true;
                }
                else if (input[input.size() - 2] != '.' && (input.back() != 't' || input.back() != 'p')) {
                    std::cout << "Invalid file extension" << std::endl;
                    bad_filename = true;
                }

                if (bad_filename) {
                    std::cout << "Enter filename: ";
                    std::cin >> input;
                }
            } while (bad_filename);

            // Good filename now, guaranteed to be text or program

            Filable::Type fileType = (input.back() == 't' ? Filable::Type::Text : Filable::Type::Program);

            Filable file;
            file.type = fileType;

            //
            for (int i = 0; i < 8; i++) {
                file.name[i] = '\0';
            }

            // Getting filename
            for (int i = 0;; i++) {
                if (input[i] == '.') {
                    break;
                }
                file.name[i] = input[i];
            }

            file.name[8] = '.';

            if (file.type == Filable::Type::Text) {

                file.name[9] = 't';
            }
            else {
                file.name[9] = 'p';
            }
            file.name[10] = '\0';

            // Getting file contents
            if (file.type == Filable::Type::Text) {

                std::cout << "Enter contents: ";
                std::cin >> file.contents.text_data;
            } else {
                std::cout << "Enter CPU requirements: ";
                std::cin >> file.contents.program.cpu_req;

                std::cout << "Enter memory requirements: ";
                std::cin >> file.contents.program.mem_req;
            }

            write_file(fs_name, file);
        } else if (input == "EndDir") {
        } else if (input == "quit") {
            close = true;
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}