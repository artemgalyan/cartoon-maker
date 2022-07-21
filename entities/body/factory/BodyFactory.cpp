#include "BodyFactory.h"

BodyFactory *BodyFactory::Instance() {
  if (instance_ == nullptr) {
    instance_ = new BodyFactory();
  }
  return instance_;
}

void BodyFactory::Initialize() {
  instance_ = Instance();
}
