#include<iostream>
#define RLEN 5
#define CLEN RLEN

void OutputGraphInfo(const char* str,int(*graph)[RLEN])
{
    std::cout<<str<<std::endl;
    for(int i=0;i<RLEN;i++)
    {
        for(int j=0;j<CLEN;j++)
        {
            if(graph[i][j]>0)
                std::cout<<"vertex"<<i+1<<" to vertex"<<j+1<<" have edge,value is "<<graph[i][j]<<std::endl;
        }
    }
}

int main()
{
    //带权有向图的邻接矩阵
    int graph1[RLEN][CLEN]=
    {
        {-1,5,-1,4,-1},
        {-1,-1,-1,-1,4},
        {-1,1,-1,-1,-1},
        {-1,-1,2,-1,-1},
        {-1,-1,2,-1,-1}
    };
    
    //带权无向图的邻接矩阵
    int graph2[RLEN][CLEN]=
    {
        {-1,5,-1,4,-1},
        {5,-1,1,-1,4},
        {-1,1,-1,2,2},
        {4,-1,2,-1,-1},
        {-1,4,2,-1,-1}
    };

    OutputGraphInfo("graph1 info:",graph1);
    OutputGraphInfo("graph2 info:",graph2);

    return 0;  
}