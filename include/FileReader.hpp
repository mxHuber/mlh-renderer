#ifndef MLH_RENDERER_FILE_READER_HPP
#define MLH_RENDERER_FILE_READER_HPP

#include <string>

namespace mlh {

class FileReader {
public:
  static void readFromFile(std::string &ContainerForInput,
                           const std::string &FileDirectory);
};

} // namespace mlh

#endif
