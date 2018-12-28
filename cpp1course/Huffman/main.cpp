#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

#include <huffman.h>

int main(int argc, char* argv[])
{
    if (argc != 4 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0)) {
        std::cout << "fill arguments: -c/-d, fileIn, fileOut" << std::endl;
        return 0;
    }
    std::ifstream fin(argv[2], std::ios::binary);
    if (!fin) {
        std::cerr << "No input file" << std::endl;
        return -1;
    }
    std::ofstream fout(argv[3], std::ios::binary);
    if (!fout) {
        std::cerr << "No output file" << std::endl;
        return -1;
    }
    bool encode = std::strcmp(argv[1], "-c") == 0;
    clock_t time = clock();
    if (encode) {
        Huffman::compress(fin, fout);
    } else {
        try {
            Huffman::decompress(fin, fout);
        } catch (...) {
            std::cerr << "file is corrupted or empty" << std::endl;
            return -1;
        }
    }
    double time_spent = static_cast<double>(clock() - time) / CLOCKS_PER_SEC;
    std::cerr << "Success" << std::endl;
    std::cerr << "Time spent: " << std::setprecision(3) << time_spent << " seconds" << std::endl;
    return 0;
}