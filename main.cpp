#include <stdio.h>
#include "load_buffer.h"

#define READ_BUFFER_MAX (20 * (1 << 20))
int main() {
    FILE* file_;
    ObLoadDataBuffer buffer;
    buffer.create(READ_BUFFER_MAX);
    file_ = fopen("demo_1g.csv", "read");
    while (!feof(file_)) // to read file
    {
        // fucntion used to read the contents of file
        fread(buffer, sizeof(buffer), 1, file_);
//        std::cout << buffer;
    }
//    std::cout << "Hello, World!" << std::endl;
}
