#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <numeric> // for std::gcd

class Crypto {
public:
    std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

};
