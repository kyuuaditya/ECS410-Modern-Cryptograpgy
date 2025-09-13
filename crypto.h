#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <numeric> // for std::gcd
#include <vector>

class Crypto {
public:
    // English alphabets
    std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // English letter frequencies (A–Z , normalized)
    std::vector<double> englishFreq = {
        0.082,0.015,0.028,0.043,0.127,0.022,0.020,0.061,0.070,0.002,
        0.008,0.040,0.024,0.067,0.075,0.019,0.001,0.060,0.063,0.091,
        0.028,0.010,0.023,0.001,0.020,0.001
    };

    ///function to check if the input message is valid (only contains alphabetic characters, no-spaces and uppercase only)
    bool is_valid_message(const std::string& message) {
        for (char c : message) {
            if (!std::isupper(c) || !std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    /// function to convert a string to uppercase
    std::string to_uppercase(const std::string& input) {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    /// function to remove spaces and non-alphabetic characters from a string
    std::string alpha_only(const std::string& input) {
        std::string result = input;
        result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
            return !std::isalpha(c) || std::isspace(c);
            }), result.end());
        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// shift_cipher shifts each letter in the message by the given key.
    /// @param message The message to be ciphered. (only alphabetic characters are shifted.)
    /// @param key The shift key. (integer < 26)
    /// @return The ciphered message.
    std::string shift_cipher(const std::string& message, int key) {
        std::string result;

        if (!is_valid_message(message)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }

        for (char character : message) {
            size_t index = alphabets.find(character); // find index in alphabets.
            result += alphabets[((index + key + alphabets.size()) % alphabets.size())];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// shift_cipher_decode decodes a message that was encoded using the shift_cipher with the given key.
    /// @param message The message to be decoded.
    /// @param key The shift key used during encoding.
    /// @return The decoded message.
    std::string shift_cipher_decode(const std::string& cipher_text, int key) {
        if (!is_valid_message(cipher_text)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }

        return shift_cipher(cipher_text, -key);
    }

    //----------------------------------------------------------------------------------------------------------------

    /// key should be a 26-character string representing the substitution alphabets.
    /// @param message The message to be ciphered.
    /// @param key The substitution key.
    /// @return The ciphered message.
    std::string substitution_cipher(const std::string& message, const std::string& key) {
        std::string result;
        std::string message_modified;

        if (!is_valid_message(message)) {
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (key.size() != alphabets.size()) { // return error message if key size is not 26
            std::cerr << "Error: Key size must be 26 characters." << std::endl;
            return "";
        }

        for (char character : message) {
            size_t index = alphabets.find(character);
            result += key[index];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// substitution_cipher_decode decodes a message that was encoded using the substitution_cipher with the given key.
    /// @param message The message to be decoded.
    /// @param key The substitution key used during encoding.
    /// @return The decoded message.
    std::string substitution_cipher_decode(const std::string& cipher_text, const std::string& key) {
        std::string reverse_key;

        if (!is_valid_message(cipher_text)) {
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (key.size() != alphabets.size()) { // return error message if key size is not 26
            std::cerr << "Error: Key size must be 26 characters." << std::endl;
            return "";
        }

        for (char character : cipher_text) {
            size_t index = key.find(character);
            reverse_key += alphabets[index];
        }
        return reverse_key;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// affine_cipher is a type of monoalphabetic substitution cipher where each letter in an alphabet is mapped using a mathematical function.
    /// @param message The message to be ciphered.
    /// @param a The multiplicative key. (must be coprime with 26)
    /// @param b The additive key. (integer < 26)
    /// @return The ciphered message.
    std::string affine_cipher(const std::string& message, int a, int b) {
        std::string result;

        if (!is_valid_message(message)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (std::gcd(a, 26) != 1) { // return error message if a is not coprime with 26
            std::cerr << "Error: 'a' must be coprime with 26." << std::endl;
            return "";
        }

        for (char character : message) {
            size_t index = alphabets.find(character);
            result += alphabets[((a * index + b) % alphabets.size())];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// affine_cipher_decode decodes the cipher text that was encoded using the affine_cipher with the given keys.
    /// @param cipher_text The cipher text to be decoded.
    /// @param a The multiplicative key used during encoding.
    /// @param b The additive key used during encoding.
    /// @return The decoded message.
    std::string affine_cipher_decode(const std::string& cipher_text, int a, int b) {
        std::string result;
        int a_inv = 0;

        if (!is_valid_message(cipher_text)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (std::gcd(a, 26) != 1) { // return error message if a is not coprime with 26
            std::cerr << "Error: 'a' must be coprime with 26." << std::endl;
            return "";
        }

        // Calculate modular multiplicative inverse of a under modulo 26
        for (int i = 0; i < 26; i++) {
            if ((a * i) % 26 == 1) {
                a_inv = i;
                break;
            }
        }

        for (char character : cipher_text) {
            size_t index = alphabets.find(character);
            result += alphabets[((a_inv * (index - b + alphabets.size())) % alphabets.size())];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// vigenere_cipher uses a keyword to shift letters in the message.
    /// @param message The message to be ciphered.
    /// @param key The keyword used for shifting.
    /// @return The ciphered message.
    std::string vigenere_cipher(const std::string& message, const std::string& key) {
        std::string result;
        std::string message_modified;

        if (!is_valid_message(message)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (!is_valid_message(key)) { // return error message if key is not valid
            std::cerr << "Error: Key must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }

        // Repeat the key to match the length of the message
        std::string extended_key;
        for (size_t i = 0; i < message.size(); i++) {
            extended_key += key[i % key.size()];
        }

        for (size_t i = 0; i < message.size(); i++) {
            size_t message_index = alphabets.find(message[i]);
            size_t key_index = alphabets.find(extended_key[i]);
            result += alphabets[(message_index + key_index) % alphabets.size()];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// vigenere_cipher_decode decodes the cipher text that was encoded using the vigenere_cipher with the given key.
    /// @param cipher_text The cipher text to be decoded.
    /// @param key The keyword used during encoding.
    /// @return The decoded message.
    std::string vigenere_cipher_decode(const std::string& cipher_text, const std::string& key) {
        std::string result;

        if (!is_valid_message(cipher_text)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (!is_valid_message(key)) { // return error message if key is not valid
            std::cerr << "Error: Key must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }

        // Repeat the key to match the length of the cipher_text
        std::string extended_key;
        for (size_t i = 0; i < cipher_text.size(); i++) {
            extended_key += key[i % key.size()];
        }

        for (size_t i = 0; i < cipher_text.size(); i++) {
            size_t cipher_index = alphabets.find(cipher_text[i]);
            size_t key_index = alphabets.find(extended_key[i]);
            result += alphabets[(cipher_index - key_index + alphabets.size()) % alphabets.size()];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// This stream_cipher is defined as a modification of the Vigenere cipher. such that each time we use the keyword, we replace each letter by its successor modulo 26.
    /// @param message The message to be ciphered.
    /// @param key The keystream used for ciphering.
    /// @return The ciphered message.
    std::string stream_cipher_hw1(const std::string& message, const std::string& key) {
        std::string result;

        if (!is_valid_message(message)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (!is_valid_message(key)) { // return error message if key is not valid
            std::cerr << "Error: Key must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }

        size_t m = key.size();
        std::string keystream = key;

        // Generate keystream to match message length
        while (keystream.size() < message.size()) {
            std::string prev_block = keystream.substr(keystream.size() - m, m);
            std::string next_block;
            for (char c : prev_block) {
                size_t idx = alphabets.find(c);
                idx = (idx + 1) % alphabets.size();
                next_block += alphabets[idx];
            }
            keystream += next_block.substr(0, std::min(m, message.size() - keystream.size()));
        }

        for (size_t i = 0; i < message.size(); i++) {
            size_t message_index = alphabets.find(message[i]);
            size_t key_index = alphabets.find(keystream[i]);
            result += alphabets[(message_index + key_index) % alphabets.size()];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// stream_cipher_decode decodes the cipher text that was encoded using the stream_cipher with the given key.
    /// @param cipher_text The cipher text to be decoded.
    /// @param key The keystream used during encoding.
    /// @return The decoded message.

    std::string stream_cipher_hw1_decode(const std::string& cipher_text, const std::string& key) {
        std::string result;

        if (!is_valid_message(cipher_text)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (!is_valid_message(key)) { // return error message if key is not valid
            std::cerr << "Error: Key must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }

        size_t m = key.size();
        std::string keystream = key;
        // Generate keystream to match cipher_text length
        while (keystream.size() < cipher_text.size()) {
            std::string prev_block = keystream.substr(keystream.size() - m, m);
            std::string next_block;
            for (char c : prev_block) {
                size_t idx = alphabets.find(c);
                idx = (idx + 1) % alphabets.size();
                next_block += alphabets[idx];
            }
            keystream += next_block.substr(0, std::min(m, cipher_text.size() - keystream.size()));
        }

        for (size_t i = 0; i < cipher_text.size(); i++) {
            size_t cipher_index = alphabets.find(cipher_text[i]);
            size_t key_index = alphabets.find(keystream[i]);
            result += alphabets[(cipher_index - key_index + alphabets.size()) % alphabets.size()];
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    ///Index of coincidence tells the probability that two randomly selected letters from the text will be the same.
    /// @param text The text to calculate the index of coincidence for.
    /// @return The index of coincidence.
    double index_of_coincidence(const std::string& text) {
        if (!is_valid_message(text)) { // return error message if message is not valid
            std::cerr << "Error: Text must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return 0.0;
        }
        if (text.empty()) return 0.0;

        int letter_count[26] = { 0 };
        for (char c : text) {
            letter_count[c - 'A']++;
        }

        double n = static_cast<double>(text.size());
        double ic = 0.0;

        for (int count : letter_count) {
            ic += count * (count - 1);
        }

        ic /= (n * (n - 1));
        return ic;
    }

    /// chi_squared_test calculates the Chi-squared statistic for the given text.
    /// @param text The text to calculate the Chi-squared statistic for.
    /// @return The Chi-squared statistic.
    double chi_squared_test(const std::string& text) {
        if (!is_valid_message(text)) { // return error message if message is not valid
            std::cerr << "Error: Text must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return 0.0;
        }
        if (text.empty()) return 1e18;

        int letter_count[26] = { 0 };
        for (char c : text) {
            letter_count[c - 'A']++; // calculated in ascii.
        }

        double n = static_cast<double>(text.size());
        double chi_squared = 0.0;

        for (int i = 0; i < 26; i++) {
            double expected = englishFreq[i] * n;
            chi_squared += ((letter_count[i] - expected) * (letter_count[i] - expected)) / (expected + 1e-9);
        }

        return chi_squared;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// permutation_cipher is a transposition cipher that rearranges the characters of the plaintext according to a specified permutation key.
    /// @param message The message to be ciphered.
    /// @param key The permutation key.
    /// @return The ciphered message.
    std::string permutation_cipher(const std::string& message, const std::vector<int>& key) {
        std::string result;
        size_t n = key.size();

        if (!is_valid_message(message)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (n == 0 || *std::max_element(key.begin(), key.end()) >= static_cast<int>(n) || *std::min_element(key.begin(), key.end()) < 0) {
            std::cerr << "Error: Invalid permutation key." << std::endl;
            return "";
        }

        // Pad the message to make its length a multiple of n
        std::string padded_message = message;
        while (padded_message.size() % n != 0) {
            padded_message += 'X'; // Padding character
        }
        for (size_t i = 0; i < padded_message.size(); i += n) {
            for (int j : key) {
                result += padded_message[i + j];
            }
        }

        return result;
    }

    //----------------------------------------------------------------------------------------------------------------

    /// permutation_cipher_decode decodes the cipher text that was encoded using the permutation_cipher with the given key.
    /// @param cipher_text The cipher text to be decoded.
    /// @param key The permutation key used during encoding.
    /// @return The decoded message.
    std::string permutation_cipher_decode(const std::string& cipher_text, const std::vector<int>& key) {
        std::string result;
        size_t n = key.size();

        if (!is_valid_message(cipher_text)) { // return error message if message is not valid
            std::cerr << "Error: Message must contain only uppercase alphabetic characters with no spaces." << std::endl;
            return "";
        }
        if (n == 0 || *std::max_element(key.begin(), key.end()) >= static_cast<int>(n) || *std::min_element(key.begin(), key.end()) < 0) {
            std::cerr << "Error: Invalid permutation key." << std::endl;
            return "";
        }

        // Create inverse permutation key
        std::vector<int> inverse_key(n);
        for (size_t i = 0; i < n; i++) {
            inverse_key[key[i]] = i;
        }

        // Pad the cipher_text to make its length a multiple of n. (which would already be padded in most cases as this is a decipher function)
        std::string padded_message = cipher_text;
        while (padded_message.size() % n != 0) {
            padded_message += 'X'; // Padding character
        }

        for (size_t i = 0; i < padded_message.size(); i += n) {
            for (int j : inverse_key) {
                result += padded_message[i + j];
            }
        }

        return result;
    }

};
