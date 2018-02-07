#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>

#include "CHuffman.h"

int main(int argc, char *argv[]) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(-20, 20);

    int N = 1000;// options.xI > 0 ? options.xI : 1000;

    std::vector<int> uiData(N,0);
    for(int i=0;i<N;i++){
        uiData[i] = dis(gen);
    }

//    std::vector<int> uiData;
//    uiData.push_back(1);
//    uiData.push_back(1);
//    uiData.push_back(-2);
//    uiData.push_back(1);
//    uiData.push_back(0);
//    uiData.push_back(3);

    Huffman_compress_vec(uiData,"x.bin");

    std::vector<int> outData;
    Huffman_decompress_vec("x.bin",outData);

    if (std::equal(uiData.begin(), uiData.end(), outData.begin()))
      std::cout << "success" << std::endl;

    return EXIT_SUCCESS;
}
