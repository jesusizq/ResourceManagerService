#include "JsonParser.h"
#include <ContentType.h>
#include <Logger.h>

bool JsonParser::canProcess(const Resource &resource) const {
  return ContentType::isJson(resource.getContentType());
}

Action::ResourcePtr JsonParser::process(Action::ResourcePtr resource) {
  if (!resource) {
    Logger::log("JsonParser: Received null resource", Logger::LogLevel::ERROR);
    return nullptr;
  }

  Logger::log("JsonParser: Parsing JSON resource of type " +
                  std::string(resource->getType()),
              Logger::LogLevel::INFO);

  const auto data{std::move(resource->getData())};

  // Simulate JSON parsing validation
  bool isValidJson{true};
  if (data.empty()) {
    isValidJson = false;
  } else {
    // Basic check: JSON should start with { or [ and end with } or ]
    const auto firstChar = static_cast<char>(data[0]);
    const auto lastChar = static_cast<char>(data[data.size() - 1]);
    isValidJson = (firstChar == '{' || firstChar == '[') &&
                  (lastChar == '}' || lastChar == ']');
  }

  if (!isValidJson) {
    Logger::log("JsonParser: Invalid JSON format", Logger::LogLevel::ERROR);
    return nullptr;
  }

  auto processedData{std::make_unique<std::vector<uint8_t>>(std::move(data))};
  auto processedResource{std::make_unique<Resource>(
      std::move(processedData), ContentType::Type::PARSED_JSON)};

  processedResource->getMetadata().merge(resource->getMetadata());

  processedResource->getMetadata().set("processor", "JsonParser");
  processedResource->getMetadata().set("original_type",
                                       std::string(resource->getType()));

  Logger::log("JsonParser: Successfully parsed JSON resource",
              Logger::LogLevel::INFO);
  return processedResource;
}
