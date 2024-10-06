#include <iostream>
#include <string>
#include <cstring>
#include <codecvt>
#include <locale>

typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    char16_t chars[1];

    int getLength() {
        return length;
    }

    char16_t* getRawChars() {
        return chars;
    }

    std::string getString() {
        std::u16string u16(chars, length);
        std::string u8_conv = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
        return u8_conv;
    }
} monoString;

monoString* createMonoString(const std::u16string& input) {
    size_t size = sizeof(monoString) + (input.length() - 1) * sizeof(char16_t);
    monoString* newString = reinterpret_cast<monoString*>(malloc(size));

    if (newString) {
        newString->klass = nullptr; 
        newString->monitor = nullptr;
        newString->length = static_cast<int>(input.length());
        std::memcpy(newString->chars, input.data(), input.length() * sizeof(char16_t));
    }

    return newString;
}

int main() {
    std::u16string input = u"Hello";
    monoString* str = createMonoString(input);

    if (str) {
        std::cout << "Length: " << str->getLength() << std::endl;
        std::cout << "String: " << str->getString() << std::endl;
    }

    return 0;
}
