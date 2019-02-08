#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
	int cnt;
	char ch;
	Node* left;
	Node* right;
	Node(int x): cnt(x),ch(0),left(0),right(0) {}
	Node(int x, char c): cnt(x),ch(c),left(0),right(0) {}
};

class Compare {
public:
	bool operator () (Node* &n1, Node* & n2) {
		return n1->cnt > n2->cnt;
	}
};

int main() {
	priority_queue<Node*, vector<Node*>, Compare> q;
	q.push(new Node(30,'a'));
	q.push(new Node(40,'c'));
	q.push(new Node(41,'e'));
	q.push(new Node(82,'h'));
	q.push(new Node(87,'i'));
	q.push(new Node(52,'n'));
	q.push(new Node(23,'o'));
	q.push(new Node(68,'r'));
	q.push(new Node(44,'s'));
	q.push(new Node(75,'t'));
	q.push(new Node(16,' '));
	while(q.size() > 1 ) {
		Node* n = new Node(0);
		n->cnt += q.top()->cnt;
		cout << q.top()->cnt << " ";
		n->left = q.top();
		q.pop();
		n->cnt += q.top()->cnt;
		n->right = q.top();
		cout << q.top()->cnt << " ";
		cout << n->cnt << endl;;
		q.pop();
		q.push(n);
	}

	return 0;
}