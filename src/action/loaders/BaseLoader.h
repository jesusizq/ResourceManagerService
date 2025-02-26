#ifndef BASE_LOADER_H
#define BASE_LOADER_H

#include <Action.h>
#include <Resource.h>
#include <memory>

class BaseLoader : public Action {
protected:
  virtual ResourceDataPtr readResource(std::string_view resourcePath,
                                       std::string_view uri) = 0;
  virtual std::string_view getScheme(std::string_view uri) const = 0;
  virtual void addMetadata(ResourcePtr &rsc, std::string_view resourcePath,
                           std::string_view uri) = 0;

public:
  ResourcePtr process(ResourcePtr &resource) override;
};

#endif // BASE_LOADER_H
