#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Node {
    public:
        bool word = false;  // Node's "word" label
        Node* children[26]; // children[0] corresponds to 'a', children[1] to 'b', etc.
        Node();             // Node constructor
};

Node::Node(void) {
    for(int i = 0; i < 26; ++i) {
        children[i] = NULL;
    }
}

class MultiwayTrie {
    public:
        Node* root = new Node();  // root node of Multiway Trie
        bool find(string word);   // "find" function of MultiwayTrie class
        void insert(string word); // "insert" function of MultiwayTrie class
        void remove(string word); // "remove" function of MultiwayTrie class
};

bool MultiwayTrie::find(string word) {
    /* YOUR CODE HERE */
    Node* ptr = root;
    int i = 0;
    while(1) {
        char x = tolower(word[i]);
        if (ptr->children[x-'a'] == NULL) return false;
        ptr = ptr->children[x-'a'];
        if (i < word.size()-1) {
            i ++;
        }
        else {
            return ptr->word;
        } 
    }
    return false;
}

/* Insert word into MultiwayTrie (return nothing) */
void MultiwayTrie::insert(string word) {
    /* YOUR CODE HERE */
    Node* ptr = root;
    for (int i = 0; i < word.size(); i ++) {
        char x = tolower(word[i]);
        if (ptr->children[x-'a'] == NULL) {
            ptr->children[x-'a'] = new Node();
        }
        ptr = ptr->children[x-'a'];
        ptr->word = false;
        if (i == word.size()-1) {
            ptr->word = true;
        }
    }
}

/* Remove word from MultiwayTrie (return nothing) */
void MultiwayTrie::remove(string word) {
    /* YOUR CODE HERE */
    if (word.size() == 0) return;
    if (!MultiwayTrie::find(word)) return;
    vector<Node*> v;
    Node* ptr = root;
    for (int i = 0; i < word.size(); i ++) {
        char x = tolower(word[i]);
        ptr = ptr->children[x-'a'];
        v.push_back(ptr);
    }
    while (v.size() != 0) {
        ptr = v.back();

        v.pop_back();
        if (v.size() == word.size()-1) {
            ptr->word = false;
        }
        else if (ptr->word) {
            return;
        }
        bool erase = true;
        for (int j = 0; j < 26; j ++) {
            if (ptr->children[j] != NULL)
                erase = false;
        }
        if (erase) {
            delete ptr;
            ptr = NULL;
        }
    }
}

int main() {
    MultiwayTrie trie;
    trie.insert("word");
    trie.insert("wor");
    trie.insert("APPLE");
    cout << trie.find("word") << endl;
    trie.remove("word");
    cout << trie.find("word") << endl;
    cout << trie.find("APPLE") << endl;
    cout << "END!\n";
}