// FileLoader.h
#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <Action.h>
#include <LoaderTypes.h>

class FileLoader : public Action {
public:
  bool canProcess(const Resource &resource) const override {
    return LoaderTypes::detectType(resource.getUri()) ==
           LoaderTypes::Type::File;
  };
  ResourcePtr process(ResourcePtr resource) override;
  std::string_view getName() const override { return "FileLoader"; }
};

#endif // FILE_LOADER_H
