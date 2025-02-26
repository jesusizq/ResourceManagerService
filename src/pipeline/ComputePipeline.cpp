#include "ComputePipeline.h"
#include <LoaderFactory.h>
#include <Logger.h>
#include <ProcessorFactory.h>
#include <memory>
#include <string>
#include <vector>

ResourcePtr ComputePipeline::process(ResourcePtr &resource) {
  auto loadedResource{this->load(resource)};
  if (!loadedResource) {
    Logger::log("Failed to load resource.", Logger::LogLevel::ERROR);
    return nullptr;
  }

  return processData(loadedResource);
}

ResourcePtr ComputePipeline::load(ResourcePtr &resource) {
  // If the resource has not yet been loaded, pick a loader based on the URI
  if (resource && resource->getData().empty() && !resource->getUri().empty()) {
    const auto loaderType{LoaderTypes::detectType(resource->getUri())};
    if (m_loaders.find(loaderType) == m_loaders.end()) {
      try {
        m_loaders[loaderType] = LoaderFactory::createLoader(loaderType);
      } catch (const std::exception &ex) {
        Logger::log("Error dynamically creating loader: " +
                        std::string(ex.what()),
                    Logger::LogLevel::ERROR);
        return nullptr;
      }
    }

    const std::string loaderName{m_loaders[loaderType]->getName()};

    // Load the resource
    if (auto loader{m_loaders[loaderType].get()};
        loader && loader->canProcess(resource)) {

      auto loadedResource{loader->process(resource)};
      if (!loadedResource) {
        Logger::log(loaderName + " failed loading.", Logger::LogLevel::ERROR);
        return nullptr;
      }
      resource = std::move(loadedResource);
    } else {
      Logger::log(loaderName + " cannot load the resource.",
                  Logger::LogLevel::ERROR);
      return nullptr;
    }
  }

  return std::move(resource);
}

ResourcePtr ComputePipeline::processData(ResourcePtr &resource) {
  // Register and chain processors based on the resource content type
  const size_t MAX_ITERATIONS = 100; // To avoid infinite loops
  size_t iteration = 0;

  while (iteration < MAX_ITERATIONS) {
    const auto contentType{resource->getContentType()};
    auto processorType{ProcessorType::Unknown};
    if (ContentType::isCompressed(contentType)) {
      processorType = ProcessorType::Decompressor;
    } else if (ContentType::isJson(contentType)) {
      processorType = ProcessorType::JsonParser;
    } else if (ContentType::isImage(contentType)) {
      processorType = ProcessorType::ImageDecoder;
    } else {
      Logger::log("No processor found for content type: " +
                      ContentType::toString(contentType),
                  Logger::LogLevel::ERROR);
      break;
    }

    // Check if a processor was previously registered for this type
    if (m_processors.find(processorType) == m_processors.end()) {
      try {
        auto processor{ProcessorFactory::createProcessor(contentType)};
        m_processors[processorType] = std::move(processor);
      } catch (const std::exception &ex) {
        Logger::log("Error dynamically creating processor: " +
                        std::string(ex.what()),
                    Logger::LogLevel::ERROR);
        break;
      }
    }

    // Process the resource
    auto processor{m_processors[processorType].get()};
    if (!processor || !processor->canProcess(resource)) {
      break;
    }

    const auto oldType{resource->getContentType()};
    resource = processor->process(resource); // resource is overwritten
    if (!resource) {
      Logger::log(std::string(processor->getName()) + " failed processing.",
                  Logger::LogLevel::ERROR);
      return nullptr;
    }

    // If the processor did not change the type, assume no further processing is
    // needed.
    if (oldType == resource->getContentType()) {
      Logger::log(std::string(processor->getName()) +
                      " did not change the type of the resource.",
                  Logger::LogLevel::INFO);
      break;
    }

    ++iteration;
  }

  return std::move(resource);
}
