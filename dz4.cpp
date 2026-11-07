#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

void deleteTree(TreeNode* root) {
    if (!root) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}


//1. Восстановление бинарного дерева из массива

TreeNode* buildTree(const vector<optional<int>>& arr, int i = 0) {
    if (i >= static_cast<int>(arr.size()) || !arr[i].has_value()) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(arr[i].value());

    root->left = buildTree(arr, 2 * i + 1);
    root->right = buildTree(arr, 2 * i + 2);

    return root;
}



TreeNode* buildTreeLevelOrder(const vector<optional<int>>& values) {
    if (values.empty() || !values[0].has_value()) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(values[0].value());
    queue<TreeNode*> q;
    q.push(root);

    size_t i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* node = q.front();
        q.pop();

        if (i < values.size()) {
            optional<int> leftValue = values[i++];

            if (leftValue.has_value()) {
                node->left = new TreeNode(leftValue.value());
                q.push(node->left);
            }
        }

        if (i < values.size()) {
            optional<int> rightValue = values[i++];

            if (rightValue.has_value()) {
                node->right = new TreeNode(rightValue.value());
                q.push(node->right);
            }
        }
    }

    return root;
}


//2. Симметричное бинарное дерево

bool isMirror(TreeNode* a, TreeNode* b) {
    if (!a && !b) {
        return true;
    }

    if (!a || !b) {
        return false;
    }

    if (a->data != b->data) {
        return false;
    }

    return isMirror(a->left, b->right) && isMirror(a->right, b->left);
}

bool isSymmetric(TreeNode* root) {
    if (!root) {
        return true;
    }

    return isMirror(root->left, root->right);
}


//3. Поиск минимальной глубины бинарного дерева

int minDepthBFS(TreeNode* root) {
    if (!root) {
        return 0;
    }

    queue<pair<TreeNode*, int>> q;
    q.push({root, 1});

    while (!q.empty()) {
        TreeNode* node = q.front().first;
        int depth = q.front().second;
        q.pop();

        if (!node->left && !node->right) {
            return depth;
        }

        if (node->left) {
            q.push({node->left, depth + 1});
        }

        if (node->right) {
            q.push({node->right, depth + 1});
        }
    }

    return 0;
}

int minDepthDFS(TreeNode* root) {
    if (!root) {
        return 0;
    }

    if (!root->left && !root->right) {
        return 1;
    }

    if (!root->left) {
        return 1 + minDepthDFS(root->right);
    }

    if (!root->right) {
        return 1 + minDepthDFS(root->left);
    }

    return 1 + min(minDepthDFS(root->left), minDepthDFS(root->right));
}


//4. Поиск произведения максимального и минимального элементов

TreeNode* bstMinNode(TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    while (root->left) {
        root = root->left;
    }

    return root;
}

TreeNode* bstMaxNode(TreeNode* root) {
    if (!root) {
        return nullptr;
    }

    while (root->right) {
        root = root->right;
    }

    return root;
}

long long minMaxMultiplicationFromTree(TreeNode* root) {
    TreeNode* minNode = bstMinNode(root);
    TreeNode* maxNode = bstMaxNode(root);

    if (!minNode || !maxNode) {
        return 0;
    }

    return 1LL * minNode->data * maxNode->data;
}


long long minMaxMultiplicationFromArray(const vector<optional<int>>& data) {
    if (data.empty() || !data[0].has_value()) {
        return 0;
    }

    int minIndex = 0;

    while (true) {
        int nextLeftIndex = 2 * minIndex + 1;

        if (nextLeftIndex < static_cast<int>(data.size()) &&
            data[nextLeftIndex].has_value()) {
            minIndex = nextLeftIndex;
        } else {
            break;
        }
    }

    int maxIndex = 0;

    while (true) {
        int nextRightIndex = 2 * maxIndex + 2;

        if (nextRightIndex < static_cast<int>(data.size()) &&
            data[nextRightIndex].has_value()) {
            maxIndex = nextRightIndex;
        } else {
            break;
        }
    }

    return 1LL * data[minIndex].value() * data[maxIndex].value();
}

//5. Сравнение двух бинарных деревьев
 
bool isSameTree(TreeNode* a, TreeNode* b) {
    if (!a && !b) {
        return true;
    }

    if (!a || !b) {
        return false;
    }

    if (a->data != b->data) {
        return false;
    }

    return isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
}



int main() {
    
    vector<optional<int>> arr = {10, 5, 15, 3, 7, 13, 20};

    TreeNode* root = buildTree(arr);

    cout << "minDepthBFS = " << minDepthBFS(root) << '\n';
    cout << "minDepthDFS = " << minDepthDFS(root) << '\n';

    cout << "minMaxMultiplicationFromTree = "
         << minMaxMultiplicationFromTree(root) << '\n';

    cout << "minMaxMultiplicationFromArray = "
         << minMaxMultiplicationFromArray(arr) << '\n';

    vector<optional<int>> symArr = {1, 2, 2, 3, 4, 4, 3};

    TreeNode* symRoot = buildTree(symArr);

    cout << boolalpha;
    cout << "isSymmetric = " << isSymmetric(symRoot) << '\n';


    TreeNode* root2 = buildTree(arr);

    cout << "isSameTree = " << isSameTree(root, root2) << '\n';

    deleteTree(root);
    deleteTree(symRoot);
    deleteTree(root2);

    return 0;
}