#include "Decompressor.h"
#include <ContentType.h>
#include <Logger.h>
#include <random>

ResourceDataPtr Decompressor::processData(const ResourcePtr &resource) {
  // Simulate the decompression process
  auto processedData{
      std::make_unique<Resource::Data>(std::move(resource->getData()))};
  return processedData;
}

ContentType::Type Decompressor::getNewContentType() const {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(0, 1);

  // Randomly choose between JSON and PNG for demonstration purposes.
  return (dis(gen) == 0 ? ContentType::Type::JSON : ContentType::Type::PNG);
}

void Decompressor::addMetadata(ResourcePtr &resource) {
  auto &metadata{resource->getMetadata()};
  metadata.set("decompressor", std::string(getName()));
  metadata.set("compressionLevel", "1");
  metadata.set("compressionRatio", "1:10");
  metadata.set("compressionSpeed", "1000");
  metadata.set("compressionTime", "1000");
  metadata.set("compressionMemory", "1000");
}
