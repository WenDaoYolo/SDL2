#include<iostream>

void PrintArr(int* arr,int len)
{
	for(int i=0;i<len;i++)
		std::cout<<arr[i]<<" ";
	std::cout<<std::endl;
}

//10个桶，每个桶又可以存储若干数据，可以定义二维动态数组，或自定义桶结构(比较麻烦)
struct bucketnode
{
	int data;
	bucketnode* next;
};

class bucket
{
	public:
		int len;
		bucketnode* head;
        bucketnode* tail;
		
		bucket()
		{
			this->len=0;
			this->head=new bucketnode;
            this->tail=this->head;
			
			this->head->next=NULL;
			this->head->data=-999;
		}
		
		void Add(int e)
		{
			bucketnode* tmp=new bucketnode;
			tmp->data=e;
            tmp->next=NULL;

            tail->next=tmp;
            tail=tmp;
			this->len++;
		}
		
        void Clear()
		{
			while(this->head->next!=NULL)
			{
				bucketnode* tmp=this->head->next;
				this->head->next=tmp->next;
				delete tmp;
			}
			this->len=0;
            this->tail=this->head;
		}

		~bucket()
		{
			this->Clear();
            delete this->head;
            this->head=NULL;
            this->tail=NULL;
		}
};

int FindMax(int* arr,int len)
{
    int max=arr[0];
    for(int i=1;i<len;i++)
    {
        if(arr[i]>max)
            max=arr[i];
    }
    return max;
}

void RadixSortUp(int* arr,int len)
{
    bucket b1[10];
    int max=FindMax(arr,len);
    int count=0;

    while(max>0)
    {
        max/=10;
        count++;
    }

    int n=1,index=0;
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<len;j++)
        {
            index=(arr[j]/n)%10;
            b1[index].Add(arr[j]);
        }
        n*=10;

        int w=0;
        for(int m=0;m<10;m++)
        {
            bucketnode* find=b1[m].head->next;
            while(find!=NULL)
            {
                arr[w]=find->data;
                find=find->next;
                w++;
            }
            b1[m].Clear();
        }
    }
}

void RadixSortDown(int* arr,int len)
{
	bucket b1[10];
    int max=FindMax(arr,len);
    int count=0;

    while(max>0)
    {
        max/=10;
        count++;
    }

    int n=1,index=0;
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<len;j++)
        {
            index=(arr[j]/n)%10;
            b1[index].Add(arr[j]);
        }
        n*=10;

        int w=0;
        for(int m=9;m>=0;m--)
        {
            bucketnode* find=b1[m].head->next;
            while(find!=NULL)
            {
                arr[w]=find->data;
                find=find->next;
                w++;
            }
            b1[m].Clear();
        }
    }
}

int main()
{
	int arr[]={4,3,2,1,4,828,17,14,122};
	int len=sizeof(arr)/sizeof(int);

    std::cout<<"before:";
	PrintArr(arr,len);

	RadixSortUp(arr,len);
	std::cout<<"after:";
	PrintArr(arr,len);

    RadixSortDown(arr,len);
    std::cout<<"after:";
	PrintArr(arr,len);
	
    return 0;
}