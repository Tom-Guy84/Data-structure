
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
    AVLTree<int> tree123;
    int* one=new int(1);
    int* two=new int(2);
    int* three=new int(3);
    AVLTree<int> tree456;
    int* four=new int(4);
    int* five=new int(5);
    int* six=new int(6);
    tree123.insert(*three);
    tree123.insert(*two);
    tree123.insert(*one);
    tree456.insert(*four);
    tree456.insert(*five);
    tree456.insert(*six);
    try {
        tree123.remove(*five);
    }
    catch(AVLTree<int>::ItemNotExist& a)
    {
        cout<<"ok to remove"<<endl;
    }
    try {
        tree123.insert(*one);
    }
    catch (AVLTree<int>::ItemExist& b){
        cout<<"ok to insert"<<endl;
    }
    tree456.remove(*four);
    cout<<" after tree456.remove(*four);"<<endl;
    tree456.printTree();
    try {
        delete (tree456.remove(*four));
    }
    catch(AVLTree<int>::ItemNotExist& c)
    {
        cout<<"ok to remove after remove"<<endl;
    }
    tree456.insert(*four);
    tree456.printTree();
    cout<<"ok"<<endl;
    delete tree456.remove(*five);
    cout<<"ok 2"<<endl;
    cout<<"combi combi"<<endl;
    combineTrees(tree456,tree123);
    tree456.printTree();
    cout<<"combi combi"<<endl;
}
