#include "FileLoader.h"
#include <Logger.h>
#include <fstream>

Action::ResourcePtr FileLoader::process(Action::ResourcePtr resource) {
  if (!resource) {
    Logger::log("Received null resource", Logger::LogLevel::ERROR);
    return nullptr;
  }

  const auto uri{resource->getUri()};
  const auto resourcePath{std::string(
      uri.substr(LoaderTypes::getScheme(LoaderTypes::Type::File).size()))};
  Logger::log("Loading resource from " + resourcePath, Logger::LogLevel::INFO);

  // Simulate loading file
  auto fileData{std::make_unique<std::vector<uint8_t>>()};
  fileData->push_back('D');
  fileData->push_back('A');
  fileData->push_back('T');
  fileData->push_back('A');

  const auto contentType{ContentType::getContentTypeFromPath(resourcePath)};
  auto loadedResource{
      std::make_unique<Resource>(std::move(fileData), contentType)};

  // Copy metadata from the original resource
  loadedResource->getMetadata().merge(resource->getMetadata());

  // Add additional metadata about the loading
  loadedResource->getMetadata().set("loader", this->getName());
  loadedResource->getMetadata().set("original_uri",
                                    std::string(resource->getUri()));

  Logger::log("FileLoader: Successfully loaded file as " +
                  ContentType::toString(contentType),
              Logger::LogLevel::INFO);
  return loadedResource;
}
