#include "crypto.h"
#include <iostream>
#include <string>
#include <chrono> // for clock

int main() {
    Crypto crypto;

    // Example usage of shift_cipher
    std::string message = "THISISNOTAMESSAGESIKE";
    std::string stream_key;
    int key;
    std::string ciphered_message = "JEJNGNXZWHHGWFSUKULJQACZKKJOAAHGKEMTAFGMKVRDOPXNEHEKZNKFSKIFRQVHHOVXINPHMRTJPYWQGJWPUUVKFPOAWPMRKKQZWLQDYAZDRMLPBJKJOBWIWPSEPVVQMBCRYVCRUZAAOUMBCHDAGDIEMSZFZHALIGKEMJJFPCIWKRMLMPINAYOFIREAOLDTHITDVRMSE";
    std::string normal_text = crypto.to_uppercase(crypto.alpha_only("She considered the birds to be her friends. She'd put out food for them each morning and then she'd watch as they came to the feeders to gorge themselves for the day. She wondered what they would do if something ever happened to her. Would they miss the meals she provided if she failed to put out the food one morning"));

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

    // // test for affine cipher
    // int a = 5;
    // int b = 8;
    // std::string affine_ciphered_message = crypto.affine_cipher(message, a, b);
    // std::cout << "Affine Ciphered message: " << affine_ciphered_message << std::endl;

    // std::string affine_deciphered_message = crypto.affine_cipher_decode(affine_ciphered_message, a, b);
    // std::cout << "Affine Deciphered message: " << affine_deciphered_message << std::endl;

    // ------------------------------------------------------------------------------------------------

    // // test for vigenere cipher
    // std::string vigenere_key = "SUMMER";
    // std::string vigenere_ciphered_message = crypto.vigenere_cipher(message, vigenere_key);
    // std::cout << "Vigenere Ciphered message: " << vigenere_ciphered_message << std::endl;

    // // std::string vigenere_deciphered_message = crypto.vigenere_cipher_decode(vigenere_ciphered_message, vigenere_key);
    // // std::cout << "Vigenere Deciphered message: " << vigenere_deciphered_message << std::endl;

    //----------------------------------------------------------------------------------------------------------------

    // // test for stream cipher
    // stream_key = "SUMMER";
    // std::string stream_ciphered_message = crypto.stream_cipher_hw1(message, stream_key);
    // std::cout << "Stream Ciphered message: " << stream_ciphered_message << std::endl;

    // double decoded_message = crypto.stream_cipher_hw1_decode(ciphered_message, stream_key);
    // std::cout << "stream deciphered message: " << decoded_message << std::endl;

    //----------------------------------------------------------------------------------------------------------------

    std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    auto start = std::chrono::high_resolution_clock::now();

    // testing index of coincidence for different key sizes.
    size_t counter = 0;
    for (char character : alphabets) {
        for (char character2 : alphabets) {
            for (char character3 : alphabets) {
                for (char character4 : alphabets) {
                    for (char character5 : alphabets) {
                        std::string key = std::string{ character } + std::string{ character2 } + std::string{ character3 } + std::string{ character4 } + std::string{ character5 };
                        double test_text_IC = crypto.index_of_coincidence(crypto.stream_cipher_hw1_decode(ciphered_message, key));
                        if (test_text_IC > 0.060) {
                            counter++;
                        }
                    }
                }
            }
        }
    }
    // if the counter is giving good numbers then in that case. 
    std::cout << counter << "/" << 26 * 26 * 26 * 26 * 26 << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start) / 1000; // in milliseconds.
    std::cout << "End of Code, Time taken : " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
