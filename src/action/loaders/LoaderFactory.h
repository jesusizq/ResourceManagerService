#ifndef LOADER_FACTORY_H
#define LOADER_FACTORY_H

#include <BaseLoader.h>
#include <BundleLoader.h>
#include <FileLoader.h>
#include <HttpLoader.h>
#include <LoaderTypes.h>
#include <memory>
#include <stdexcept>

class LoaderFactory {
public:
  static std::unique_ptr<BaseLoader> createLoader(LoaderTypes::Type type) {
    if (type == LoaderTypes::Type::File)
      return std::make_unique<FileLoader>();
    else if (type == LoaderTypes::Type::Http ||
             type == LoaderTypes::Type::Https)
      return std::make_unique<HttpLoader>();
    else if (type == LoaderTypes::Type::Bundle)
      return std::make_unique<BundleLoader>();

    throw std::invalid_argument("Unknown URI scheme");
  }
};

#endif // LOADER_FACTORY_H
