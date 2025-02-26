#ifndef PROCESSOR_FACTORY_H
#define PROCESSOR_FACTORY_H

#include <BaseProcessor.h>
#include <ContentType.h>
#include <Decompressor.h>
#include <ImageDecoder.h>
#include <JsonParser.h>
#include <memory>
#include <stdexcept>

class ProcessorFactory {
public:
  static std::unique_ptr<BaseProcessor>
  createProcessor(ContentType::Type type) {
    if (ContentType::isCompressed(type)) {
      return std::make_unique<Decompressor>();
    } else if (ContentType::isJson(type)) {
      return std::make_unique<JsonParser>();
    } else if (ContentType::isImage(type)) {
      return std::make_unique<ImageDecoder>();
    }

    throw std::invalid_argument("Unknown resource type");
  }
};

#endif // PROCESSOR_FACTORY_H
