/*
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

    Search for a node to remove.
    If the node is found, delete the node.

Example 1:

Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:

Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.

Example 3:

Input: root = [], key = 0
Output: []

Constraints:

    The number of nodes in the tree is in the range [0, 104].
    -105 <= Node.val <= 105
    Each node has a unique value.
    root is a valid binary search tree.
    -105 <= key <= 105

Follow up: Could you solve it with time complexity O(height of tree)?
*/

#include <queue>
#include <sstream>

#include "gtest/gtest.h"

namespace leet {

namespace bst {

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

std::ostream& operator<<(std::ostream& os, const TreeNode* node) {
    std::queue<const TreeNode*> q;
    q.push(node);
    os << "[";
    while (!q.empty()) {
        node = q.front();
        q.pop();
        if (node) {
            os << node->val;
            if (node->left || node->right) {
                q.push(node->left);
                q.push(node->right);
            }
        } else {
            os << "null";
        }
        if (!q.empty()) {
            os << ",";
        }
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const TreeNode& node) {
    os << &node;
    return os;
}

bool operator==(const TreeNode& lhs, const TreeNode& rhs) {
    std::stringstream s1, s2;
    s1 << lhs;
    s2 << rhs;
    return s1.str() == s2.str();
}

struct TreeFactory {
    std::vector<TreeNode*> n;
    ~TreeFactory() {
        for (auto node : n) {
            delete node;
        }
    }
    TreeNode* fromString(const std::string& input) {
        if (input.empty() || input == "[]") return nullptr;

        std::stringstream ss(input.substr(1, input.size() - 2));
        std::string item;
        std::vector<std::string> nodes;
        while (getline(ss, item, ',')) {
            nodes.push_back(item);
        }

        if (nodes.size() == 1 && nodes[0] != "null") {
            return new TreeNode(stoi(nodes[0]));
        }

        if (nodes[0] == "null") return nullptr;
        TreeNode* root = new TreeNode(stoi(nodes[0]));
        n.push_back(root);

        std::queue<TreeNode*> q;
        q.push(root);
        int index = 1;

        while (!q.empty() && index < nodes.size()) {
            TreeNode* current = q.front();
            q.pop();

            if (nodes[index] != "null") {
                current->left = new TreeNode(stoi(nodes[index]));
                n.push_back(current->left);
                q.push(current->left);
            }
            index++;

            if (index < nodes.size() && nodes[index] != "null") {
                current->right = new TreeNode(stoi(nodes[index]));
                n.push_back(current->right);
                q.push(current->right);
            }
            index++;
        }

        return root;
    }
};

} // namespace bst

using namespace std;
using namespace bst;

class Solution {
    std::pair<TreeNode*, TreeNode*> findByKey(TreeNode* node, int key) {
        if (node->val == key) {
            return {nullptr, node};
        } else if (node->val > key && node->left) {
            auto [prev, res] = findByKey(node->left, key);
            if (!prev) {
                return {node, res};
            } else {
                return {prev, res};
            }
        } else if (node->val < key && node->right) {
            auto [prev, res] = findByKey(node->right, key);
            if (!prev) {
                return {node, res};
            } else {
                return {prev, res};
            }
        } else {
            return {nullptr, nullptr};
        }
    }
    std::pair<TreeNode*, TreeNode*> findLeftmostChild(TreeNode* node) {
        if (!node->left) {
            return {nullptr, node};
        } else {
            auto [prev, res] = findLeftmostChild(node->left);
            if (!prev) {
                return {node, res};
            } else {
                return {prev, res};
            }
        }
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return nullptr;
        }
        auto [parent, node] = findByKey(root, key);
        if (!node) {
            return root;
        } else if (!parent) {
            if (!node->left && !node->right) {
                return nullptr;
            } else if (node->left && !node->right) {
                return node->left;
            } else if (!node->left && node->right) {
                return node->right;
            }
        }
        // step 1-3
        if (!node->left || !node->right) {
            if (!parent) {
                return node;
            } else {
                if (parent->left == node) {
                    if (node->left) {
                        parent->left = node->left;
                    } else {
                        parent->left = node->right;
                    }
                } else {
                    if (node->left) {
                        parent->right = node->left;
                    } else {
                        parent->right = node->right;
                    }
                }
                return root;
            }
        }
        // step 4-7
        auto [G, E] = findLeftmostChild(node->right);
        node->val = E->val;
        if (G) {
            if (E->right) {
                G->left = E->right;
            } else {
                G->left = nullptr;
            }
        } else {
            if (E->right) {
                node->right = E->right;
            } else {
                node->right = nullptr;
            }
        }
        return root;
    }
};

} // namespace leet

class DeleteNodeInBst : public testing::Test {
public:
    leet::Solution s;
};

TEST_F(DeleteNodeInBst, Example1) {
    using namespace leet::bst;
    TreeFactory tf;
    auto root = tf.fromString("[5,3,6,2,4,null,7]");
    auto result = tf.fromString("[5,4,6,2,null,null,7]");
    ASSERT_EQ(*s.deleteNode(root, 3), *result);
}

TEST_F(DeleteNodeInBst, Case81) {
    using namespace leet::bst;
    TreeFactory tf;
    auto root = tf.fromString("[5,3,6,2,4,null,7]");
    auto result = tf.fromString("[6,3,7,2,4]");
    ASSERT_EQ(*s.deleteNode(root, 5), *result);
}

TEST_F(DeleteNodeInBst, Case90) {
    using namespace leet::bst;
    TreeFactory tf;
    auto root = tf.fromString("[0]");
    auto result = tf.fromString("[]");
    ASSERT_EQ(*s.deleteNode(root, 0), *result);
}

TEST_F(DeleteNodeInBst, Case91) {
    using namespace leet::bst;
    TreeFactory tf;
    auto root = tf.fromString("[1,null,2]");
    auto result = tf.fromString("[2]");
    ASSERT_EQ(*s.deleteNode(root, 1), *result);
}
