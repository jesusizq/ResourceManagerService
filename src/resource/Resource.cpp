#include "Resource.h"

Resource::Resource(std::string_view uri) : m_uri(uri) {
  m_type = ContentType::getContentTypeFromPath(m_uri);
  m_metadata.set("source_uri", m_uri);
}
