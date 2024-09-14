#include "hyper/codegen/Translator.hpp"
#include <iostream>

namespace hyper{
   namespace translators{
      void printProduce(algebra::Operator& op, std::ostream& s){
         auto& print = static_cast<algebra::Print&>(op);
         Translator::produce(*print.child.get(), s);
      }
     void printConsume(algebra::Operator& /*op*/, algebra::Operator&, std::ostream& s){
         s << "cout << x;\n";
      }
   }
}

REGISTER_PRODUCE_FUNC("print", hyper::translators::printProduce);
REGISTER_CONSUME_FUNC("print", hyper::translators::printConsume);
