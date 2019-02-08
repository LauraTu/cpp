#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

string longestPalindrome(string s) {
    string ss = "#";
    string rnt = "";
    for (auto ch: s) {
        ss += ch;
        ss += "#";
    }
    vector<int> r(ss.size(), 0);
    int max_c = 0;
    int cur_c = -1;
    int cur_r = -1;
    int cur_l = -1;
    for (int i = 0; i < ss.size(); i ++) {
        int j = 0;
        if (i <= cur_r) {
            int l = cur_c*2-i;
            int cur_l = cur_c-r[cur_c];
            if (cur_l <= (l-r[l])) {
                j = r[l];
            } else {
                j = cur_l-l;
            }
        }
        while (j < i && j+i < ss.size()-1) {
            if (ss[i+j+1] == ss[i-j-1]) j ++;
            else {
                break;
            }
        }
        r[i] = j;
        if (j > r[max_c]) {
            max_c = i;
        }
        if (i+j > cur_r) {
            cur_c = i;
            cur_r = i+j;
        }
    }
    int start = max_c - r[max_c];
    int end = max_c + r[max_c];
    while (start <= end) {
        if (ss[start] != '#') {
            rnt += ss[start];
        }
        start ++;
    }
    return rnt;
}

string mostCommonWord(string paragraph, vector<string>& banned) {
    unordered_map<string, int> words;
    unordered_set<string> ban;
    for (auto w: banned) {
        ban.insert(w);
    }
    int max_cnt = 0;
    string max_word = "";
    int i = 0;
    while (i < paragraph.size()) {
        if (('a' <= paragraph[i] && paragraph[i] <= 'z') || ('A' <= paragraph[i] && paragraph[i] <= 'Z')) {
            string tmp = "";
            while (i < paragraph.size()) {
                if (('a' <= paragraph[i] && paragraph[i] <= 'z') || ('A' <= paragraph[i] && paragraph[i] <= 'Z')) {
                    tmp += tolower(paragraph[i]);
                    i ++;
                } else {
                    break;
                }
            }
            if (ban.count(tmp) == 0) {
                if (words.count(tmp) == 0) {
                    words[tmp] = 1;
                } else {
                    words[tmp] += 1;
                }
                if (words[tmp] > max_cnt) {
                    max_cnt = words[tmp];
                    max_word = tmp;
                }
            }
        } else {
            i ++;
        }
    }
    return max_word;
}

struct Node {
    int val;
    Node* left;
    Node* right;
};

struct RetVal {
    float sum;
    float cnt;
};

RetVal search(Node* root, Node* &rnt, float &ave) {
    if (!root) {
        return {0,0};
    } else {
        RetVal left = search(root->left, rnt, ave);
        RetVal right = search(root->right, rnt, ave);
        float sum = left.sum+right.sum+root->val;
        float cnt = left.cnt+right.cnt+1;
        float average = sum/cnt;
        if (average > ave) {
            ave = average;
            rnt = root;
        }
        return {sum, cnt};
    }
}

int k_distinct(string s, int k) {
    unordered_map<char, int> m;
    int i = 0;
    int h = 0;
    int cnt = 0;
    while (i < s.size()) {
        if (m.size() == k) {
            if (m.count(s[i]) > 0) {
                m[s[i]] += 1;
                cnt += 1;
            } else {
                while (h < i) {
                    m[s[h]] -= 1;
                    if (m[s[h]] == 0) {
                        m.erase(s[h]);
                        h ++;
                        break;
                    }
                    cnt ++;
                    h ++;
                }
                m[s[i]] = 1;
                cnt ++;
            }
        } else {
            if (m.count(s[i]) > 0) {
                m[s[i]] += 1;
            } else {
                m[s[i]] = 1;
            }
            if (m.size() == k)
                cnt ++;
        }
        i ++;
    }
    if (m.size() == k) {
        while (h < s.size()) {
            m[s[h]] -= 1;
            if (m[s[h]] == 0) {
                break;
            } else {
                cnt ++;
                h ++;
            }
        }
    }
    return cnt;
}

int main() {
    cout << k_distinct("abccbacba", 3) << endl;
}
