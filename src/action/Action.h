#ifndef ACTION_H
#define ACTION_H

#include <Resource.h>
#include <memory>
#include <string_view>

class Action {
public:
  using ResourcePtr = std::unique_ptr<Resource>;
  virtual ~Action() = default;

  virtual bool canProcess(const Resource &resource) const = 0;
  virtual ResourcePtr process(ResourcePtr resource) = 0;
  virtual std::string_view getName() const = 0;
};

#endif // ACTION_H
