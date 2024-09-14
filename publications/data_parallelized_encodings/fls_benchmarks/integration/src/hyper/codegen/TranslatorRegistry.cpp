#include "hyper/codegen/TranslatorRegistry.hpp"

namespace hyper {

TranslatorRegistry* TranslatorRegistry::global() {
   static TranslatorRegistry* global_registry = new TranslatorRegistry();
   return global_registry;
}

bool TranslatorRegistry::registerProduce(const std::string& op,
                                         ProduceFunc func) {
   produceRegistry[op] = func;
   return true;
}
ProduceFunc TranslatorRegistry::lookupProduce(const std::string& op) const {
   auto it = produceRegistry.find(op);
   if (it != produceRegistry.end()) {
      return it->second;
   } else {
      throw;
   }
}

bool TranslatorRegistry::registerConsume(const std::string& op,
                                         ConsumeFunc func) {
   consumeRegistry[op] = func;
   return true;
}
ConsumeFunc TranslatorRegistry::lookupConsume(const std::string& op) const {
   auto it = consumeRegistry.find(op);
   if (it != consumeRegistry.end()) {
      return it->second;
   } else {
      throw;
   }
}
}
