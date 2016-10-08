#include <MateLib.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
    try {
        Mate::FileReader fr("/tmp/pw2");
        std::cout << "filesize: " << fr.get_size() << std::endl;

        return 0;
    } catch (const Mate::Exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}