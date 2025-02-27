#include "Resource.h"

Resource::Resource(std::string_view uri) : m_uri(uri) {
  m_type = ContentType::getContentTypeFromPath(m_uri);
  m_metadata.set("source_uri", m_uri);
  m_metadata.set("original_type", std::string(this->getType()));
}

Resource::Resource(const Resource &other)
    : m_type(other.m_type), m_uri(other.m_uri), m_metadata(other.m_metadata),
      m_data(other.m_data) {}

Resource::Resource(Resource &&other) noexcept
    : m_type(other.m_type), m_uri(std::move(other.m_uri)),
      m_metadata(std::move(other.m_metadata)), m_data(std::move(other.m_data)) {
}

Resource &Resource::operator=(const Resource &other) {
  if (this != &other) {
    m_type = other.m_type;
    m_uri = other.m_uri;
    m_metadata = other.m_metadata;
    m_data = other.m_data;
  }
  return *this;
}

Resource &Resource::operator=(Resource &&other) noexcept {
  if (this != &other) {
    m_type = other.m_type;
    m_uri = std::move(other.m_uri);
    m_metadata = std::move(other.m_metadata);
    m_data = std::move(other.m_data);
  }
  return *this;
}