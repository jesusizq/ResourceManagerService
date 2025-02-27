#ifndef IMAGE_DECODER_H
#define IMAGE_DECODER_H

#include "BaseProcessor.h"
#include <string_view>

class ImageDecoder : public BaseProcessor {
public:
  bool canProcess(const ResourcePtr &resource) const override {
    return ContentType::isImage(resource->getContentType());
  };

  void addMetadata(ResourcePtr &resource) override;
  ResourceDataPtr processData(const ResourcePtr &resource) override;
  ContentType::Type getNewContentType() const override {
    return ContentType::Type::DECODED_IMAGE;
  }

  std::string_view getName() const override { return "ImageDecoder"; }
};

#endif // IMAGE_DECODER_H