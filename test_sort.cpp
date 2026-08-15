#include<iostream>
#include<time.h>

////////////////////////////////////////////////////////////////////////
void produce_random_num(int* arr,int len)
{
    srand((unsigned int)time(NULL));
    //...或者c++的chrono时间库
}

void BubbleSort(int* arr,int len)
{
    //start
    std::cout<<"called test1!"<<std::endl;
    //end
}
////////////////////////////////////////////////////////////////////////

void TestSort(const char* str,void(*fun_ptr)(int*,int),int* arr,int len)
{
    std::cout<<str<<std::endl;
    fun_ptr(arr,len);
}

int main()
{
    int arr[]={1,2,3,4};
    int len=0;

    const char* str="BubbleSort:";
    TestSort(str,BubbleSort,arr,len);

    return 0;
}