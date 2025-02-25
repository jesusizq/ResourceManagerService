#ifndef CONTENT_TYPE_H
#define CONTENT_TYPE_H

#include <string>
#include <string_view>

namespace ContentType {
enum class Type {

  // Compressed types
  COMPRESSED,
  GZIP,
  ZIP,
  TAR,

  // JSON type
  JSON,

  // Image types
  PNG,
  JPEG,
  GIF,
  BMP,
  TIFF,
  WEBP,

  // Processed types
  DECODED_IMAGE,
  PARSED_JSON,

  // Others
  OCTET_STREAM,

  // Default type
  UNKNOWN
};

std::string toString(Type type);
Type fromString(std::string_view typeString);
ContentType::Type getContentTypeFromPath(const std::string &path);

inline bool isCompressed(Type type) {
  return type == Type::COMPRESSED || type == Type::GZIP || type == Type::ZIP ||
         type == Type::TAR;
}

inline bool isImage(Type type) {
  return type == Type::PNG || type == Type::JPEG || type == Type::GIF ||
         type == Type::BMP || type == Type::TIFF || type == Type::WEBP;
}

inline bool isJson(Type type) { return type == Type::JSON; }
} // namespace ContentType

#endif // CONTENT_TYPE_H