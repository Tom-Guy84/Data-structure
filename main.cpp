//
// Created by 0rth0Normal on 19/11/2021.
//
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
   Group g1(1);
   Group g2(1);
   assert(g1==g2);
   Group g3(2);
   assert(!(g3<=g1));
   AVLTree<int> t;
    int* b(new int(1));
   t.insert(*b);
    int* a(t.find(1));
   assert(*a==1);
   t.remove(*b);
    int* c(t.find(*b));
   assert(c==nullptr);
    int* d(new int(1));
   t.insert(*d);
    int* e(new int(2));
   t.insert(*e);
    int* f(new int(3));
   t.insert(*f);
   t.printTree();
   AVLTree<int> t2;
   int* aa(new int(9));
   int* bb(new int (1010));
   t2.insert(*aa);
   t2.insert(*bb);
   t2.printTree();
   combineTrees(t, t2);
   t.printTree();
   delete b;
   delete d;
   delete e;
   delete f;
   delete aa;
   delete bb;
   return 0;
}