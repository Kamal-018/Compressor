#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

unordered_map<char, string> huffmanCodes;

void encode(HuffmanNode* root, string str) {
    if (root == nullptr) return;
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = str;
    }
    encode(root->left, str + "0");
    encode(root->right, str + "1");
}

priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq;

    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }

    encode(pq.top(), "");

    return pq;
}

int main() {
    string text;

    cout << "Enter a word: ";
    getline(cin, text);

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq = buildHuffmanTree(text);

    cout << "Huffman Codes:" << endl;
    for (auto pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
