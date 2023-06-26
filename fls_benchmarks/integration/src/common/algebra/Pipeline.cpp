#include "common/algebra/Pipeline.hpp"

using namespace std;

namespace algebra{

   Pipeline& Pipeline::map(){
      root = make_unique<Map>(move(root));
      return *this;
   }

   Pipeline& Pipeline::scan(runtime::Relation& r){
      root = make_unique<Scan>(r);
      return *this;
   }

  Pipeline& Pipeline::print(std::vector<std::string> attrs){
    root = make_unique<Print>(move(root), move(attrs));
      return *this;
   }
   Pipeline& Pipeline::hashjoin(Pipeline& m){
      root = make_unique<HashJoin>(move(m.root), move(root));
      return *this;
   }


   void Pipeline::print(std::ostream& s)const{
      root->print(s);
   }
}
