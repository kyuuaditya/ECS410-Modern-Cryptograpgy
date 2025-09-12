#include <iostream>
#include <string>
#include <cctype>

class Crypto {
public:
    std::string alphabets_lower = "abcdefghijklmnopqrstuvwxyz";
    std::string alphabets_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string shift_cypher(const std::string& message, int key) {
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

    std::string shift_cypher_decode(const std::string& message, int key) {
        return shift_cypher(message, -key);
    }

    std::string substitution_cypher(const std::string& message, const std::string& key) {
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
