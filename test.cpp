#include "crypto.h"
#include <iostream>
#include <string>

int main() {
    Crypto crypto;

    // Example usage of shift_cipher
    std::string message = "ASDFGHJKL";
    int key;

    // std::cout << "Enter message: ";
    // std::getline(std::cin, message);
    // std::cout << "Enter key: ";
    // std::cin >> key;

    // ------------------------------------------------------------------------------------------------

    // // test for applying shift cipher and then decoding it back
    // std::string ciphered_message = crypto.shift_cipher(message, key);
    // std::cout << "Ciphered message: " << ciphered_message << std::endl;

    // std::string deciphered_message = crypto.shift_cipher_decode(ciphered_message, key);
    // std::cout << "Deciphered message: " << deciphered_message << std::endl;

    // ------------------------------------------------------------------------------------------------

    // test for substitution cipher
    std::string substitution_key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    std::string substituted_message = crypto.substitution_cipher(message, substitution_key);
    std::cout << "Substituted message: " << substituted_message << std::endl;

    std::string deciphered_message = crypto.substitution_cipher_decode(substituted_message, substitution_key);
    std::cout << "Deciphered message: " << deciphered_message << std::endl;

    // ------------------------------------------------------------------------------------------------

    return 0;
}
