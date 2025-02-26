#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include "BaseLoader.h"
#include <LoaderTypes.h>

class FileLoader : public BaseLoader {
public:
  bool canProcess(const ResourcePtr &resource) const override {
    return LoaderTypes::detectType(resource->getUri()) ==
           LoaderTypes::Type::File;
  };
  std::string_view getName() const override { return "FileLoader"; }

protected:
  std::string_view getScheme(std::string_view uri) const override {
    return LoaderTypes::getScheme(LoaderTypes::Type::File);
  }

  ResourceDataPtr readResource(std::string_view resourcePath,
                               std::string_view uri) override;

  void addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                   std::string_view uri) override;
};

#endif // FILE_LOADER_H
