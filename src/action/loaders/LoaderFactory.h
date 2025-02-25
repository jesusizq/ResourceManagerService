#ifndef LOADER_FACTORY_H
#define LOADER_FACTORY_H

#include <Action.h>
#include <BundleLoader.h>
#include <FileLoader.h>
#include <HttpLoader.h>
#include <LoaderTypes.h>
#include <memory>
#include <stdexcept>

class LoaderFactory {
public:
  static std::unique_ptr<Action> createLoader(std::string_view uri) {
    if (LoaderTypes::detectType(uri) == LoaderTypes::Type::File)
      return std::make_unique<FileLoader>();
    else if (LoaderTypes::detectType(uri) == LoaderTypes::Type::Http ||
             LoaderTypes::detectType(uri) == LoaderTypes::Type::Https)
      return std::make_unique<HttpLoader>();
    else if (LoaderTypes::detectType(uri) == LoaderTypes::Type::Bundle)
      return std::make_unique<BundleLoader>();

    throw std::invalid_argument("Unknown URI scheme");
  }
};

#endif // LOADER_FACTORY_H
