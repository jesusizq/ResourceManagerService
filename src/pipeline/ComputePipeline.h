#ifndef COMPUTE_PIPELINE_H
#define COMPUTE_PIPELINE_H

#include <BaseLoader.h>
#include <BaseProcessor.h>
#include <LoaderTypes.h>
#include <ProcessorTypes.h>
#include <Resource.h>
#include <memory>
#include <unordered_map>

class ComputePipeline {
public:
  ComputePipeline() = default;

  ResourcePtr process(ResourcePtr &resource);
  ResourcePtr process(std::string_view uri) {
    auto resource{std::make_unique<Resource>(uri)};
    return process(resource);
  }

private:
  using ProcessorPtr = std::unique_ptr<BaseProcessor>;
  using LoaderPtr = std::unique_ptr<BaseLoader>;

  ResourcePtr load(ResourcePtr &resource);
  ResourcePtr processData(ResourcePtr &resource);

  template <typename K, typename T>
  void add(const K &key, std::unique_ptr<T> component,
           std::unordered_map<K, std::unique_ptr<T>> &container) {
    if (container.find(key) == container.end()) {
      container[key] = std::move(component);
    }
  }

  template <typename K, typename T>
  void remove(const K &key,
              std::unordered_map<K, std::unique_ptr<T>> &container) {
    container.erase(key);
  }

  template <typename K, typename T>
  T *find(const K &key,
          const std::unordered_map<K, std::unique_ptr<T>> &container) {
    if (auto it = container.find(key); it != container.end()) {
      return it->second.get();
    }
    return nullptr;
  }

  std::unordered_map<LoaderTypes::Type, LoaderPtr> m_loaders;
  std::unordered_map<ProcessorType, ProcessorPtr> m_processors;
};

#endif // COMPUTE_PIPELINE_H
