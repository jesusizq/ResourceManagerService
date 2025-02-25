// Metadata.h
#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <string_view>
#include <unordered_map>

class Metadata {
public:
  void clear() { m_entries.clear(); }
  std::string_view get(std::string_view key) const;
  void set(std::string_view key, std::string_view value) {
    m_entries[std::string(key)] = std::string(value);
  }
  bool has(std::string_view key) const {
    return m_entries.find(std::string(key)) != m_entries.end();
  }
  void remove(std::string_view key) { m_entries.erase(std::string(key)); }
  void merge(const Metadata &other);

private:
  std::unordered_map<std::string, std::string> m_entries;
};

#endif // METADATA_H
