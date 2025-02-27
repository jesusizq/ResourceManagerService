#include "ImageDecoder.h"
#include <ContentType.h>
#include <Logger.h>

ResourceDataPtr ImageDecoder::processData(const ResourcePtr &resource) {
  Logger::log("ImageDecoder: Decoding image of type " +
                  std::string(resource->getType()),
              Logger::LogLevel::INFO);
  // Simulate the image decoding process
  auto processedData{
      std::make_unique<Resource::Data>(std::move(resource->getData()))};
  return processedData;
}

void ImageDecoder::addMetadata(ResourcePtr &resource) {
  auto &metadata{resource->getMetadata()};
  metadata.set("imageDecoder", std::string(getName()));
  metadata.set("imageFormat", "PNG");
  metadata.set("width", "1920");
  metadata.set("height", "1080");
  metadata.set("colorSpace", "RGB");
  metadata.set("bitDepth", "8");
}
