#pragma
#include<iostream>
using namespace std;

template<class T>
class AVLTreeNode {  //定义平衡树的结点类
public:
	T val;
	int height;
	AVLTreeNode* left;
	AVLTreeNode* right;
	AVLTreeNode(T value, AVLTreeNode* l = nullptr, AVLTreeNode* r = nullptr) :val(value), left(l), right(r), height(0) {

	}
};
template<class T>
class AVLTree {
public:
	AVLTreeNode<T>* root;
public:
	// 公有函数，相当于外部接口
	AVLTree() :root(nullptr) {
	
	};

	//获取树的高度
	int height();

	//前中后序遍历
	void preOrder();
	void inOrder();
	void postOrder();

	//查找值为key的节点
	AVLTreeNode<T>* Search(T key);

	void Insert(T key);
	void Remove(T key);
	

private:
	// 获取树的高度
	int height(AVLTreeNode<T>* rootNode);
	
	//前中后序遍历
	void preOrder(AVLTreeNode<T>* rootNode) const;
	void inOrder(AVLTreeNode<T>* rootNode) const;
	void postOrder(AVLTreeNode<T>* rootNode) const;

	//搜索值为key的结点，返回该结点
	AVLTreeNode<T>* Search(AVLTreeNode<T>* x, T key) const;

	//LL:左单旋转(向右旋转一次)
	AVLTreeNode<T>* LL_Rotation(AVLTreeNode<T>* rootNode);

	//RR 右单旋转(向左旋转一次)
	AVLTreeNode<T>* RR_Rotation(AVLTreeNode<T>* rootNode);

	//LR 
	AVLTreeNode<T>* LR_Rotation(AVLTreeNode<T>* rootNode);

	//RL
	AVLTreeNode<T>* RL_Rotation(AVLTreeNode<T>* rootNode);

	// 插入函数
	AVLTreeNode<T>* Insert(AVLTreeNode<T>* &rootNode, T val);

	// 删除AVL树(tree)中的结点(node)，并返回被删除的结点
	AVLTreeNode<T>* Remove(AVLTreeNode<T>* &rootNode, AVLTreeNode<T>* delnode);

	//平衡树的最大值结点和最小值结点
	AVLTreeNode<T>* minNode(AVLTreeNode<T>* rootNode);
	AVLTreeNode<T>* maxNode(AVLTreeNode<T>* rootNode);
}; 

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* rootNode) { //以rootNode为根的树的高度
	if (rootNode == nullptr) {
		return 0;
	}
	return rootNode->height;
}

template<class T>
int AVLTree<T>::height() {   //整棵树的高度
	return height(this->root);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minNode(AVLTreeNode<T>* rootNode) {
	if (rootNode->left == nullptr) {
		return rootNode;
	}
	else {
		return minNode(rootNode->left);
	}
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maxNode(AVLTreeNode<T>* rootNode) {
	if (rootNode->right == nullptr) {
		return rootNode;
	}
	else {
		return maxNode(rootNode->right);
	}
}

template<class T>  //LL情况下的旋转,向右方向旋转一次即可
AVLTreeNode<T>* AVLTree<T>::LL_Rotation(AVLTreeNode<T>* rootNode) {
	AVLTreeNode<T>* newRoot = rootNode->left;
	rootNode->left = newRoot->right;  // 把newRoot的左子树给rootNode
	newRoot->right = rootNode;  //调换父子关系(也就是旋转)

	newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
	rootNode->height = max(height(rootNode->left), height(rootNode->right)) + 1;
	return newRoot;  //返回旋转完成后树的根
}

template<class T>  //RR情况下得旋转,也就是向左旋转一次
AVLTreeNode<T>* AVLTree<T>::RR_Rotation(AVLTreeNode<T>* rootNode) {
	AVLTreeNode<T>* newRoot = rootNode->right;
	rootNode->right = newRoot->left;
	newRoot->left = rootNode;  //调换父子关系
	newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
	rootNode->height = max(height(rootNode->left), height(rootNode->right)) + 1;
	return newRoot;  //返回旋转完成后树的根
}

template<class T>  //LR，左子树先向左旋(RR)，整棵树再向右旋(LL)
AVLTreeNode<T>* AVLTree<T>::LR_Rotation(AVLTreeNode<T>* rootNode) {
	rootNode->left = RR_Rotation(rootNode->left);
	return LL_Rotation(rootNode);
}

template<class T>  //RL 右子树先向右旋(LL) 整棵树再向左旋(RR)
AVLTreeNode<T>* AVLTree<T>::RL_Rotation(AVLTreeNode<T>* rootNode) {
	rootNode->right = LL_Rotation(rootNode->right);
	return RR_Rotation(rootNode);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::Insert(AVLTreeNode<T>* &rootNode, T val) {
	if (rootNode == nullptr) {
		rootNode = new AVLTreeNode<T>(val);
		if (rootNode == nullptr) {
			std::cout << "Error: create node failed!" << endl;
			return nullptr;
		}
	}
	else if (val < rootNode->val) {  //说明新结点插入了左子树
		rootNode->left = Insert(rootNode->left, val);
		int root_factor = height(rootNode->left) - height(rootNode->right); //计算平衡因子
		if (root_factor > 1) {  //出现不平衡，因为插入的是左子树，首先确实第一个为L
			if (val < rootNode->left->val) {  //第二个也为L LL型
				rootNode = LL_Rotation(rootNode);  //平衡处理
			}
			else {   //LR型
				rootNode = LR_Rotation(rootNode);
			}
		}
	}
	else if (val > rootNode->val) {  //插入右子树，首先可以确实第一个为R
		rootNode->right = Insert(rootNode->right, val);
		int root_factor = height(rootNode->left) - height(rootNode->right); //计算平衡因子
		if (root_factor < -1) {  ////出现不平衡，因为插入的是右子树，首先可以确实第一个为R
			if (val > rootNode->right->val) {  //插入右子树的右子树 为RR型
				rootNode = RR_Rotation(rootNode);
			}
			else   // RL型
			{
				rootNode = RL_Rotation(rootNode);
			}
		}
	}
	else {
		std::cout << "The node has exists in tree" << endl;
	}
	rootNode->height = max(height(rootNode->left), height(rootNode->right)) + 1;
	return rootNode;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::Search(AVLTreeNode<T>* rootNode, T val) const {
	if (rootNode == nullptr || rootNode->val == val)
		return rootNode;
	if (val < rootNode->val) {
		return Search(rootNode->left, val);
	}
	else {
		return Search(rootNode->right, val);
	}
}

template<class T>
void AVLTree<T>::Insert(T val) {
	Insert(this->root, val);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::Remove(AVLTreeNode<T>* &rootNode, AVLTreeNode<T>* del) {
	if (rootNode == nullptr || del == nullptr) {
		return nullptr;
	}
	if (del->val < rootNode->val) {  //待删除的节点在rootNode的左子树中
		rootNode->left = Remove(rootNode->left, del);
		int root_factor = height(rootNode->left) - height(rootNode->right);
		if (root_factor == -2) {
			if (height(rootNode->right->left) > height(rootNode->right->right)) {
				rootNode = RL_Rotation(rootNode);
			}
			else {
				rootNode = RR_Rotation(rootNode);
			}
		}
	}
	else if (del->val > rootNode->val) {
		rootNode->right = Remove(rootNode->right, del);
		int root_factor = height(rootNode->left) - height(rootNode->right);
		if (root_factor == 2 ) { //因为右子树有结点被删除，高度会下降
			if (height(rootNode->left->right) > height(rootNode->left->left)) {
				rootNode = LR_Rotation(rootNode);
			}
			else {
				rootNode = LL_Rotation(rootNode);
			}
		}
	}
	else {  //rootNode正好是要删除的点

		if (rootNode->left != nullptr && rootNode->right != nullptr) {
			if (height(rootNode->left) > height(rootNode->right)) {
				//tree的左子树比较高
				//取出tree的左子树的最大节点
				//将该节点作为rootnode
				//删除该最大节点  递归实现
				AVLTreeNode<T>* maxNode1 = maxNode(rootNode->left);
				rootNode->val = maxNode1->val;
				rootNode->left = Remove(rootNode->left, maxNode1);
			}
			else {
				AVLTreeNode<T>* minNode1 = minNode(rootNode->right);
				rootNode->val = minNode1->val;
				rootNode->right = Remove(rootNode->right, minNode1);
			}
		}
		else {
			AVLTreeNode<T>* temp = rootNode;
			rootNode = (rootNode->left == nullptr) ? rootNode->right : rootNode->left;
			delete temp;
		}
	}
	return rootNode;
}

template<class T>
void AVLTree<T>::Remove(T val) {
	AVLTreeNode<T>* tem;
	if ((tem = Search(this->root, val)) != nullptr) {
		this->root = Remove(this->root, tem);
	}
}

template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* rootNode) const {
	if (rootNode != nullptr) {
		cout << rootNode->val << " ";
		preOrder(rootNode->left);
		preOrder(rootNode->right);
	}
}

template<class T>
void AVLTree<T>::preOrder() {
	preOrder(this->root);
}

template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* rootNode) const {
	if (rootNode != nullptr) {
		inOrder(rootNode->left);
		cout << rootNode->val << " ";
		inOrder(rootNode->right);
	}
}

template<class T>
void AVLTree<T>::inOrder() {
	inOrder(this->root);
}

template<class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* rootNode) const {
	if (rootNode != nullptr) {
		postOrder(rootNode->left);
		postOrder(rootNode->right);
		cout << rootNode->val << " ";
	}
}

template<class T>
void AVLTree<T>::postOrder() {
	postOrder(this->root);
}

