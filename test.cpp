#include "crypto.h"
#include <iostream>
#include <string>

int main() {
    Crypto crypto;

    // Example usage of shift_cipher
    std::string message = "ABZSDFGHJKL";
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

    // // test for substitution cipher
    // std::string substitution_key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    // std::string substituted_message = crypto.substitution_cipher(message, substitution_key);
    // std::cout << "Substituted message: " << substituted_message << std::endl;

    // std::string deciphered_message = crypto.substitution_cipher_decode(substituted_message, substitution_key);
    // std::cout << "Deciphered message: " << deciphered_message << std::endl;

    // ------------------------------------------------------------------------------------------------

    // test for affine cipher
    int a = 5;
    int b = 8;
    std::string affine_ciphered_message = crypto.affine_cipher(message, a, b);
    std::cout << "Affine Ciphered message: " << affine_ciphered_message << std::endl;

    std::string affine_deciphered_message = crypto.affine_cipher_decode(affine_ciphered_message, a, b);
    std::cout << "Affine Deciphered message: " << affine_deciphered_message << std::endl;


    return 0;
}
