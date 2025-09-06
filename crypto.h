#include <iostream>
#include <string>
#include <cctype>

class Crypto {
public:
    std::string shift_cypher(const std::string& message, int key) {
        std::string result;
        std::string alphabets_lower = "abcdefghijklmnopqrstuvwxyz";
        std::string alphabets_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (char character : message) {
            if (islower(character)) {
                size_t index = alphabets_lower.find(character);
                if (index != std::string::npos) {
                    result += alphabets_lower[(index + key) % alphabets_lower.size()];
                } else {
                    result += character; // for non-alphabetic characters
                }
            } else if (isupper(character)) {
                size_t index = alphabets_upper.find(character);
                if (index != std::string::npos) {
                    result += alphabets_upper[(index + key) % alphabets_upper.size()];
                } else {
                    result += character; // for non-alphabetic characters
                }
            } else {
                result += character; // for non-alphabetic characters
            }
        }
        return result;
    }
};
