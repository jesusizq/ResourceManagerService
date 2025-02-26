#include "FileLoader.h"
#include <filesystem>

ResourceDataPtr FileLoader::readResource(std::string_view resourcePath,
                                         std::string_view uri) {
  // Simulate file data
  auto data{std::make_unique<Resource::Data>()};
  data->push_back('F');
  data->push_back('I');
  data->push_back('L');
  data->push_back('E');
  return data;
}

void FileLoader::addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                             std::string_view uri) {
  // Simulate metadata addition
  std::filesystem::path path(resourcePath);
  rsc->getMetadata().set("file_size", 1024); // Simulated file size
  rsc->getMetadata().set("file_extension", path.extension().string());
  rsc->getMetadata().set("file_name", path.filename().string());
  rsc->getMetadata().set("file_path", path.string());
  rsc->getMetadata().set("last_modified", "2025-01-01");
};
