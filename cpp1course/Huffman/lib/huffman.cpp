#include <array>
#include <vector>
#include <queue>
#include <memory>
#include <iostream>
#include <functional>
#include <cstring>

#include "huffman.h"

struct Huffman::my_istream {
    std::array<byte_t, 1 << 16> buffer{};
    uint8_t bit_pos = 0;
    size_t pos = 0;
    size_t size = 0;
    std::istream &istream;

    explicit my_istream(std::istream &istream) : istream(istream) {
        check_end();
    }

    void check_end() {
        if (size_t shift = size - pos; shift < 2) {
            for (size_t i = 0; i < shift; ++i) {
                buffer[i] = buffer[pos + i];
            }
            istream.read(reinterpret_cast<char *>(buffer.data() + shift), buffer.size() - shift);
            size = shift + istream.gcount();
            pos = 0;
        }
    }

    bool read_bit() {
        bool bit = (buffer[pos] & (1 << (8 - 1 - bit_pos))) != 0;
        ++bit_pos;
        if (bit_pos == 8) {
            bit_pos = 0;
            ++pos;
            check_end();
        }
        return bit;
    };

    uint8_t read_byte() {
        uint8_t bits = (buffer[pos] << bit_pos) | (buffer[pos + 1] >> (8 - bit_pos));
        ++pos;
        check_end();
        return bits;
    }

    bool has_more() {
        return !istream.fail() || pos < size;
    }

    void rewind() {
        istream.clear();
        istream.seekg(std::ios::beg);
        pos = size = bit_pos = 0;
        check_end();
    }

    ~my_istream() {
        rewind();
    }
};

struct Huffman::my_ostream {
    std::array<byte_t, 1 << 16> buffer{};
    uint8_t bit_pos = 0;
    size_t size = 0;
    std::ostream &ostream;

    explicit my_ostream(std::ostream &ostream) : ostream(ostream) {}

    void clear_buffer() {
        ostream.write(reinterpret_cast<const char *>(buffer.data()), size + (bit_pos != 0));
        size = bit_pos = 0;
        buffer.fill(0);
    }

    void write_bits(code_t bits, uint8_t count) {
        bits <<= bits_in_code - count;
        for (uint8_t i = 0; i < count; ++i) {
            decltype(bits) mask = (code_t(1) << (bits_in_code - 1 - i));
            buffer[size] |= (byte_t((bits & mask) != 0)) << (8 - 1 - bit_pos);
            ++bit_pos;
            if (bit_pos == 8) {
                bit_pos = 0;
                ++size;
                if (size == buffer.size()) {
                    clear_buffer();
                }
            }
        }
    }

    ~my_ostream() {
        clear_buffer();
    }

};

struct Huffman::symbol {
    byte_t byte;
    size_t count;
    code_t code;
    uint8_t bits;

    symbol(byte_t byte, size_t count, code_t code, uint8_t bits) : byte(byte), count(count), code(code),
                                                                   bits(bits) {}
};

struct Huffman::encode_node {
    byte_t byte{};
    size_t count{};
    std::shared_ptr<encode_node> left = nullptr;
    std::shared_ptr<encode_node> right = nullptr;

    encode_node() = default;

    encode_node(byte_t byte, size_t count) : byte(byte), count(count) {}

    encode_node(encode_node left, encode_node right) : count(left.count + right.count),
                                                       left(std::make_shared<encode_node>(left)),
                                                       right(std::make_shared<encode_node>(right)) {}
};

struct Huffman::decode_node {
    byte_t byte;
    std::shared_ptr<decode_node> left0 = nullptr;
    std::shared_ptr<decode_node> right1 = nullptr;

    explicit decode_node(byte_t byte) : byte(byte) {}

    decode_node(decode_node left, decode_node right) : byte(0),
                                                       left0(std::make_shared<decode_node>(left)),
                                                       right1(std::make_shared<decode_node>(right)) {}

};

//private:___________________________________________________________________________________________________
std::vector<Huffman::symbol> Huffman::build_dictionary(my_istream &istream) {
    std::vector<symbol> dictionary;
    dictionary.reserve(ALPHABET_SIZE);
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        dictionary.emplace_back(i, 0, 0, 0);
    }
    while (istream.has_more()) {
        ++dictionary[istream.read_byte()].count;
    }
    istream.rewind();
    return dictionary;
}

void Huffman::build_tree(std::vector<symbol> &dictionary, my_ostream &ostream) {
    std::array<encode_node, MAX_TREE_NODES> nodes{};
    std::function<bool(encode_node, encode_node)> comparator = [](encode_node const &lhs, encode_node const &rhs) {
        return lhs.count > rhs.count;
    };
    std::priority_queue<encode_node, std::vector<encode_node>, decltype(comparator)> queue(comparator);
    for (auto const &symbol : dictionary) {
        if (symbol.count > 0) {
            queue.emplace(symbol.byte, symbol.count);
        }
    }
    while (queue.size() != 1) {
        auto lhs = queue.top();
        queue.pop();
        auto rhs = queue.top();
        queue.pop();
        queue.emplace(lhs, rhs);
    }
    auto root = queue.top();
    store_tree(root, 0, !root.left && !root.right, dictionary, ostream);
}

void Huffman::store_tree(encode_node const &node, code_t code, uint8_t bits, std::vector<symbol> &dictionary,
                my_ostream &ostream) {
    if (!node.left && !node.right) {
        ostream.write_bits(1, 1);
        ostream.write_bits(node.byte, 8);
        dictionary[node.byte].code = code;
        dictionary[node.byte].bits = bits;
        return;
    } else {
        ostream.write_bits(0, 1);
    }
    ++bits;
    store_tree(*node.left, (code << 1) | 0, bits, dictionary, ostream);
    store_tree(*node.right, (code << 1) | 1, bits, dictionary, ostream);
}

Huffman::decode_node Huffman::recover_tree(my_istream &istream) {
    if (istream.read_bit()) {
        byte_t byte = istream.read_byte();
        return decode_node(byte);
    }
    auto left = recover_tree(istream);
    auto right = recover_tree(istream);
    return decode_node(left, right);
}

//public:____________________________________________________________________________________________________
void Huffman::compress(std::istream &in, std::ostream &out) {
    my_istream istream(in);
    auto dictionary = build_dictionary(istream);
    size_t file_size = 0;
    char bytes[sizeof(size_t)];
    for (auto const &symbol : dictionary) {
        file_size += symbol.count;
    }
    if (file_size == 0) {
        return;
    }
    std::memcpy(bytes, &file_size, sizeof(size_t));
    for (char byte : bytes) {
        out.put(byte);
    }
    my_ostream ostream(out);
    build_tree(dictionary, ostream);
    while (istream.has_more()) {
        byte_t byte = istream.read_byte();
        ostream.write_bits(dictionary[byte].code, dictionary[byte].bits);
    }
}

void Huffman::decompress(std::istream &in, std::ostream &out) {
    size_t file_size = 0;
    char bytes[sizeof(size_t)];
    for (char &byte : bytes) {
        int tmp = in.get();
        if (tmp == std::char_traits<char>::eof()) {
            return;
        } else {
            byte = static_cast<char>(tmp);
        }
    }
    std::memcpy(&file_size, bytes, sizeof(size_t));
    if (file_size == 0) {
        return;
    }
    my_istream istream(in);
    auto root = recover_tree(istream);
    for (size_t i = 0; i < file_size; ++i) {
        if (!istream.has_more()) {
            throw std::runtime_error("reading went wrong");
        }
        auto *node = &root;
        while (!(!node->left0 && !node->right1)) {
            bool tmpbit = istream.read_bit();
            if (tmpbit) { node = node->right1.get(); }
            else { node = node->left0.get(); }

        }
        out.put(node->byte);
    }
}