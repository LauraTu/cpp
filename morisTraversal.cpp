#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode (int x): val(x),left(NULL),right(NULL) {}
};

TreeNode* createNode(vector<int> v, int index){
	if (v[index] == -1) return NULL;
	TreeNode* new_node = new TreeNode(0);
	new_node->val = v[index];
	new_node->left = NULL;
	new_node->right = NULL;
	if ((2*index+1) < v.size()) {
		new_node->left = createNode(v, 2*index+1);
	}
	if ((2*index+2) < v.size()) {
		new_node->right = createNode(v, 2*index+2);
	}
	return new_node;
}

vector<int> stack_postorder(TreeNode *root) {
	vector<int> rst;
	if (!root) return rst;
	stack<pair<TreeNode*, int> > s;
	s.push({root,2});
	while (!s.empty()) {
		if (s.top().second == 0) {
			rst.push_back(s.top().first->val);
			s.pop();
		} else if (s.top().second == 1) {
			s.top().second --;
			if (s.top().first->right) {
				s.push({s.top().first->right, 2});
			}
		} else {
			s.top().second --;
			if (s.top().first->left) {
				s.push({s.top().first->left, 2});
			}
		}
	}
	return rst;
}

vector<int> stack_preorder(TreeNode *root) {
	vector<int> rst;
	if (!root) return rst;
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		rst.push_back(s.top()->val);
		TreeNode* ptr = s.top();
		s.pop();
		if (ptr->right)
			s.push(ptr->right);
		if (ptr->left)
			s.push(ptr->left);
	}
	return rst;
}

vector<int> stack_inorder(TreeNode* root) {
	vector<int> rst;
	if (!root) return rst;
	stack<pair<TreeNode*, int> > s;
	s.push({root,1});
	while (!s.empty()) {
		if (s.top().second == 0) {
			rst.push_back(s.top().first->val);
			TreeNode* ptr = s.top().first;
			s.pop();
			if(ptr->right)
				s.push({ptr->right, 1});
		} else {
			s.top().second --;
			if (s.top().first->left)
				s.push({s.top().first->left,1});
		}
	}
	return rst;
}

vector<int> moris_inorder(TreeNode* root) {
	vector<int> rst;
	if (!root) return rst;
	TreeNode *cur = root;
	TreeNode *prev = NULL;
	while (cur) {
		if (!cur->left) {
			rst.push_back(cur->val);
			cur = cur->right;
		} else {
			prev = cur->left;
			while (prev->right && prev->right != cur) {
				prev = prev->right;
			}
			if (!prev->right) {
				prev->right = cur;
				cur = cur->left;
			} else {
				rst.push_back(cur->val);
				prev->right = NULL;
				cur = cur->right;
			}
		}
	}
	return rst;
}

vector<int> moris_preorder(TreeNode* root) {
	vector<int> rst;
	if (!root) return rst;
	TreeNode *cur = root;
	TreeNode *next = NULL;
	TreeNode *prev = NULL;
	while (cur) {
		next = NULL;
		prev = NULL;
		rst.push_back(cur->val);
		if (cur->right) {
			next = cur->right;
		}
		if (cur->left) {
			prev = cur->left;
			while ((prev->right || prev->left) && prev->left != next) {
				if (prev->right)
					prev = prev->right;
				else
					prev = prev->left;
			}
			if (!prev->left)
				prev->left = next;															
		} 
		if (cur->left)
			cur = cur->left;
		else 
			cur = cur->right;
	}
	return rst;
}

// vector<int> moris_postorder(TreeNode* root) {
// 	vector<int> rst;
// 	if (!root) return rst;
// 	TreeNode dump;
// }

void print_vector(string info, vector<int> v) {
	cout << info << endl;
	for (int const &i: v) {
		cout << i << ' ';
	}
	cout << endl;
}

int main() {
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(10);
	v.push_back(-1);
	v.push_back(-1);
	v.push_back(11);
	v.push_back(-1);
	v.push_back(-1);
	TreeNode *root = createNode(v, 0);
	vector<int> post_stack = stack_postorder(root);
	print_vector("Post Order with Stack", post_stack);
	vector<int> pre_stack = stack_preorder(root);
	print_vector("Pre Order with Stack", pre_stack);
	vector<int> in_stack = stack_inorder(root);
	print_vector("In Order with Stack", in_stack);
	vector<int> in_moris = moris_inorder(root);
	print_vector("Moris In Order", in_moris);
	vector<int> pre_moris = moris_preorder(root);
	print_vector("Moris Pre Order", pre_moris);
	return 0;
}