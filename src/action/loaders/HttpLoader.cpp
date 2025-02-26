#include "HttpLoader.h"

ResourceDataPtr HttpLoader::readResource(std::string_view resourcePath,
                                         std::string_view uri) {
  // Simulate data
  const auto isHttps{
      uri.find(LoaderTypes::getScheme(LoaderTypes::Type::Https)) == 0};
  const size_t prefixSize =
      isHttps ? LoaderTypes::getScheme(LoaderTypes::Type::Https).size()
              : LoaderTypes::getScheme(LoaderTypes::Type::Http).size();
  auto data{std::make_unique<std::vector<uint8_t>>()};

  data->push_back('H');
  data->push_back('T');
  data->push_back('T');
  data->push_back('P');
  if (isHttps) {
    data->push_back('S');
  }
  return data;
}

void HttpLoader::addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                             std::string_view uri) {
  // Simulate metadata addition
  rsc->getMetadata().set("http_status_code", 200);
  rsc->getMetadata().set("http_status_message", "OK");
  rsc->getMetadata().set("http_content_type", "text/html");
  rsc->getMetadata().set("http_content_length", 1024);
  rsc->getMetadata().set("http_content_encoding", "utf-8");
  rsc->getMetadata().set("http_content_language", "en");
};
