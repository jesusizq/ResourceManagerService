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

  // First copy the original metadata and store it as previous before adding new
  // metadata
  auto &newMetadata{processedResource->getMetadata()};
  newMetadata = resource->getMetadata();
  newMetadata.storeAsPrevious();

  // Process data and set content type
  processedResource->setData(std::move(*this->processData(resource)));
  processedResource->setContentType(this->getNewContentType());

  // Add processor-specific metadata
  this->updateMetadata(processedResource);

  Logger::log(std::string(getName()) + ": Successfully processed resource as " +
                  processedResource->getType(),
              Logger::LogLevel::INFO);
  return processedResource;
}

void BaseProcessor::updateMetadata(ResourcePtr &resource) {
  auto &metadata{resource->getMetadata()};
  metadata.set("processor", std::string(this->getName()));
  this->addMetadata(resource);
}
