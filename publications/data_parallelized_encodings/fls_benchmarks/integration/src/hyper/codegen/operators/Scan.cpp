#include "hyper/codegen/Translator.hpp"
#include <iostream>

namespace hyper{
   namespace translators{
      void scanProduce(algebra::Operator& op, std::ostream& s){
         auto& scan = static_cast<algebra::Scan&>(op);
         auto& rel = scan.rel;

         for(auto& attrIt : rel.attributes){
           auto& name = attrIt.first;
           auto& attr = attrIt.second;
           //TODO: attr type to c++ type
           s << "auto& " << name << "_vec="<<rel.name<<"attributes.typedAccess<"<< attr.type->cppname() <<">();\n";
         }
        s << "for(int i=0;i<"<< rel.name <<".tup_c,++i){\n";
        for(auto& attrIt : rel.attributes){
          auto& name = attrIt.first;
          auto& attr = attrIt.second;
          s << "auto& " << name << "="<<attr.name<<"_vec[i];\n";
        }
        Translator::consume(*op.parent, op, s);
        s << "}\n";
      }
   }
}

REGISTER_PRODUCE_FUNC("scan", hyper::translators::scanProduce);
