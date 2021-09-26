#pragma
#include<iostream>
using namespace std;

template<class T>
class AVLTreeNode {  //����ƽ�����Ľ����
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
	// ���к������൱���ⲿ�ӿ�
	AVLTree() :root(nullptr) {
	
	};

	//��ȡ���ĸ߶�
	int height();

	//ǰ�к������
	void preOrder();
	void inOrder();
	void postOrder();

	//����ֵΪkey�Ľڵ�
	AVLTreeNode<T>* Search(T key);

	void Insert(T key);
	void Remove(T key);
	

private:
	// ��ȡ���ĸ߶�
	int height(AVLTreeNode<T>* rootNode);
	
	//ǰ�к������
	void preOrder(AVLTreeNode<T>* rootNode) const;
	void inOrder(AVLTreeNode<T>* rootNode) const;
	void postOrder(AVLTreeNode<T>* rootNode) const;

	//����ֵΪkey�Ľ�㣬���ظý��
	AVLTreeNode<T>* Search(AVLTreeNode<T>* x, T key) const;

	//LL:����ת(������תһ��)
	AVLTreeNode<T>* LL_Rotation(AVLTreeNode<T>* rootNode);

	//RR �ҵ���ת(������תһ��)
	AVLTreeNode<T>* RR_Rotation(AVLTreeNode<T>* rootNode);

	//LR 
	AVLTreeNode<T>* LR_Rotation(AVLTreeNode<T>* rootNode);

	//RL
	AVLTreeNode<T>* RL_Rotation(AVLTreeNode<T>* rootNode);

	// ���뺯��
	AVLTreeNode<T>* Insert(AVLTreeNode<T>* &rootNode, T val);

	// ɾ��AVL��(tree)�еĽ��(node)�������ر�ɾ���Ľ��
	AVLTreeNode<T>* Remove(AVLTreeNode<T>* &rootNode, AVLTreeNode<T>* delnode);

	//ƽ���������ֵ������Сֵ���
	AVLTreeNode<T>* minNode(AVLTreeNode<T>* rootNode);
	AVLTreeNode<T>* maxNode(AVLTreeNode<T>* rootNode);
}; 

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* rootNode) { //��rootNodeΪ�������ĸ߶�
	if (rootNode == nullptr) {
		return 0;
	}
	return rootNode->height;
}

template<class T>
int AVLTree<T>::height() {   //�������ĸ߶�
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

template<class T>  //LL����µ���ת,���ҷ�����תһ�μ���
AVLTreeNode<T>* AVLTree<T>::LL_Rotation(AVLTreeNode<T>* rootNode) {
	AVLTreeNode<T>* newRoot = rootNode->left;
	rootNode->left = newRoot->right;  // ��newRoot����������rootNode
	newRoot->right = rootNode;  //�������ӹ�ϵ(Ҳ������ת)

	newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
	rootNode->height = max(height(rootNode->left), height(rootNode->right)) + 1;
	return newRoot;  //������ת��ɺ����ĸ�
}

template<class T>  //RR����µ���ת,Ҳ����������תһ��
AVLTreeNode<T>* AVLTree<T>::RR_Rotation(AVLTreeNode<T>* rootNode) {
	AVLTreeNode<T>* newRoot = rootNode->right;
	rootNode->right = newRoot->left;
	newRoot->left = rootNode;  //�������ӹ�ϵ
	newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
	rootNode->height = max(height(rootNode->left), height(rootNode->right)) + 1;
	return newRoot;  //������ת��ɺ����ĸ�
}

template<class T>  //LR����������������(RR)����������������(LL)
AVLTreeNode<T>* AVLTree<T>::LR_Rotation(AVLTreeNode<T>* rootNode) {
	rootNode->left = RR_Rotation(rootNode->left);
	return LL_Rotation(rootNode);
}

template<class T>  //RL ��������������(LL) ��������������(RR)
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
	else if (val < rootNode->val) {  //˵���½�������������
		rootNode->left = Insert(rootNode->left, val);
		int root_factor = height(rootNode->left) - height(rootNode->right); //����ƽ������
		if (root_factor > 1) {  //���ֲ�ƽ�⣬��Ϊ�������������������ȷʵ��һ��ΪL
			if (val < rootNode->left->val) {  //�ڶ���ҲΪL LL��
				rootNode = LL_Rotation(rootNode);  //ƽ�⴦��
			}
			else {   //LR��
				rootNode = LR_Rotation(rootNode);
			}
		}
	}
	else if (val > rootNode->val) {  //���������������ȿ���ȷʵ��һ��ΪR
		rootNode->right = Insert(rootNode->right, val);
		int root_factor = height(rootNode->left) - height(rootNode->right); //����ƽ������
		if (root_factor < -1) {  ////���ֲ�ƽ�⣬��Ϊ������������������ȿ���ȷʵ��һ��ΪR
			if (val > rootNode->right->val) {  //������������������ ΪRR��
				rootNode = RR_Rotation(rootNode);
			}
			else   // RL��
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
	if (del->val < rootNode->val) {  //��ɾ���Ľڵ���rootNode����������
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
		if (root_factor == 2 ) { //��Ϊ�������н�㱻ɾ�����߶Ȼ��½�
			if (height(rootNode->left->right) > height(rootNode->left->left)) {
				rootNode = LR_Rotation(rootNode);
			}
			else {
				rootNode = LL_Rotation(rootNode);
			}
		}
	}
	else {  //rootNode������Ҫɾ���ĵ�

		if (rootNode->left != nullptr && rootNode->right != nullptr) {
			if (height(rootNode->left) > height(rootNode->right)) {
				//tree���������Ƚϸ�
				//ȡ��tree�������������ڵ�
				//���ýڵ���Ϊrootnode
				//ɾ�������ڵ�  �ݹ�ʵ��
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

