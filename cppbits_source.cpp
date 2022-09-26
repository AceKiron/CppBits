#include <iostream>

#define CPPBITS_SOURCE

#include "cppbits.hpp"

namespace CppBits {

    Reader::Reader(const std::string& filename)
        : m_BitsOffset(0), m_BytesOffset(0) {
        m_Stream.open(filename, std::ifstream::in);
    }

    Reader::~Reader() {
        m_Stream.close();
    }

    uint8_t Reader::ReadChar() {
        uint8_t c = 0;
        for (int i = 0; i < 8; i++) {
            c *= 2;
            if (ReadBit()) c++;
        }
        return c;
    }

    bool Reader::ReadBoolean() {
        return ReadBit();
    }

    std::string Reader::ReadString() {
        std::string result = "";

        while (true) {
            if (!ReadBit()) break;
            result += ReadChar();
        }

        return result;
    }

    bool Reader::ReadBit() {
        if (m_BitsOffset == 0) {
            m_Current = m_Stream.get();
        }

        bool bit = (m_Current >> (7 - m_BitsOffset)) & 1;
        m_BitsOffset++;

        if (m_BitsOffset == 8) m_BitsOffset = 0;

        return bit;
    }

    Writer::Writer(const std::string& filename)
        : m_BitsOffset(0), m_Current(0) {
        m_Stream.open(filename);
    }

    Writer::~Writer() {
        Finalize();
    }

    void Writer::WriteChar(const uint8_t& value) {
        for (int i = 7; i >= 0; i--) WriteBit((value >> i) & 1);
    }

    void Writer::WriteBoolean(const bool& value) {
        WriteBit(value);
    }

    void Writer::WriteString(const std::string& value) {
        for (int ci = 0; ci < value.size(); ci++) {
            WriteBit(true);
            WriteChar(value.at(ci));
        }
        WriteBit(false);
    }

    void Writer::Finalize() {
        m_Current *= pow(2, 8 - m_BitsOffset);
        m_Stream << m_Current;

        m_Stream.close();
    }

    void Writer::WriteBit(const bool& bit) {
        m_Current *= 2;
        m_Current += bit;
        
        m_BitsOffset++;

        if (m_BitsOffset == 8) {
            m_Stream << m_Current;

            m_BitsOffset = 0;
            m_Current = 0;
        }
    }

}

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