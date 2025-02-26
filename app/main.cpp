#include <ComputePipeline.h>
#include <Logger.h>
#include <iostream>
#include <string>

int main() {
  std::string uri;
  bool running = true;
  while (running) {
    Logger::log("Enter resource URI (or type 'exit' or 'q' to quit): ",
                Logger::LogLevel::INFO);
    std::cout << std::flush;

    std::getline(std::cin, uri);
    if (uri.empty()) {
      Logger::log("Empty URI, try again.", Logger::LogLevel::WARNING);
      continue;
    } else if (uri == "exit" || uri == "q") {
      Logger::log("Exiting program.", Logger::LogLevel::INFO);
      running = false;
      continue;
    }

    Logger::log("Computing resource with URI: [" + uri + "]",
                Logger::LogLevel::INFO);

    ComputePipeline pipeline;
    try {
      const auto resource{pipeline.process(uri)};
      if (resource) {
        Logger::log("Pipeline processing complete. Final resource type: " +
                        std::string(resource->getType()),
                    Logger::LogLevel::INFO);
        continue;
      }

      Logger::log("Pipeline processing did not return a processed resource.",
                  Logger::LogLevel::WARNING);

    } catch (const std::exception &ex) {
      Logger::log("Error processing resource: " + std::string(ex.what()),
                  Logger::LogLevel::ERROR);
    }
  }

  return 0;
}
