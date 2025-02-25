#include "HttpLoader.h"
#include <Logger.h>

Action::ResourcePtr HttpLoader::process(Action::ResourcePtr resource) {
  if (!resource) {
    Logger::log("HttpLoader: Received null resource", Logger::LogLevel::ERROR);
    return nullptr;
  }

  const auto uri{resource->getUri()};
  const auto isHttps{
      uri.find(LoaderTypes::getScheme(LoaderTypes::Type::Https)) == 0};
  const size_t prefixSize =
      isHttps ? LoaderTypes::getScheme(LoaderTypes::Type::Https).size()
              : LoaderTypes::getScheme(LoaderTypes::Type::Http).size();
  const auto resourcePath{std::string(uri.substr(prefixSize))};
  Logger::log("Loading resource from " + resourcePath, Logger::LogLevel::INFO);

  // Simulate HTTP data
  auto data{std::make_unique<std::vector<uint8_t>>()};
  data->push_back('H');
  data->push_back('T');
  data->push_back('T');
  data->push_back('P');
  if (isHttps) {
    data->push_back('S');
  }

  const auto contentType{ContentType::getContentTypeFromPath(resourcePath)};
  auto loadedResource{std::make_unique<Resource>(std::move(data), contentType)};

  // Copy metadata from the original resource
  loadedResource->getMetadata().merge(resource->getMetadata());

  // Add additional metadata about the loading
  loadedResource->getMetadata().set("loader", this->getName());
  loadedResource->getMetadata().set("original_uri",
                                    std::string(resource->getUri()));

  Logger::log("HttpLoader: Successfully loaded resource as " +
                  ContentType::toString(contentType),
              Logger::LogLevel::INFO);
  return loadedResource;
}
