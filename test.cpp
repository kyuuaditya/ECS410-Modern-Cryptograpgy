#include "crypto.h"
#include <iostream>
#include <string>

int main() {
    Crypto crypto;

    // Example usage of shift_cypher
    std::string message;
    int key;

    std::cout << "Enter message: ";
    std::getline(std::cin, message);
    // std::cout << "Enter key: ";
    // std::cin >> key;

    // ------------------------------------------------------------------------------------------------

    // // test for applying shift cypher and then decoding it back
    // std::string ciphered_message = crypto.shift_cypher(message, key);
    // std::cout << "Ciphered message: " << ciphered_message << std::endl;

    // std::string deciphered_message = crypto.shift_cypher_decode(ciphered_message, key);
    // std::cout << "Deciphered message: " << deciphered_message << std::endl;

    // ------------------------------------------------------------------------------------------------

    // test for substitution cypher
    std::string substitution_key = "QWERTYUIOPASDFGHJKLZXCVBNM"; // simple reverse alphabet substitution
    std::string substituted_message = crypto.substitution_cypher(message, substitution_key);
    std::cout << "Substituted message: " << substituted_message << std::endl;

    // ------------------------------------------------------------------------------------------------
    return 0;
}
