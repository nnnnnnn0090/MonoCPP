#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <locale>
#include <codecvt>

class monoString {
public:
    void *klass;
    void *monitor;
    int length;
    char16_t chars[1];

    monoString(const std::u16string& input) {
        size_t size = sizeof(monoString) + (input.length() - 1) * sizeof(char16_t);
        auto newString = reinterpret_cast<monoString*>(malloc(size));

        if (newString) {
            newString->klass = nullptr;
            newString->monitor = nullptr;
            newString->length = static_cast<int>(input.length());
            std::memcpy(newString->chars, input.data(), input.length() * sizeof(char16_t));
            *this = *newString;
            free(newString);
        }
    }

    ~monoString() {
    }

    int getLength() const {
        return length;
    }

    char16_t* getRawChars() {
        return chars;
    }

    std::string getString() const {
        std::u16string u16 = std::u16string(chars, length);
        std::string u8_conv = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
        return u8_conv;
    }
};

int main() {
    std::u16string input = u"Hello, Mono!";
    monoString myMonoString(input);

    std::cout << "Length: " << myMonoString.getLength() << std::endl;
    std::cout << "String: " << myMonoString.getString() << std::endl;

    return 0;
}
