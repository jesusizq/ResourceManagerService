#include "JsonParser.h"
#include <ContentType.h>
#include <Logger.h>

ResourceDataPtr JsonParser::processData(const ResourcePtr &resource) {
  Logger::log("JsonParser: Parsing JSON resource of type " +
                  std::string(resource->getType()),
              Logger::LogLevel::INFO);

  // Simulate JSON parsing validation.
  auto processedData{
      std::make_unique<Resource::Data>(std::move(resource->getData()))};
  return processedData;
}

void JsonParser::addMetadata(ResourcePtr &resource) {
  auto &metadata{resource->getMetadata()};
  metadata.set("version", "1.0");
  metadata.set("timestamp", "2025-01-01 12:00:00");
  metadata.set("status", "success");
  metadata.set("mode", "strict");
}
