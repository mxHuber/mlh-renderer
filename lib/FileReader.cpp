#include "FileReader.hpp"
#include <fstream>
#include <iostream>

void FileReader::readFromFile(std::string &ContainerForInput,
                              const std::string &FileDirectory) {
  std::ifstream InputStream(FileDirectory);

  // check stream status
  if (!InputStream) {
    std::cout << "[FileReader::readFromFile]: Couldn't open file: "
              << FileDirectory << std::endl;
  }

  while (char CurrentChar = InputStream.get() != InputStream.eof()) {
    ContainerForInput += CurrentChar;
  }
}
