#include<iostream>

typedef char elemtype;

struct BTreeNode
{
	elemtype data;
	int lflag,rflag;
	BTreeNode* left;
	BTreeNode* right;
};

struct BTree
{
	BTreeNode root;
};

BTree bt;
BTreeNode* tmp1=new BTreeNode;
BTreeNode* tmp2=new BTreeNode;
BTreeNode* tmp3=new BTreeNode;
BTreeNode* tmp4=new BTreeNode;
BTreeNode* tmp5=new BTreeNode;
BTreeNode* tmp6=new BTreeNode;

void MidOrderSearch(BTreeNode* root)
{
	if(root==NULL)
		return;

	MidOrderSearch(root->left);
	std::cout<<root->data<<" ";
	MidOrderSearch(root->right);
}

void MidThreadBTreeSearch(BTree& bt)
{
    //找中序序列的第一个结点，即左子树的最深左孩子
    BTreeNode* first=bt.root.left;
    if(first==NULL)
        return;

    while(first->left!=NULL&&first->lflag==0)
        first=first->left;
    std::cout<<first->data<<" ";

    while(true)
    {
        if(first->rflag==1)//右指针是线索
        {
            if(first->right==NULL)//最后一个结点也遍历完了
                return;
            else
            {
                first=first->right;
                std::cout<<first->data<<" ";
            }
        }
        else//右指针是孩子
        {
            first=first->right;
            //找右子树的最深左孩子
            while(first->left!=NULL&&first->lflag==0)
                first=first->left;
            std::cout<<first->data<<" "; 
        }
    }

}

void CreateBTree()
{
    bt.root.data='A';
    tmp1->data='B';
    tmp2->data='C';
    tmp3->data='D';
    tmp4->data='E';
    tmp5->data='F';
    tmp6->data='G';
    
    bt.root.left=tmp1;
    bt.root.lflag=0;
    bt.root.right=tmp2;
    bt.root.rflag=0;

    tmp1->rflag=0;
    tmp1->right=tmp3;
    tmp1->left=NULL;

    tmp2->lflag=0;
    tmp2->left=tmp4;
    tmp2->right=NULL;

    tmp3->lflag=0;
    tmp3->left=tmp5;
    tmp3->right=NULL;

    tmp4->rflag=0;
    tmp4->right=tmp6;
    tmp4->left=NULL;

    tmp5->left=NULL;
    tmp5->right=NULL;
    tmp6->left=NULL;
    tmp6->right=NULL;
}

void CreateMidOrderThreadBTree()
{
    tmp1->lflag=1;
    tmp2->rflag=1;

    tmp3->right=&(bt.root);
    tmp3->rflag=1;

    tmp4->left=&(bt.root);
    tmp4->lflag=1;

    tmp5->left=tmp1;
    tmp5->lflag=1;
    tmp5->right=tmp3;
    tmp5->rflag=1;

    tmp6->left=tmp4;
    tmp6->lflag=1;
    tmp6->right=tmp2;
    tmp6->rflag=1;
}

void DestroyBTree()
{
    delete tmp6;
	delete tmp5;
	delete tmp4;
	delete tmp3;
	delete tmp2;
	delete tmp1;
}

void TestThreadBTree()
{
	//构造二叉树(中序序列BFDAEGC)
	CreateBTree();
    //中序递归遍历
    MidOrderSearch(&(bt.root));
    std::cout<<std::endl;
    //构造中序线索二叉树
    CreateMidOrderThreadBTree();
    //中序线索二叉树遍历
    MidThreadBTreeSearch(bt);
	//销毁二叉树
    DestroyBTree();
}

int main()
{
	TestThreadBTree();

	return 0;
}