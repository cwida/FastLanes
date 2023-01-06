#include "hyper/codegen/Translator.hpp"

using namespace std;

namespace hyper{

   void Translator::produce(algebra::Operator& op, std::ostream& s){
      // lookup produce function
      auto prod = hyper::TranslatorRegistry::global()->lookupProduce(op.name);
      // render function into s
      prod(op, s);
   }

   void Translator::consume(algebra::Operator& op,algebra::Operator& source, std::ostream& s){
      // lookup consume function
      auto cons = hyper::TranslatorRegistry::global()->lookupConsume(op.name);
      // render function into s
      cons(op, source, s);
   }

}
