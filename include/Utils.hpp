#ifndef MLH_RENDERER_UTILS_HPP
#define MLH_RENDERER_UTILS_HPP

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace mlh {

inline std::vector<std::string> getFileNamesInDir(const std::string &DirPath) {
  if (!std::filesystem::exists(DirPath)) {
    std::cout << "Directory does not exist: " << DirPath << std::endl;
  }

  std::vector<std::string> List;

  for (const auto &Entry : std::filesystem::directory_iterator(DirPath)) {
    if (Entry.is_regular_file()) {
      List.push_back(Entry.path());
    }
  }

  return List;
}

} // namespace mlh

#endif
