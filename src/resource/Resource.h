// Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <ContentType.h>
#include <Metadata.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

class Resource {
public:
  explicit Resource(std::string_view uri);

  Resource(std::unique_ptr<std::vector<uint8_t>> data,
           ContentType::Type contentType);

  Resource(std::unique_ptr<std::vector<uint8_t>> data,
           std::string_view contentTypeStr);

  Resource(Resource &&other) noexcept;
  Resource &operator=(Resource &&other) noexcept;

  Resource(const Resource &) = delete;
  Resource &operator=(const Resource &) = delete;

  ContentType::Type getContentType() const { return m_type; }
  std::string_view getType() const { return ContentType::toString(m_type); }

  void setType(ContentType::Type type) { m_type = type; }
  void setType(std::string_view typeStr) {
    m_type = ContentType::fromString(typeStr);
  }

  std::string_view getUri() const { return m_uri; }

  const std::vector<uint8_t> &getData() const { return *m_data; }
  std::vector<uint8_t> &getData() { return *m_data; }

  Metadata &getMetadata() { return m_metadata; }
  const Metadata &getMetadata() const { return m_metadata; }

private:
  std::unique_ptr<std::vector<uint8_t>> m_data;
  ContentType::Type m_type;
  std::string m_uri;
  Metadata m_metadata;
};

#endif // RESOURCE_H