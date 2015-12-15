#include "std_headers.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


class Solution {
public:
	void process(TreeNode* node) {
		cout << node->val << " ";
	}

	void inorderTraversal(struct TreeNode* root, vector<int>& res) {
		std::stack<TreeNode*> parentList;
		bool init = true;
		TreeNode* currentRoot = root;
		if (currentRoot == NULL)
			return;
		parentList.push(root);
		while (!parentList.empty()) {
			if (currentRoot && currentRoot->left) {
				parentList.push(currentRoot->left);
				currentRoot = currentRoot->left;
				continue;
			}

			currentRoot = parentList.top();
			parentList.pop();
			res.push_back(currentRoot->val);

			if (currentRoot->right)
				parentList.push(currentRoot->right);

			currentRoot = currentRoot->right;
		}
	}

	vector<int> inorderTraversal(TreeNode* root) {
		int returnSize = 0;
		vector<int> res;
		inorderTraversal(root, res);
		return res;
	}
};