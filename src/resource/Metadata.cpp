#include "Metadata.h"

std::string_view Metadata::get(std::string_view key) const {
  if (const auto it{m_entries.find(std::string(key))}; it != m_entries.end()) {
    return it->second;
  }
  return "";
}

void Metadata::merge(const Metadata &other) {
  for (const auto &[key, value] : other.m_entries) {
    m_entries[key] = value;
  }
}
