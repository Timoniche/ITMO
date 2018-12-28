#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iosfwd>
#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <cstring>

typedef unsigned char byte_t;
typedef uint64_t code_t;
const uint8_t bits_in_code = 64;
const size_t ALPHABET_SIZE = 256;
const size_t MAX_TREE_NODES = (1 << 9) - 1;

class Huffman {
public:
    static void compress(std::istream& in, std::ostream& out);
    static void decompress(std::istream& in, std::ostream& out);
private:
    struct my_istream;
    struct my_ostream;
    struct symbol;
    struct encode_node;
    struct decode_node;
    //__________________________________________________________________________________________________
    static std::vector<symbol> build_dictionary(my_istream &istream);
    static void build_tree(std::vector<symbol> &dictionary, my_ostream &ostream);
    static void store_tree(encode_node const &node, code_t code, uint8_t bits, std::vector<symbol> &dictionary,
                    my_ostream &ostream);
    static decode_node recover_tree(my_istream &istream);
};



#endif //HUFFMAN_H