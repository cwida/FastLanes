#pragma once

#include "hyper/codegen/Translator.hpp"
#include <unordered_map>

namespace hyper {

typedef void (*ProduceFunc)(algebra::Operator& op, std::ostream& s);
typedef void (*ConsumeFunc)(algebra::Operator& op, algebra::Operator& sender,
                            std::ostream& s);

class TranslatorRegistry {
 public:
   bool registerProduce(const std::string& op, ProduceFunc func);
   ProduceFunc lookupProduce(const std::string& op) const;

   bool registerConsume(const std::string& op, ConsumeFunc func);
   ConsumeFunc lookupConsume(const std::string& op) const;

   static TranslatorRegistry* global();

 private:
   std::unordered_map<std::string, ProduceFunc> produceRegistry;
   std::unordered_map<std::string, ConsumeFunc> consumeRegistry;
};
}

// Macros used to register consume and produce functions.
#define REGISTER_PRODUCE_FUNC(name, fn)                                        \
   REGISTER_PRODUCE_FUNC_UNIQ_HELPER(__COUNTER__, name, fn)

#define REGISTER_PRODUCE_FUNC_UNIQ_HELPER(ctr, name, fn)                       \
   REGISTER_PRODUCE_FUNC_UNIQ(ctr, name, fn)

#define REGISTER_PRODUCE_FUNC_UNIQ(ctr, name, fn)                              \
   static bool unused_ret_val_##ctr __attribute__((unused)) =                  \
       hyper::TranslatorRegistry::global()->registerProduce(name, fn)

#define REGISTER_CONSUME_FUNC(name, fn)                                        \
   REGISTER_CONSUME_FUNC_UNIQ_HELPER(__COUNTER__, name, fn)

#define REGISTER_CONSUME_FUNC_UNIQ_HELPER(ctr, name, fn)                       \
   REGISTER_CONSUME_FUNC_UNIQ(ctr, name, fn)

#define REGISTER_CONSUME_FUNC_UNIQ(ctr, name, fn)                              \
   static bool unused_ret_val_##ctr __attribute__((unused)) =                  \
       hyper::TranslatorRegistry::global()->registerConsume(name, fn)
