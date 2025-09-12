#include <iostream>
#include <string>
#include <cctype>

class Crypto {
public:
    std::string alphabets_lower = "abcdefghijklmnopqrstuvwxyz";
    std::string alphabets_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /// shift_cipher shifts each letter in the message by the given key.
    /// @param message The message to be ciphered. (only alphabetic characters are shifted.)
    /// @param key The shift key. (integer < 26)
    /// @return The ciphered message.
    std::string shift_cipher(const std::string& message, int key) {
        std::string result;

        for (char character : message) {
            if (islower(character)) {
                size_t index = alphabets_lower.find(character);
                if (index != std::string::npos) {
                    result += alphabets_lower[( (index + key + alphabets_lower.size()) % alphabets_lower.size() )];
                } else {
                    result += character; // for non-alphabetic characters
                }
            } else if (isupper(character)) {
                size_t index = alphabets_upper.find(character);
                if (index != std::string::npos) {
                    result += alphabets_lower[( (index + key + alphabets_lower.size()) % alphabets_lower.size() )];
                } else {
                    result += character; // for non-alphabetic characters
                }
            } else {
                result += character; // for non-alphabetic characters
            }
        }
        return result;
    }

    /// shift_cipher_decode decodes a message that was encoded using the shift_cipher with the given key.
    /// @param message The message to be decoded.
    /// @param key The shift key used during encoding.
    /// @return The decoded message.
    std::string shift_cipher_decode(const std::string& message, int key) {
        return shift_cipher(message, -key);
    }

    /// key should be a 26-character string representing the substitution alphabets.
    /// @param message The message to be ciphered.
    /// @param key The substitution key.
    /// @return The ciphered message.
    std::string substitution_cipher(const std::string& message, const std::string& key) {
        std::string result;
        
        for (char character : message) {
            if (islower(character)) {
                size_t index = alphabets_lower.find(character);
                if (index != std::string::npos && key.size() == alphabets_lower.size()) {
                    result += key[index];
                } else {
                    result += character;
                }
            } else if (isupper(character)) {
                size_t index = alphabets_upper.find(character);
                if (index != std::string::npos && key.size() == alphabets_upper.size()) {
                    result += key[index];
                } else {
                    result += character;
                }
            } else {
                result += character;
            }
        }
        return result;
    }
};
