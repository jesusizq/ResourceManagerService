#include "ImageDecoder.h"
#include <ContentType.h>
#include <Logger.h>

bool ImageDecoder::canProcess(const Resource &resource) const {
  return ContentType::isImage(resource.getContentType());
}

Action::ResourcePtr ImageDecoder::process(Action::ResourcePtr resource) {
  if (!resource) {
    Logger::log("ImageDecoder: Received null resource",
                Logger::LogLevel::ERROR);
    return nullptr;
  }

  Logger::log("ImageDecoder: Decoding image of type " +
                  std::string(resource->getType()),
              Logger::LogLevel::INFO);

  // Simulate the decoding process
  auto processedData{
      std::make_unique<std::vector<uint8_t>>(std::move(resource->getData()))};

  auto processedResource{std::make_unique<Resource>(
      std::move(processedData), ContentType::Type::DECODED_IMAGE)};

  processedResource->getMetadata().merge(resource->getMetadata());
  processedResource->getMetadata().set("processor", "ImageDecoder");
  processedResource->getMetadata().set("original_type",
                                       std::string(resource->getType()));

  Logger::log("ImageDecoder: Successfully decoded image",
              Logger::LogLevel::INFO);
  return processedResource;
}