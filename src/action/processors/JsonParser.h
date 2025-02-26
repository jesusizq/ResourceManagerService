#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "BaseProcessor.h"
#include <string_view>

class JsonParser : public BaseProcessor {
public:
  bool canProcess(const ResourcePtr &resource) const override {
    return ContentType::isJson(resource->getContentType());
  };

  ResourceDataPtr processData(const ResourcePtr &resource) override;
  ContentType::Type getNewContentType() const override {
    return ContentType::Type::PARSED_JSON;
  }

  std::string_view getName() const override { return "JsonParser"; }
};

#endif // JSON_PARSER_H