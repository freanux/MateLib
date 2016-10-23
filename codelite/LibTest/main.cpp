#include <MateLib.hpp>

#include <iostream>
#include <clocale>

int main(int argc, char *argv[]) {
    static const int BufLength = 256;

    setlocale(LC_ALL, "");

    const char *src = "my äöü text";
    wchar_t dst[BufLength];

    Mate::fast_mbstowcs(dst, src, BufLength);
    std::wcout << dst << std::endl;

    return 0;
}