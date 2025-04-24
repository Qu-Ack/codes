#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// A Huffman tree node
struct Node {
  char ch;
  int freq;
  std::shared_ptr<Node> left, right;
  Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
  Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r)
      : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

// Comparator for priority queue
struct NodeCmp {
  bool operator()(const std::shared_ptr<Node> &a,
		  const std::shared_ptr<Node> &b) const {
    return a->freq > b->freq;
  }
};

// Build Huffman Tree and return root
std::shared_ptr<Node> buildHuffmanTree(const std::string &data) {
  // Count frequency of each character
  std::unordered_map<char, int> freq;
  for (char c : data)
    freq[c]++;

  // Create min-heap (priority queue)
  std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>,
		      NodeCmp>
      pq;
  for (auto &kv : freq) {
    pq.push(std::make_shared<Node>(kv.first, kv.second));
  }

  // Merge nodes until one remains
  while (pq.size() > 1) {
    auto left = pq.top();
    pq.pop();
    auto right = pq.top();
    pq.pop();
    pq.push(std::make_shared<Node>(left, right));
  }
  return pq.top();
}

// Traverse tree to build codes
void buildCodes(const std::shared_ptr<Node> &node, const std::string &prefix,
		std::unordered_map<char, std::string> &codes) {
  if (!node)
    return;
  if (!node->left && !node->right) {
    codes[node->ch] = prefix;
  }
  buildCodes(node->left, prefix + "0", codes);
  buildCodes(node->right, prefix + "1", codes);
}

// Encode input string into Huffman coded binary string
std::string encode(const std::string &data,
		   std::unordered_map<char, std::string> &codes) {
  std::string encoded;
  for (char c : data) {
    encoded += codes[c];
  }
  return encoded;
}

// Decode Huffman coded string using tree
std::string decode(const std::string &encoded,
		   const std::shared_ptr<Node> &root) {
  std::string decoded;
  auto node = root;
  for (char bit : encoded) {
    node = (bit == '0') ? node->left : node->right;
    if (!node->left && !node->right) {
      decoded += node->ch;
      node = root;
    }
  }
  return decoded;
}

int main() {
  std::string text;
  std::cout << "Enter text to encode: ";
  std::getline(std::cin, text);

  auto root = buildHuffmanTree(text);
  std::unordered_map<char, std::string> codes;
  buildCodes(root, "", codes);

  std::cout << "Huffman Codes:\n";
  for (auto &kv : codes)
    std::cout << kv.first << ": " << kv.second << '\n';

  auto encoded = encode(text, codes);
  std::cout << "\nEncoded string: " << encoded << '\n';

  auto decoded = decode(encoded, root);
  std::cout << "Decoded string: " << decoded << '\n';

  return 0;
}
