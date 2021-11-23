//
// Created by 0rth0Normal on 19/11/2021.
//
#include <iostream>
#include "Player.h"
#include <cassert>
using namespace wet1_dast;
using std::cout;
using std::endl;
int main()
{
    //first test,check that everything compile allright.
    Player p(1,2);

    //second test,Player shouldn't get either id<=0 or level<0
    try{
        cout<<"first test-start"<<endl;
        Player p1(0,1);//first test-player_id=0;
    }
    catch(std::runtime_error& e)
    {
        e.what();
        cout<<"first test-success"<<endl;
    }
    //second test,Player shouldn't get either id<=0 or level<0
    try{
        cout<<"second test-start"<<endl;
        Player p2(2,-1);//first test-player_id=0;
    }
    catch(std::runtime_error& e)
    {
        cout<<"second test-success"<<endl;
        e.what();
    }
    //third test,Player shouldn't get either id<=0 or level<0
    try{
        cout<<"third test-start"<<endl;
        Player p3(-1,-2);//first test-player_id=0;
    }
    catch(std::runtime_error& e)
    {
        cout<<"third test-success"<<endl;
        e.what();
    }
    cout<<"4th test, checking for player1==player2"<<endl;
    Player p4(1,1);
    Player p5(1,2);
    Player p6(2,2);
    Player p7(3,4);
    Player p8(1,1);
    cout<<"(1,1)!=(1,2)"<<endl;//different level
    assert(!(p4==p5));
    cout<<"(1,2)!=(2,2)"<<endl;//different id
    assert(!(p5==p6));
    cout<<"(1,1)==(1,1)"<<endl;//same
    assert(p4==p8);
    cout<<"(1,1)!=(3,4)"<<endl;//different id and different level
    assert (!(p4==p7));
    cout<<"changing p5 level to 1,then check again."<<endl;
    p5.setLevel(1);
    assert(p4==p5);
    cout<<"success in player1==player2"<<endl;
    //basiclly,we're checking only for
    cout<<"5th test,checking player1==id"<<endl;
    Player p9(1,2);
    assert(p9==1);
    assert(!(p9==2));
    cout<<"success in player1==id"<<endl;
    cout<<"testing p1<=p2"<<endl;
    cout<<"first test , p1<=p1"<<endl;
    Player ziv1(206606709,23);
    Player tom1(315155671,22);
    Player ziv2(206606709,24);
    Player tom2(1,22);
    //same id ,same level
    assert(ziv1<=ziv1);
    //higher level, same id .
    assert(ziv1<=ziv2);
    //same level, lower id.
    assert(tom1<=tom2);
    //higer level,lower id.
    assert(tom1<=ziv1);
    //lower level,higher id
    assert(!(ziv1<=tom1));
    cout<<ziv1;
    return 0;
}