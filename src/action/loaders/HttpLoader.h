#ifndef HTTP_LOADER_H
#define HTTP_LOADER_H

#include <Action.h>
#include <LoaderTypes.h>

class HttpLoader : public Action {
public:
  bool canProcess(const Resource &resource) const override {
    return LoaderTypes::detectType(resource.getUri()) ==
               LoaderTypes::Type::Http ||
           LoaderTypes::detectType(resource.getUri()) ==
               LoaderTypes::Type::Https;
  };
  ResourcePtr process(ResourcePtr resource) override;
  std::string_view getName() const override { return "HttpLoader"; }
};

#endif // HTTP_LOADER_H
