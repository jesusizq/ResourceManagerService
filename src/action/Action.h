#ifndef ACTION_H
#define ACTION_H

#include <Resource.h>
#include <memory>
#include <string_view>

using ResourcePtr = std::unique_ptr<Resource>;
using ResourceDataPtr = std::unique_ptr<Resource::Data>;

class Action {
public:
  virtual ~Action() = default;

  virtual bool canProcess(const ResourcePtr &resource) const = 0;
  virtual ResourcePtr process(ResourcePtr &resource) = 0;
  virtual std::string_view getName() const = 0;
};

#endif // ACTION_H
