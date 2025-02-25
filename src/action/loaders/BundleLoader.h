#ifndef BUNDLE_LOADER_H
#define BUNDLE_LOADER_H

#include <Action.h>
#include <LoaderTypes.h>

class BundleLoader : public Action {
public:
  bool canProcess(const Resource &resource) const override {
    return LoaderTypes::detectType(resource.getUri()) ==
           LoaderTypes::Type::Bundle;
  };
  ResourcePtr process(ResourcePtr resource) override;
  std::string_view getName() const override { return "BundleLoader"; }
};

#endif // BUNDLE_LOADER_H
