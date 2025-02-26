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
