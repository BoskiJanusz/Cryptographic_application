#include "crypto.h"


int main()
{
   
    Crypto C;
    C.make_ascii_map_to_encrypt();
    //C.set_string_to_encrypt();
    C.encrypt_file_by_key();
    C.decrypt_file_by_key();
    return 0;
}