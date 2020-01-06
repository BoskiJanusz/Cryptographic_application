#include "crypto.h"

void Crypto::mix_vector_numbers()
{
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distribution(32, 126); //ASCII ABC..123...abc...(*^
    ascii_vector.reserve(94);                                 //126  - 32  = 94
    while (ascii_vector.size() < 95)                          //rand 94 unnique numbers from 32 to 126
    {
        int temp = distribution(gen);

        auto result = std::find(std::begin(ascii_vector), std::end(ascii_vector), temp);

        if (result == std::end(ascii_vector))
            ascii_vector.emplace(ascii_vector.end(), temp);
    }
}

void Crypto::make_ascii_map_to_encrypt()
{
    mix_vector_numbers();
    std::fstream file;
    file.open("./key/key.txt", std::ios::out);
    char temp = 32;
    for (auto elem : ascii_vector)
    {
        map_with_ascii_chars[temp] = elem;
        if (file.is_open())
        {
            file << static_cast<char>(elem) << " " << temp << "\n";
        }
        else
        {
            std::cout << "unable to open";
        }

        temp++;
    }

    file.close();
}

void Crypto::set_string_to_encrypt()
{
    std::string str;
    std::getline(std::cin, str);
    std::cout << "Before: " << str << std::endl
              << "After: ";
    for (unsigned int i = 0; i < str.length(); i++)
    {
        auto it = map_with_ascii_chars.find(str[i]);
        std::cout << it->second;
    }
}

void Crypto::encrypt_file_by_key()
{
    std::fstream key_file, file_to_encrypt, encrypted_file;
    key_file.open("./key/key.txt", std::ios::in);
    file_to_encrypt.open("./files/encrypt.txt", std::ios::in);
    encrypted_file.open("./files/encrypted.txt", std::ios::out);

    std::string line;

    if (key_file.is_open() && file_to_encrypt.is_open() && encrypted_file.is_open())
    {
        while (std::getline(key_file, line))
        {
            //::cout<< int(line[0]) << " " << int(line[2])<<std::endl;
            map_to_encrypt[line[0]] = line[2];
            
        }
        // for (auto elem : map_to_encrypt)
        //     std::cout << int(elem.first) << " " << elem.second << std::endl;
        while (std::getline(file_to_encrypt, line))
        {
            //std::getline(file_to_encrypt, line);

            for (unsigned int i = 0; i < line.length(); i++)
            {
                auto it = map_to_encrypt.find(line[i]);
                encrypted_file << it->second;
            }
            encrypted_file << '\n';
        }
    }
    else
    {
        std::cout << "unable to open file" << std::endl;
    }
    key_file.close();
    file_to_encrypt.close();
    encrypted_file.close();
}

void Crypto::decrypt_file_by_key()
{
    std::fstream key_file, file_to_decrypt, decrypted_file;
    key_file.open("./key/key.txt", std::ios::in);
    file_to_decrypt.open("./files/encrypted.txt", std::ios::in);
    decrypted_file.open("./files/decrypted.txt", std::ios::out);

    std::string line;
    mix_vector_numbers();

    if (key_file.is_open() && file_to_decrypt.is_open() && decrypted_file.is_open())
    {
        while (  std::getline(key_file, line))
        {
           // std::getline(key_file, line);
            map_to_decrypt[line[2]] = line[0];
        }

        while ( std::getline(file_to_decrypt, line))
        {
            //std::getline(file_to_decrypt, line);

            for (unsigned int i = 0; i < line.length(); i++)
            {
                auto it = map_to_decrypt.find(line[i]);
                decrypted_file << it->second;
            }
            decrypted_file << '\n';
        }
    }

    else
    {
        std::cout << "unable to open file" << std::endl;
    }
    key_file.close();
    file_to_decrypt.close();
    decrypted_file.close();
}