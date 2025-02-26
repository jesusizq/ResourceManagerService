// Metadata.h
#ifndef METADATA_H
#define METADATA_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

class Metadata {
public:
  // Define the possible types that can be stored as metadata values
  using MetadataValue =
      std::variant<std::string, int, std::shared_ptr<Metadata>>;

  template <typename T> std::optional<T> get(const std::string &key) const {
    auto it = m_entries.find(key);
    if (it == m_entries.end()) {
      return std::nullopt;
    }

    try {
      return std::get<T>(it->second);
    } catch (const std::bad_variant_access &) {
      return std::nullopt;
    }
  }

  template <typename T> void set(const std::string &key, const T &value) {
    m_entries[key] = value;
  }

  void clear() { m_entries.clear(); }
  void remove(const std::string &key) { m_entries.erase(key); }
  void merge(const Metadata &other) {
    for (const auto &[key, value] : other.m_entries) {
      m_entries[key] = value;
    }
  }

  bool has(const std::string &key) const {
    return m_entries.find(key) != m_entries.end();
  }

  void storeAsPrevious() {
    auto previousMetadata = std::make_shared<Metadata>();
    previousMetadata->m_entries = m_entries;
    m_entries.clear();
    m_entries["prev_metadata"] = previousMetadata;
  }

  std::shared_ptr<Metadata> getPreviousMetadata() const {
    auto previous = get<std::shared_ptr<Metadata>>("prev_metadata");
    return previous.value_or(nullptr);
  }

private:
  std::unordered_map<std::string, MetadataValue> m_entries;
};

#endif // METADATA_H
