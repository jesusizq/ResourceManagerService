#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <Action.h>
#include <string_view>

class JsonParser : public Action {
public:
  bool canProcess(const Resource &resource) const override;
  ResourcePtr process(ResourcePtr resource) override;
  std::string_view getName() const override { return "JsonParser"; }
};

#endif // JSON_PARSER_H
