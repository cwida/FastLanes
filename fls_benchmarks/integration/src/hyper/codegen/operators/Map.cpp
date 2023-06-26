#include "hyper/codegen/Translator.hpp"
#include <iostream>

namespace hyper{
   namespace translators{
      void mapProduce(algebra::Operator& op, std::ostream& s){
         auto& map = static_cast<algebra::Map&>(op);
         Translator::produce(*map.child.get(), s);
      }
      void mapConsume(algebra::Operator& op, algebra::Operator&, std::ostream& s){
         s << "x = t.a + z;\n";
         Translator::consume(*op.parent, op, s);
      }
   }
}

REGISTER_PRODUCE_FUNC("map", hyper::translators::mapProduce);
REGISTER_CONSUME_FUNC("map", hyper::translators::mapConsume);
