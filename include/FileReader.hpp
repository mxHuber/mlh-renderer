#ifndef MLH_RENDERER_FILE_READER_HPP
#define MLH_RENDERER_FILE_READER_HPP

#include <string>

namespace mlh {

struct FileReader {
  static void readFromFile(std::string &ContainerForInput,
                           const std::string &FileDirectory);
};

} // namespace mlh

#endif
