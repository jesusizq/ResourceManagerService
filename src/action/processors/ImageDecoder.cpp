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
