#include<iostream>

struct set_node
{
    int father;
};

set_node sets[9];

void InitSetNode()
{
    for(int i=0;i<9;i++)
        sets[i].father=i;
}

int FindSet(int x)
{
    if(sets[x].father==x)
        return x;
        //sets[x].father<0
    else
        return FindSet(sets[x].father);
        //return sets[x].father=FindSet(sets[x].father);
}

void UnionSet(int x,int y)
{    
    int xf=FindSet(x);
    int yf=FindSet(y);

    if(xf==yf)
        return; 

    sets[yf].father=xf;
}

void CreateSet()
{
    //set1: 1(root)、4、8
    UnionSet(1,4);
    UnionSet(1,8);

    //set2：3(root)、5、2、7
    UnionSet(3,5);
    UnionSet(3,2);
    UnionSet(3,7);
    
    //set3：6(root)、0
    UnionSet(6,0);

    std::cout<<"4's set:"<<FindSet(4)<<std::endl;
    std::cout<<"7's set:"<<FindSet(7)<<std::endl;
    std::cout<<"0's set:"<<FindSet(0)<<std::endl;
}

void TestUnion()
{
    UnionSet(4,7);
    std::cout<<"4's set:"<<FindSet(4);
    std::cout<<",4's father:"<<sets[4].father<<std::endl;

    std::cout<<"7's set:"<<FindSet(7);
    std::cout<<",7's father:"<<sets[7].father<<std::endl;
}

int FindSetProcess(int x)
{
    if(sets[x].father==x)
        return x;
    else
        return sets[x].father=FindSetProcess(sets[x].father);
}

void TestFindSetProcess()
{
    std::cout<<"after process"<<std::endl;
    std::cout<<"4's set:"<<FindSetProcess(4);
    std::cout<<",4's father:"<<sets[4].father<<std::endl;

    std::cout<<"7's set:"<<FindSetProcess(7);
    std::cout<<",7's father:"<<sets[7].father<<std::endl;
}

int main()
{
    InitSetNode();
    CreateSet();

    TestUnion();
    TestFindSetProcess();

    return 0;
}