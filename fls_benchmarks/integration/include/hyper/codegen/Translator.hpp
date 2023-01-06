#pragma once

#include "common/algebra/Operators.hpp"
#include "hyper/codegen/TranslatorRegistry.hpp"

namespace hyper{

   class Translator{
   public:
      static void produce(algebra::Operator& op, std::ostream& s);
      static void consume(algebra::Operator& op, algebra::Operator& source , std::ostream& s);
   };
}
