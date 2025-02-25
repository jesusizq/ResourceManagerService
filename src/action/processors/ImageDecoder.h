#ifndef IMAGE_DECODER_H
#define IMAGE_DECODER_H

#include <Action.h>
#include <string_view>

class ImageDecoder : public Action {
public:
  bool canProcess(const Resource &resource) const override;
  ResourcePtr process(ResourcePtr resource) override;
  std::string_view getName() const override { return "ImageDecoder"; }
};

#endif // IMAGE_DECODER_H
