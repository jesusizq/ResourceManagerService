#ifndef BASE_PROCESSOR_H
#define BASE_PROCESSOR_H

#include <Action.h>
#include <ContentType.h>
#include <Resource.h>
#include <memory>
#include <string>

using ResourcePtr = std::unique_ptr<Resource>;

class BaseProcessor : public Action {
protected:
  virtual ResourceDataPtr processData(const ResourcePtr &resource) = 0;
  virtual ContentType::Type getNewContentType() const = 0;

  virtual void updateMetadata(ResourcePtr &resource,
                              const ResourcePtr &originalResource);

public:
  ResourcePtr process(ResourcePtr &resource) override;
};

#endif // BASE_PROCESSOR_H
