#ifndef BUNDLE_LOADER_H
#define BUNDLE_LOADER_H

#include "BaseLoader.h"
#include <LoaderTypes.h>

class BundleLoader : public BaseLoader {
public:
  bool canProcess(const ResourcePtr &resource) const override {
    return LoaderTypes::detectType(resource->getUri()) ==
           LoaderTypes::Type::Bundle;
  };
  std::string_view getName() const override { return "BundleLoader"; }

protected:
  std::string_view getScheme(std::string_view uri) const override {
    return LoaderTypes::getScheme(LoaderTypes::Type::Bundle);
  }

  ResourceDataPtr readResource(std::string_view resourcePath,
                               std::string_view uri) override;

  void addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                   std::string_view uri) override;
};

#endif // BUNDLE_LOADER_H
