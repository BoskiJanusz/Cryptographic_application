#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <numeric>


class Crypto
{
    std::vector<int> ascii_vector;
    std::map<char, char> map_with_ascii_chars;
    std::map<char, char> map_to_encrypt;
    std::map<char, char> map_to_decrypt;
    
    void mix_vector_numbers();
    

    public:
    Crypto(){};
    ~Crypto(){};
    void make_ascii_map_to_encrypt();
    void set_string_to_encrypt();
    void encrypt_file_by_key();
    void decrypt_file_by_key();
    


};