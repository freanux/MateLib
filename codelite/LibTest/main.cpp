#include <MateLib.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
    try {
        Mate::FileWriter fw("/tmp/test");
        fw.write("test data");

        return 0;
    } catch (const Mate::Exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}