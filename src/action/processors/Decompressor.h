#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "BaseProcessor.h"
#include <string_view>

class Decompressor : public BaseProcessor {
public:
  bool canProcess(const ResourcePtr &resource) const override {
    return ContentType::isCompressed(resource->getContentType());
  };

  ResourceDataPtr processData(const ResourcePtr &resource) override;
  ContentType::Type getNewContentType() const override;

  std::string_view getName() const override { return "Decompressor"; }
};

#endif // DECOMPRESSOR_H