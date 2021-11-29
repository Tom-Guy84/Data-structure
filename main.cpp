
#include <iostream>
#include <cassert>
#include "library1.h"
using std::cout;
using std::endl;
int main()
{
   void* manager=Init();
   assert(AddGroup(manager,1)==SUCCESS);
   assert(AddPlayer(manager,1,1,1)==SUCCESS);
   assert(AddGroup(manager,2)==SUCCESS);
   assert(AddPlayer(manager,4,2,1)==SUCCESS);
   assert(AddPlayer(manager,5,2,2)==SUCCESS);
   assert(ReplaceGroup(manager,2,1)==SUCCESS);
   assert(RemovePlayer(manager,4) == SUCCESS);
   Quit(&manager);

}
