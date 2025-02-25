#include "Resource.h"
#include <Logger.h>
#include <utility>

Resource::Resource(std::string_view uri)
    : m_data(std::make_unique<std::vector<uint8_t>>()), m_uri(uri) {
  Logger::log("Resource created with URI: " + std::string(uri),
              Logger::LogLevel::DEBUG);

  if (const auto pos{m_uri.rfind('.')}; pos != std::string::npos) {
    const std::string extension{m_uri.substr(pos + 1)};
    if (extension == "png" || extension == "jpg" || extension == "jpeg" ||
        extension == "gif" || extension == "bmp") {
      m_type = ContentType::fromString("image/" + extension);
    } else if (extension == "json") {
      m_type = ContentType::fromString("application/json");
    } else if (extension == "gz" || extension == "zip" || extension == "tar") {
      m_type = ContentType::fromString("application/compressed");
    } else {
      m_type = ContentType::fromString("application/octet-stream");
    }
  } else {
    m_type = ContentType::fromString("application/octet-stream");
  }

  m_metadata.set("source_uri", m_uri);
}

Resource::Resource(std::unique_ptr<std::vector<uint8_t>> data,
                   ContentType::Type contentType)
    : m_data(std::move(data)), m_type(contentType) {
  Logger::log("Resource created with type: " +
                  ContentType::toString(contentType),
              Logger::LogLevel::DEBUG);
}

Resource::Resource(std::unique_ptr<std::vector<uint8_t>> data,
                   std::string_view contentTypeStr)
    : m_data(std::move(data)), m_type(ContentType::fromString(contentTypeStr)) {
  Logger::log("Resource created with type: " + std::string(contentTypeStr),
              Logger::LogLevel::DEBUG);
}

Resource::Resource(Resource &&other) noexcept
    : m_data(std::move(other.m_data)), m_type(std::move(other.m_type)),
      m_uri(std::move(other.m_uri)), m_metadata(std::move(other.m_metadata)) {}

Resource &Resource::operator=(Resource &&other) noexcept {
  if (this != &other) {
    m_data = std::move(other.m_data);
    m_type = std::move(other.m_type);
    m_uri = std::move(other.m_uri);
    m_metadata = std::move(other.m_metadata);
  }
  return *this;
}