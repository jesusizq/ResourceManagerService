#ifndef LOADER_TYPES_H
#define LOADER_TYPES_H

#include <string_view>

namespace LoaderTypes {

enum class Type {
  File,
  Http,
  Https,
  Bundle,
  Unknown,
};

constexpr std::string_view getScheme(Type type) {
  switch (type) {
  case Type::File:
    return "file://";
  case Type::Http:
    return "http://";
  case Type::Https:
    return "https://";
  case Type::Bundle:
    return "bundle://";
  case Type::Unknown:
    return "";
  }
  return "";
}

constexpr Type detectType(std::string_view uri) {
  if (uri.find(getScheme(Type::File)) == 0)
    return Type::File;
  if (uri.find(getScheme(Type::Http)) == 0)
    return Type::Http;
  if (uri.find(getScheme(Type::Https)) == 0)
    return Type::Https;
  if (uri.find(getScheme(Type::Bundle)) == 0)
    return Type::Bundle;
  return Type::Unknown;
}

} // namespace LoaderTypes

#endif // LOADER_TYPES_H