#include "Metadata.h"

Metadata::Metadata(const Metadata &other) : m_entries(other.m_entries) {}

Metadata::Metadata(Metadata &&other) noexcept
    : m_entries(std::move(other.m_entries)) {}

Metadata &Metadata::operator=(const Metadata &other) {
  if (this != &other) {
    m_entries = other.m_entries;
  }
  return *this;
}

Metadata &Metadata::operator=(Metadata &&other) noexcept {
  if (this != &other) {
    m_entries = std::move(other.m_entries);
  }
  return *this;
}

void Metadata::storeAsPrevious() {
  auto previous{std::make_shared<Metadata>()};
  previous->m_entries = std::move(m_entries);
  m_entries.clear();
  m_entries[PREV_METADATA_KEY] = previous;
}

Metadata::PrevMetadataPtr Metadata::getPrevious() const {
  const auto previous{get<PrevMetadataPtr>(PREV_METADATA_KEY)};
  return previous.value_or(nullptr);
}
