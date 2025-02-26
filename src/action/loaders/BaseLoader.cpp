#include "BaseLoader.h"
#include <Logger.h>
#include <Resource.h>

ResourcePtr BaseLoader::process(ResourcePtr &resource) {
  if (!resource) {
    Logger::log("Received null resource", Logger::LogLevel::ERROR);
    return nullptr;
  }

  const auto uri{resource->getUri()};
  const auto scheme{this->getScheme(uri)};
  const auto resourcePath{std::string(uri.substr(scheme.size()))};

  Logger::log("Loading resource from " + resourcePath, Logger::LogLevel::INFO);

  auto data{this->readResource(resourcePath, uri)};
  resource->setData(std::move(*data));
  this->addMetadata(resource, resourcePath, uri);

  const auto contentType{ContentType::getContentTypeFromPath(resourcePath)};
  Logger::log(std::string(getName()) + ": Successfully loaded resource as " +
                  ContentType::toString(contentType),
              Logger::LogLevel::INFO);

  return std::move(resource);
}
