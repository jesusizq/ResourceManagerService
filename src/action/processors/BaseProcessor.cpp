#include "BaseProcessor.h"
#include <Logger.h>
#include <memory>
#include <string_view>

ResourcePtr BaseProcessor::process(ResourcePtr &resource) {
  if (!resource) {
    Logger::log("BaseProcessor: Received null resource",
                Logger::LogLevel::ERROR);
    return nullptr;
  }

  auto processedResource{std::make_unique<Resource>(resource->getUri())};

  // Copy previous metadata and then store it as previous
  auto newMetadata{processedResource->getMetadata()};
  newMetadata = resource->getMetadata();
  newMetadata.storeAsPrevious();

  processedResource->setData(std::move(*this->processData(resource)));
  processedResource->setContentType(this->getNewContentType());
  processedResource->getMetadata().merge(newMetadata);

  this->updateMetadata(processedResource, resource);

  Logger::log(std::string(getName()) + ": Successfully processed resource as " +
                  processedResource->getType(),
              Logger::LogLevel::INFO);
  return processedResource;
}

void BaseProcessor::updateMetadata(ResourcePtr &resource,
                                   const ResourcePtr &originalResource) {
  resource->getMetadata().merge(originalResource->getMetadata());
  resource->getMetadata().set("processor", std::string(this->getName()));
  resource->getMetadata().set("original_type",
                              std::string(originalResource->getType()));
}