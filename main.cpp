
// Created by  on 19/11/2021.
//
#include <iostream>
#include "Player.h"
#include <cassert>
#include "AVLTree.h"
#include "PlayerManager.h"

using namespace wet1_dast;
using std::cout;
using std::endl;

void func1();

void func2();

int main() {
    func1();
    AVLTree<int> tm1m212; //LR
    AVLTree<int> tm6132; //RL
    int *minus_one = new int(-1);
    int *minus_two = new int(-2);
    int *one_LR = new int(1);
    int *two = new int(2);
    int *minus_six = new int(-6);
    int *one_RL = new int(1);
    int *three = new int(3);
    int *two_RL = new int(2);
    tm1m212.insert(*minus_one);//*minus_one
    tm1m212.insert(*minus_two);
    tm1m212.insert(*one_LR);
    tm1m212.insert(*two);
    tm1m212.printTree();
    tm6132.insert(*minus_six);
    tm6132.insert(*three);
    tm6132.insert(*one_RL);
    tm6132.insert(*two_RL);
    tm6132.printTree();
    //lets mess around abit
    delete tm6132.remove(*one_RL);
    delete tm1m212.remove(*two);
    try {
        delete tm6132.remove(*one_LR);
    }
    catch (AVLTree<int>::ItemNotExist &a) {
        std::cout << "good" << endl;
    }
    combineTrees(tm6132,tm1m212);
    tm6132.printTree();
    func2();

}

void func1() {
    cout << " not extremist,just ambitious ;)" << endl;

}

void func2() {
    cout << "good night tom" << endl;
}