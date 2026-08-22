#include<iostream>

typedef char elemtype;

struct BTreeNode
{
	elemtype data;
	BTreeNode* left;
	BTreeNode* right;
};

struct BTree
{
	BTreeNode root;
};

void PrevOrderSearch(BTreeNode* root)
{
	if(root==NULL)
		return;

	std::cout<<root->data<<" ";
	PrevOrderSearch(root->left);
	PrevOrderSearch(root->right);
}

void MidOrderSearch(BTreeNode* root)
{
	if(root==NULL)
		return;

	MidOrderSearch(root->left);
	std::cout<<root->data<<" ";
	MidOrderSearch(root->right);
}

void BehindOrderSearch(BTreeNode* root)
{
	if(root==NULL)
		return;

	BehindOrderSearch(root->left);
	BehindOrderSearch(root->right);
	std::cout<<root->data<<" ";
}

void TestSearch(BTree& bt)
{
	BTreeNode* tmp2=new BTreeNode;
	BTreeNode* tmp3=new BTreeNode;
	BTreeNode* tmp4=new BTreeNode;
	BTreeNode* tmp5=new BTreeNode;

	bt.root.data='A';
	tmp2->data='B';
	tmp3->data='C';
	tmp4->data='D';
	tmp5->data='E';

	bt.root.left=tmp2;
	bt.root.right=tmp3;
	tmp2->left=tmp4;
	tmp2->right=NULL;
	tmp3->left=NULL;
	tmp3->right=tmp5;
	tmp4->left=NULL;
	tmp4->right=NULL;
	tmp5->left=NULL;
	tmp5->right=NULL;

	PrevOrderSearch(&(bt.root));
	std::cout<<std::endl;
	MidOrderSearch(&(bt.root));
	std::cout<<std::endl;
	BehindOrderSearch(&(bt.root));
	std::cout<<std::endl;

	delete tmp5;
	delete tmp4;
	delete tmp3;
	delete tmp2;
}

int main()
{
	BTree bt;
	TestSearch(bt);

    return 0;
}