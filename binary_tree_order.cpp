#include<iostream>

typedef char elemtype;

//abcde
elemtype tit[10]={'#','A','B','#','C','#','#','#','D','E'};

void TestTree()
{
    int index=1*2;
    if(tit[index]=='#')
        std::cout<<tit[1]<<"'s left child is not exist"<<std::endl;
    else
        std::cout<<tit[1]<<"'s left child:"<<tit[index]<<std::endl;

    index=1*2+1;
    if(tit[index]=='#')
        std::cout<<tit[1]<<"'s left child is not exist"<<std::endl;
    else
        std::cout<<tit[1]<<"'s left child:"<<tit[index]<<std::endl;

    index=8/2;
    std::cout<<tit[8]<<"'s parent:"<<tit[index]<<std::endl;

    index=9/2;
    std::cout<<tit[9]<<"'s parent:"<<tit[index]<<std::endl;
}

int main()
{
    //分别测试A的左右孩子，DE的父结点
    TestTree();
    return 0;
}