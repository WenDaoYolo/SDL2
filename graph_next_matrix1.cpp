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
            if(graph[i][j]==1)
                std::cout<<"vertex"<<i+1<<" to vertex"<<j+1<<" have edge"<<std::endl;
        }
    }
}

int main()
{
    //有向图的邻接矩阵
    int graph1[RLEN][CLEN]=
    {
        {0,1,0,1,0},
        {0,0,0,0,1},
        {0,1,0,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0}
    };
    
    //无向图的邻接矩阵
    int graph2[RLEN][CLEN]=
    {
        {0,1,0,1,0},
        {1,0,1,0,1},
        {0,1,0,1,1},
        {1,0,1,0,0},
        {0,1,1,0,0}
    };

    OutputGraphInfo("graph1 info:",graph1);
    OutputGraphInfo("graph2 info:",graph2);

    return 0;  
}