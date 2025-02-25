#include "Decompressor.h"
#include <ContentType.h>
#include <Logger.h>
#include <random>
bool Decompressor::canProcess(const Resource &resource) const {
  return ContentType::isCompressed(resource.getContentType());
}

Action::ResourcePtr Decompressor::process(Action::ResourcePtr resource) {
  if (!resource) {
    Logger::log("Decompressor: Received null resource",
                Logger::LogLevel::ERROR);
    return nullptr;
  }

  Logger::log("Decompressor: Decoding compressed resource of type " +
                  std::string(resource->getType()),
              Logger::LogLevel::INFO);

  // Simulate decompression process
  auto processedData{
      std::make_unique<std::vector<uint8_t>>(std::move(resource->getData()))};

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(0, 1);

  const auto contentType{dis(gen) == 0 ? ContentType::Type::JSON
                                       : ContentType::Type::PNG};
  auto processedResource{
      std::make_unique<Resource>(std::move(processedData), contentType)};

  processedResource->getMetadata().merge(resource->getMetadata());

  processedResource->getMetadata().set("processor", "Decompressor");
  processedResource->getMetadata().set("original_type",
                                       std::string(resource->getType()));

  Logger::log("Decompressor: Successfully decompressed resource",
              Logger::LogLevel::INFO);
  return processedResource;
}
