#ifndef HTTP_LOADER_H
#define HTTP_LOADER_H

#include "BaseLoader.h"
#include <LoaderTypes.h>

class HttpLoader : public BaseLoader {
public:
  bool canProcess(const ResourcePtr &resource) const override {
    return LoaderTypes::detectType(resource->getUri()) ==
               LoaderTypes::Type::Http ||
           LoaderTypes::detectType(resource->getUri()) ==
               LoaderTypes::Type::Https;
  };
  std::string_view getName() const override { return "HttpLoader"; }

protected:
  std::string_view getScheme(std::string_view uri) const override {
    return LoaderTypes::detectType(uri) == LoaderTypes::Type::Http
               ? LoaderTypes::getScheme(LoaderTypes::Type::Http)
               : LoaderTypes::getScheme(LoaderTypes::Type::Https);
  }

  ResourceDataPtr readResource(std::string_view resourcePath,
                               std::string_view uri) override;

  void addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                   std::string_view uri) override;
};

#endif // HTTP_LOADER_H
