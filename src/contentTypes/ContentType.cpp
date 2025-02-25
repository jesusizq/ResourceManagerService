#include "ContentType.h"

namespace ContentType {

std::string toString(Type type) {
  switch (type) {
  case Type::COMPRESSED:
    return "application/compressed";
  case Type::GZIP:
    return "application/gzip";
  case Type::ZIP:
    return "application/zip";
  case Type::TAR:
    return "application/tar";
  case Type::JSON:
    return "application/json";
  case Type::PNG:
    return "image/png";
  case Type::JPEG:
    return "image/jpeg";
  case Type::GIF:
    return "image/gif";
  case Type::BMP:
    return "image/bmp";
  case Type::TIFF:
    return "image/tiff";
  case Type::WEBP:
    return "image/webp";
  case Type::DECODED_IMAGE:
    return "image/decoded";
  case Type::PARSED_JSON:
    return "application/json-parsed";
  case Type::OCTET_STREAM:
    return "application/octet-stream";
  case Type::UNKNOWN:
    return "unknown/unknown";
  }
  return "unknown/unknown";
}

Type fromString(std::string_view typeString) {
  if (typeString == "application/compressed")
    return Type::COMPRESSED;
  if (typeString == "application/gzip")
    return Type::GZIP;
  if (typeString == "application/zip")
    return Type::ZIP;
  if (typeString == "application/tar")
    return Type::TAR;
  if (typeString == "application/json")
    return Type::JSON;
  if (typeString == "image/png")
    return Type::PNG;
  if (typeString == "image/jpeg")
    return Type::JPEG;
  if (typeString == "image/gif")
    return Type::GIF;
  if (typeString == "image/bmp")
    return Type::BMP;
  if (typeString == "image/tiff")
    return Type::TIFF;
  if (typeString == "image/webp")
    return Type::WEBP;
  if (typeString == "image/decoded")
    return Type::DECODED_IMAGE;
  if (typeString == "application/json-parsed")
    return Type::PARSED_JSON;
  if (typeString == "application/octet-stream")
    return Type::OCTET_STREAM;
  return Type::UNKNOWN;
}

ContentType::Type getContentTypeFromPath(const std::string &path) {
  if (auto pos{path.rfind('.')}; pos != std::string::npos) {
    const std::string extension{path.substr(pos + 1)};
    if (extension == "png")
      return Type::PNG;
    if (extension == "jpg" || extension == "jpeg")
      return Type::JPEG;
    if (extension == "gif")
      return Type::GIF;
    if (extension == "bmp")
      return Type::BMP;
    if (extension == "json")
      return Type::JSON;
    if (extension == "gz")
      return Type::GZIP;
    if (extension == "zip")
      return Type::ZIP;
    if (extension == "tar")
      return Type::TAR;
  }
  return Type::OCTET_STREAM;
}

} // namespace ContentType
