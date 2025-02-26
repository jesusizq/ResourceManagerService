#ifndef RESOURCE_H
#define RESOURCE_H

#include <ContentType.h>
#include <Metadata.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

class BaseProcessor;

class Resource {
  friend class BaseProcessor;

public:
  // Assume all resources can be represented like this
  using Data = std::vector<uint8_t>;

  explicit Resource(std::string_view uri);
  virtual ~Resource() = default;

  ContentType::Type getContentType() const { return m_type; }
  std::string getType() const { return ContentType::toString(m_type); }
  std::string getUri() const { return m_uri; }
  const Data &getData() const { return m_data; }
  Data &getData() { return m_data; }
  void setData(Data &&data) { m_data = std::move(data); }

  Metadata &getMetadata() { return m_metadata; }
  const Metadata &getMetadata() const { return m_metadata; }

private:
  ContentType::Type m_type;
  std::string m_uri;
  Metadata m_metadata;
  Data m_data;

  void setContentType(ContentType::Type type) { m_type = type; }
};

#endif // RESOURCE_H
