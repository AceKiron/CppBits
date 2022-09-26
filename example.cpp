#include <iostream>

#include "cppbits.hpp"

int main() {
    CppBits::Writer* writer = new CppBits::Writer("test.bin");
    
    writer->WriteBoolean(true);
    writer->WriteBoolean(false);

    writer->WriteChar('a');
    writer->WriteChar('b');
    writer->WriteChar('c');
    
    writer->WriteBoolean(true);

    writer->WriteString("Hello world!");

    writer->WriteChar('/');

    delete writer;



    CppBits::Reader* reader = new CppBits::Reader("test.bin");

    std::cout << reader->ReadBoolean() << std::endl;
    std::cout << reader->ReadBoolean() << std::endl;

    std::cout << (char) reader->ReadChar() << std::endl;
    std::cout << (char) reader->ReadChar() << std::endl;
    std::cout << (char) reader->ReadChar() << std::endl;

    std::cout << reader->ReadBoolean() << std::endl;

    std::cout << reader->ReadString() << std::endl;

    std::cout << (char) reader->ReadChar() << std::endl;

    delete reader;
}