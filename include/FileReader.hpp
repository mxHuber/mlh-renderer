#ifndef MLH_RENDERER_FILE_READER_HPP
#define MLH_RENDERER_FILE_READER_HPP

#include <fstream>
#include <iostream>
#include <sstream>

namespace mlh {

class FileReader {
public:
  static void readFromFile(std::string &ContainerForInput,
                           const std::string &FileDirectory) {
    std::ifstream InputStream(FileDirectory);
    if (!InputStream.is_open()) {
      std::cout << "Couldn't open file: " << FileDirectory << std::endl;
    }
    std::stringstream Buffer;
    Buffer << InputStream.rdbuf();
    ContainerForInput = Buffer.str();
  }
};

} // namespace mlh

#endif
