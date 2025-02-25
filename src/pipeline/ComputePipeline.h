#ifndef COMPUTE_PIPELINE_H
#define COMPUTE_PIPELINE_H

#include <Action.h>
#include <Resource.h>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class ComputePipeline {
public:
  using ResourcePtr = std::unique_ptr<Resource>;

  ResourcePtr process(ResourcePtr resource);
  ResourcePtr process(std::string_view uri) {
    return process(std::make_unique<Resource>(uri));
  };

private:
  using ProcessorPtr = std::unique_ptr<Action>;

  void addProcessor(const std::string &type, ProcessorPtr processor) {
    if (m_processors.find(type) == m_processors.end()) {
      m_processors[type] = std::move(processor);
    }
  };
  void removeProcessor(const std::string &type) { m_processors.erase(type); }
  std::unordered_map<std::string, ProcessorPtr> m_processors;
};

#endif // COMPUTE_PIPELINE_H
