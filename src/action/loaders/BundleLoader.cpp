#include "BundleLoader.h"

ResourceDataPtr BundleLoader::readResource(std::string_view resourcePath,
                                           std::string_view uri) {
  // Simulate file data
  auto data{std::make_unique<Resource::Data>()};
  data->push_back('B');
  data->push_back('U');
  data->push_back('N');
  data->push_back('D');
  data->push_back('L');
  data->push_back('E');
  return data;
}

void BundleLoader::addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                               std::string_view uri) {
  // Simulate metadata addition
  rsc->getMetadata().set("bundle_app_name", "AppBundle");
  rsc->getMetadata().set("bundle_version", "1.0.0");
  rsc->getMetadata().set("bundle_license", "LICENSE_STRING");
};
