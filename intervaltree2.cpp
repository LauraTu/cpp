#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int start;
	int end;
	int val;
	Node* left;
	Node* right;
	Node(int s, int e): start(s),end(e),val(0),left(NULL),right(NULL) {}
};

Node* buildTree(vector<int> &vec, int s, int e) {
	Node* root = new Node(s,e);
	if (s == e) {
		root->val = vec[s];
	} else {
		int mid = (s+e)/2;
		root->left = buildTree(vec,s,mid);
		root->right = buildTree(vec,mid+1,e);
		root->val = root->left->val+root->right->val;
	}
	return root;
}

void print(Node* root) {
	if (root) {
		cout << root->start << "," << root->end << ":" << root->val << endl;
		print(root->left);
		print(root->right);
	}
}

void update(Node* root, int index, int value) {
	if (root->start == root->end && root->start == index) {
		root->val = value;
	} else {
		if (root->left->end >= index) {
			update(root->left, index, value);
		} else {
			update(root->right, index, value);
		}
		root->val = root->left->val + root->right->val;
	}
}

int query(Node* node, int s, int e){
	if (node->start == s && node->end == e) {
		return node->val;
	} else if (node->left->end >= e) {
		return query(node->left, s, e);
	} else if (node->right->start <= s) {
		return query(node->right, s, e);
	} else {
		int left = query(node->left, s, node->left->end);
		int right = query(node->right, node->right->start, e);
		return left+right;
	}
}

int main() {
	vector<int> v = {1,2,3,4,5,6,7,8,9,10};
	Node* root = buildTree(v,0,v.size()-1);
	// update(root, 0, 0);
	// print(root);
	cout << query(root,1,3) << endl;
	return 0;
}