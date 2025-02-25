#include "ComputePipeline.h"
#include <Decompressor.h>
#include <ImageDecoder.h>
#include <JsonParser.h>
#include <LoaderFactory.h>
#include <Logger.h>
#include <ProcessorFactory.h>
#include <memory>
#include <string>
#include <vector>

ComputePipeline::ResourcePtr ComputePipeline::process(ResourcePtr resource) {
  if (resource && resource->getData().empty() && !resource->getUri().empty()) {
    try {
      auto loader{LoaderFactory::createLoader(resource->getUri())};
      resource = loader->process(std::move(resource));
      if (!resource) {
        Logger::log("Loader failed processing.", Logger::LogLevel::ERROR);
        return nullptr;
      }
    } catch (const std::exception &ex) {
      Logger::log("Error creating loader: " + std::string(ex.what()),
                  Logger::LogLevel::ERROR);
      return nullptr;
    }
  }

  // Process the resource by dynamically fetching the processor based on its
  // type.
  const size_t MAX_ITERATIONS = 100; // prevent infinite processing loops
  size_t iteration = 0;
  while (iteration < MAX_ITERATIONS) {
    ProcessorPtr processor;
    try {
      processor = ProcessorFactory::createProcessor(resource->getType());
    } catch (const std::exception &ex) {
      break;
    }

    if (processor->canProcess(*resource)) {
      std::string oldType{resource->getType()};
      auto processedResource{processor->process(std::move(resource))};
      if (!processedResource) {
        Logger::log("Processor " + std::string(processor->getName()) +
                        " failed processing.",
                    Logger::LogLevel::ERROR);
        return nullptr;
      }
      resource = std::move(processedResource);

      // If the processor did not change the type we assume processing to be
      // complete.
      if (oldType == resource->getType()) {
        break;
      }
    } else {
      break;
    }

    ++iteration;
  }

  return resource;
}