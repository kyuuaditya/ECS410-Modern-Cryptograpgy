#include "crypto.h"
#include <iostream>
#include <string>
#include <chrono> // for clock

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generator

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

    // std::string decoded_message = crypto.stream_cipher_hw1_decode(stream_ciphered_message, stream_key);
    // std::cout << "stream deciphered message: " << decoded_message << std::endl;

    //----------------------------------------------------------------------------------------------------------------

    std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    auto start = std::chrono::high_resolution_clock::now();

    // Finding the key length of the stream cipher.
    int found_key_length = crypto.find_key_length(ciphered_message);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start) / 1000; // in milliseconds.
    std::cout << "End of Code, Time taken : " << duration.count() << " milliseconds" << std::endl;

    //----------------------------------------------------------------------------------------------------------------

    std::string candidateKey = "";

    if (found_key_length != -1) {
        // Breaking the stream cipher with key length L.
        for (int pos = 0; pos < found_key_length; pos++) {
            double bestScore = 1e18;
            char bestChar;

            // collect subsequence for this position.
            std::string subseq = "";
            for (int i = pos; i < ciphered_message.size(); i += found_key_length) {
                subseq.push_back(ciphered_message[i]);
            }

            // test all possible key chars
            for (char character : alphabets) {
                std::string decodedSubseq = crypto.stream_cipher_hw1_decode(subseq, std::string{ character });

                double score = crypto.chi_squared_test(decodedSubseq);
                if (score < bestScore) { // lower is better.
                    bestScore = score;
                    bestChar = character;
                }
            }

            candidateKey.push_back(bestChar);
            std::cout << "Position : " << pos << " Character : '" << bestChar << "' with chi² = " << bestScore << std::endl;
        }

        std::cout << "Candidate key = " << candidateKey << std::endl;
        std::cout << "Deciphered text = " << crypto.stream_cipher_hw1_decode(ciphered_message, candidateKey) << std::endl;
    }
    else {
        std::cerr << "Error: Unable to determine the key length." << std::endl;
    }

    //----------------------------------------------------------------------------------------------------------------

    // // test for permutation cipher
    // std::vector<int> perm_key = { 4, 3, 1, 0, 2 }; // example key
    // std::string perm_ciphered_message = crypto.permutation_cipher(normal_text, perm_key);
    // std::cout << "Permutation Ciphered message: " << perm_ciphered_message << std::endl;

    // std::string perm_deciphered_message = crypto.permutation_cipher_decode(perm_ciphered_message, perm_key);
    // std::cout << "Permutation Deciphered message: " << perm_deciphered_message << std::endl;

    //----------------------------------------------------------------------------------------------------------------


    return 0;
}
