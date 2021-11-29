
#include <iostream>
#include "Player.h"
#include <cassert>
#include "AVLTree.h"
#include "PlayerManager.h"
using namespace wet1_dast;
using std::cout;
using std::endl;
int main()
{
   PlayerManager* manager=new PlayerManager();
    assert(manager->AddGroup(1)==SUCCESS);
   assert(manager->AddPlayer(1,1,1)==SUCCESS);
   assert(manager->AddGroup(2)==SUCCESS);
   assert(manager->AddPlayer(4,2,1)==SUCCESS);
   assert(manager->AddPlayer(5,2,2)==SUCCESS);
   assert(manager->ReplaceGroup(2,1)==SUCCESS);
   assert(manager->RemovePlayer(4) == SUCCESS);

}
