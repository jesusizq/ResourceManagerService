#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <Action.h>
#include <string_view>

class Decompressor : public Action {
public:
  bool canProcess(const Resource &resource) const override;
  ResourcePtr process(ResourcePtr resource) override;
  std::string_view getName() const override { return "Decompressor"; }
};

#endif // DECOMPRESSOR_H