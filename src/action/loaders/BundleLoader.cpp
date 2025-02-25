#include "BundleLoader.h"
#include <ContentType.h>
#include <Logger.h>

Action::ResourcePtr BundleLoader::process(Action::ResourcePtr resource) {
  if (!resource) {
    Logger::log("Received null resource", Logger::LogLevel::ERROR);
    return nullptr;
  }

  const auto uri{resource->getUri()};
  const auto resourcePath{std::string(
      uri.substr(LoaderTypes::getScheme(LoaderTypes::Type::Bundle).size()))};
  Logger::log("Loading resource from " + resourcePath, Logger::LogLevel::INFO);

  // Simulate bundle data
  auto bundleData{std::make_unique<std::vector<uint8_t>>()};
  bundleData->push_back('B');
  bundleData->push_back('U');
  bundleData->push_back('N');
  bundleData->push_back('D');
  bundleData->push_back('L');
  bundleData->push_back('E');

  const auto contentType{ContentType::getContentTypeFromPath(resourcePath)};
  auto loadedResource{
      std::make_unique<Resource>(std::move(bundleData), contentType)};

  // Copy metadata from the original resource
  loadedResource->getMetadata().merge(resource->getMetadata());

  // Add additional metadata about the loading
  loadedResource->getMetadata().set("loader", this->getName());
  loadedResource->getMetadata().set("original_uri", std::string(uri));

  Logger::log("Successfully loaded resource as " +
                  ContentType::toString(contentType),
              Logger::LogLevel::INFO);
  return loadedResource;
}