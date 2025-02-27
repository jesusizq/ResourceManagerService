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
  using PrevMetadataPtr = std::shared_ptr<const Metadata>;
  // Possible types that can be stored as metadata values
  using MetadataValue = std::variant<std::string, int, PrevMetadataPtr>;

  Metadata() = default;
  Metadata(const Metadata &other);
  Metadata(Metadata &&other) noexcept;
  Metadata &operator=(const Metadata &other);
  Metadata &operator=(Metadata &&other) noexcept;
  ~Metadata() = default;

  template <typename T> std::optional<T> get(const std::string &key) const {
    const auto it{m_entries.find(key)};
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
    if (key == PREV_METADATA_KEY) {
      throw std::invalid_argument(INVALID_KEY_ERROR);
    }
    m_entries[key] = value;
  }
  template <typename T> void set(const std::string &key, T &&value) {
    if (key == PREV_METADATA_KEY) {
      throw std::invalid_argument(INVALID_KEY_ERROR);
    }
    m_entries[key] = std::forward<T>(value);
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

  void storeAsPrevious();
  PrevMetadataPtr getPrevious() const;

private:
  static constexpr const char *PREV_METADATA_KEY = "prev";
  static constexpr const char *INVALID_KEY_ERROR = "Invalid key";
  std::unordered_map<std::string, MetadataValue> m_entries;
};

#endif // METADATA_H
