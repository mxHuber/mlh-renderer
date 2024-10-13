#include "FileReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace mlh {

void FileReader::readFromFile(std::string &ContainerForInput,
                              const std::string &FileDirectory) {
  std::ifstream InputStream(FileDirectory);
  if (!InputStream.is_open()) {
    std::cout << "Couldn't open file: " << FileDirectory << std::endl;
  }
  std::stringstream Buffer;
  Buffer << InputStream.rdbuf();
  ContainerForInput = Buffer.str();
}

} // namespace mlh
