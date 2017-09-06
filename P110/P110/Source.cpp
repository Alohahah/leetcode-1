#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//31.09%

class Solution {
public:
    bool isBalanced(TreeNode* root) {
		if (root == nullptr)
			return true;
		
		bool left = isBalanced(root->left);
		bool right = isBalanced(root->right);

		return left && right && abs(maxDepth(root->left) - maxDepth(root->right)) <= 1;		//�ж��������Ƿ���ƽ����,�������Ƿ���ƽ����,�Լ����Ƿ���ƽ���� 
    }

	int maxDepth(TreeNode* node)
	{
		if (node == nullptr)
			return 0;

		return max(maxDepth(node->left) + 1, maxDepth(node->right) + 1);
	}
};