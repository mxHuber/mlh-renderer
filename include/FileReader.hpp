#ifndef EXREND2D_FILE_READER_HPP
#define EXREND2D_FILE_READER_HPP

#include <string>

struct FileReader {
  static void readFromFile(std::string &ContainerForInput,
                           const std::string &FileDirectory);
};

#endif
