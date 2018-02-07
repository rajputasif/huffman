#ifndef _CHUFFMAN_H
#define _CHUFFMAN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "BWT/CHuffman_int/HuffmanTree.h"
#include "BWT/CHuffman_int/Codec.h"

//void Huffman_compress(const std::string &src, const std::string &dest) {
//    std::ifstream is(src);
//    std::ofstream os(dest);

//    unsigned char byte;
//    std::map<Byte, int> freq;
//    std::vector<Byte> inputs;
//    while (is.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
//        ++freq[byte];
//        inputs.push_back(byte);
//    }
//    if (freq.empty()) return; // empty file

//    HuffmanTree tree(freq);
//    EncodingTable encoding_table = tree.getEncodingTable();
//    Encoder encoder(encoding_table);

//    uint8_t code_count = static_cast<unsigned char>(freq.size()-1); // decrease by one to prevent overflow
//    os.write(reinterpret_cast<char *>(&code_count), sizeof(code_count));
//    os << encoding_table.toString();

//    int32_t char_count = inputs.size();
//    os.write(reinterpret_cast<char *>(&char_count), sizeof(char_count));

//    Byte buf = 0;
//    int len = 0;

//    for (const auto uc: inputs) {
//        const auto &code = encoder.get(uc);
//        for (bool bit: code) {
//            buf |= bit;
//            ++len;
//            if (len == 8) {
//                os.write(reinterpret_cast<char *>(&buf), sizeof(buf));
//                buf = 0;
//                len = 0;
//            } else {
//                buf <<= 1;
//            }
//        }
//    }
//    if (len) {
//        buf <<= 7 - len;
//        os.write(reinterpret_cast<char *>(&buf), sizeof(buf));
//    }
//};


//void Huffman_decompress(const std::string &src, const std::string &dest) {
//    std::ifstream is(src);
//    std::ofstream os(dest);

//    uint8_t code_count;
//    is.read(reinterpret_cast<char *>(&code_count), sizeof(code_count));
//    if (!is) return; //empty file

//    HuffmanTree tree(is, code_count + 1);
//    Decoder decoder(tree.getRoot());
//    int32_t char_count;
//    is.read(reinterpret_cast<char *>(&char_count), sizeof(char_count));
//    Byte buf;
//    int len = 0;
//    Byte mask = 1 << 7;
//    while (true) {
//        while (len-- > 0) {
//            bool result = decoder.advance(mask & buf);
//            buf <<= 1;
//            if (result) {
//                Byte value = decoder.getValue();
//                os.write(reinterpret_cast<char *>(&value), sizeof(value));
//                decoder.reset();
//                --char_count;
//                if (char_count == 0) return;
//            }
//        }
//        is.read(reinterpret_cast<char *>(&buf), sizeof(buf));
//        len = 8;
//    }
//}

template <typename T>
void Huffman_compress_vec(std::vector<T> &inData, const std::string &dest) {
    //std::ifstream is(src);
    std::ofstream os(dest);

    T byte;
    std::map<T, int> freq;
    std::vector<T> inputs;
   for(int i=0;i<inData.size();i++){
   // while (is.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
       byte = inData[i];
       ++freq[byte];
        inputs.push_back(byte);
    }
    if (freq.empty()) return; // empty file

    HuffmanTree tree(freq);
    EncodingTable encoding_table = tree.getEncodingTable();
    Encoder encoder(encoding_table);

    uint8_t code_count = static_cast<unsigned char>(freq.size()-1); // decrease by one to prevent overflow
    os.write(reinterpret_cast<char *>(&code_count), sizeof(code_count));
    os << encoding_table.toString();

    int32_t char_count = inputs.size();
    os.write(reinterpret_cast<char *>(&char_count), sizeof(char_count));

    Byte buf = 0;
    int len = 0;

    for (const auto uc: inputs) {
        const auto &code = encoder.get(uc);
        for (bool bit: code) {
            buf |= bit;
            ++len;
            if (len ==  8) {
                os.write(reinterpret_cast<char *>(&buf), sizeof(buf));
                buf = 0;
                len = 0;
            } else {
                buf <<= 1;
            }
        }
    }
    if (len) {
        buf <<=  7 - len;
        os.write(reinterpret_cast<char *>(&buf), sizeof(buf));
    }
    std::cout<<"Writing done!\n";
}

template <typename T>
void Huffman_decompress_vec(const std::string &src, std::vector<T> &outData) {
    std::ifstream is(src);
    //std::ofstream os(dest);

    uint8_t code_count;
    is.read(reinterpret_cast<char *>(&code_count), sizeof(code_count));
    if (!is) return; //empty file

    HuffmanTree tree(is, code_count + 1);
    Decoder decoder(tree.getRoot());
    int32_t char_count;
    is.read(reinterpret_cast<char *>(&char_count), sizeof(char_count));
    Byte buf;
    int len = 0;
    Byte mask = 1 << 7;
    while (true) {
        while (len-- > 0) {
            bool thisBit = mask & buf;
            bool result = decoder.advance(thisBit);
            buf <<= 1;
            if (result) {
                T value = decoder.getValue();
                //os.write(reinterpret_cast<char *>(&value), sizeof(value));
                outData.push_back(value);
                decoder.reset();
                --char_count;
                if (char_count == 0) return;
            }
        }
        is.read(reinterpret_cast<char *>(&buf), sizeof(buf));
        len = 8;
    }
    std::cout<<"Reading done...";
}



#endif
