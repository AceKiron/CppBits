# CppBits

A header-only/compiled C++ data serialization library.

## Usage examples

### Basic usage writer

```c++
#include <iostream>

#include "cppbits.hpp"

int main() {
    CppBits::Writer* writer = new CppBits::Writer("basic_usage.bin");
    
    writer->WriteBoolean(false);

    writer->WriteChar('a');
    writer->WriteChar('b');
    writer->WriteChar('c');

    delete writer;
}
```

---

### Basic usage reader

```c++
#include <iostream>

#include "cppbits.hpp"

int main() {
    CppBits::Reader* reader = new CppBits::Reader("test.bin");

    std::cout << reader->ReadBoolean() << std::endl;

    std::cout << (char) reader->ReadChar() << std::endl;
    std::cout << (char) reader->ReadChar() << std::endl;
    std::cout << (char) reader->ReadChar() << std::endl;

    delete reader;
}
```