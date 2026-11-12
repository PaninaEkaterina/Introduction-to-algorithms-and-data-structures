#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <utility>
#include <functional>
#include <stdexcept>

using namespace std;

struct TreeNode {
    int val;
    int balance_factor = 0;   // для задачи 5
    TreeNode* left  = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int v) : val(v) {}
};


// Задача 1. Проверка, является ли дерево полным (complete)
bool isCompleteBinaryTree(TreeNode* root) {
    if (!root) return true;

    queue<TreeNode*> q;
    q.push(root);
    bool seenNull = false;

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        if (!cur) {
            seenNull = true;
            continue;
        }

        if (seenNull) return false;   

        q.push(cur->left);
        q.push(cur->right);
    }
    return true;
}

// Задача 2. Объединение K отсортированных массивов (мин-куча)
vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) {
    using Node = tuple<int, int, int>;  
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    for (int i = 0; i < (int)arrays.size(); ++i) {
        if (!arrays[i].empty()) {
            pq.emplace(arrays[i][0], i, 0);
        }
    }

    vector<int> result;
    while (!pq.empty()) {
        auto pr = pq.top(); pq.pop();
        int value  = get<0>(pr);
        int arrIdx = get<1>(pr);
        int elemIdx= get<2>(pr);

        result.push_back(value);

        if (elemIdx + 1 < (int)arrays[arrIdx].size()) {
            pq.emplace(arrays[arrIdx][elemIdx + 1], arrIdx, elemIdx + 1);
        }
    }
    return result;
}

// Задача 3. K-й наименьший / наибольший в массиве (куча размера K)
int kthSmallestInArray(const vector<int>& nums, int k) {
    if (k <= 0 || k > (int)nums.size())
        throw invalid_argument("k вне диапазона");

    priority_queue<int> maxHeap;            
    for (int x : nums) {
        maxHeap.push(x);
        if ((int)maxHeap.size() > k) maxHeap.pop();
    }
    return maxHeap.top();
}

int kthLargestInArray(const vector<int>& nums, int k) {
    if (k <= 0 || k > (int)nums.size())
        throw invalid_argument("k вне диапазона");

    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : nums) {
        minHeap.push(x);
        if ((int)minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

// Задача 4. K-й наименьший / наибольший в BST
int kthSmallestInBST(TreeNode* root, int k) {
    if (!root || k <= 0) throw invalid_argument("некорректные аргументы");

    stack<TreeNode*> st;
    TreeNode* cur = root;

    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }

        cur = st.top(); st.pop();
        if (--k == 0) return cur->val;
        cur = cur->right;
    }
    throw out_of_range("k больше числа узлов");
}

int kthLargestInBST(TreeNode* root, int k) {
    if (!root || k <= 0) throw invalid_argument("некорректные аргументы");

    stack<TreeNode*> st;
    TreeNode* cur = root;

    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->right; }

        cur = st.top(); st.pop();
        if (--k == 0) return cur->val;
        cur = cur->left;
    }
    throw out_of_range("k больше числа узлов");
}

// Задача 5. Вычисление balance_factor для каждого узла
int fillBalanceFactors(TreeNode* root) {
    if (!root) return 0;                    

    int leftH  = fillBalanceFactors(root->left);
    int rightH = fillBalanceFactors(root->right);

    root->balance_factor = leftH - rightH;    
    return 1 + max(leftH, rightH);            
}

// Задача 6. Зеркальное отражение дерева
void mirrorTree(TreeNode* root) {
    if (!root) return;
    swap(root->left, root->right);
    mirrorTree(root->left);
    mirrorTree(root->right);
}

int main() {
    // ---- Задача 1 ----
    TreeNode* t1 = new TreeNode(1);
    t1->left  = new TreeNode(2);
    t1->right = new TreeNode(3);
    t1->left->left = new TreeNode(4);
    cout << "1. complete? " << boolalpha << isCompleteBinaryTree(t1) << "\n";

    // ---- Задача 2 ----
    vector<vector<int>> arrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    vector<int> merged = mergeKSortedArrays(arrays);
    cout << "2. merged: ";
    for (int x : merged) cout << x << ' ';
    cout << "\n";

    // ---- Задача 3 ----
    vector<int> nums = {7, 10, 4, 3, 20, 15};
    cout << "3. 3rd smallest = " << kthSmallestInArray(nums, 3) << "\n";
    cout << "   2nd largest  = " << kthLargestInArray(nums, 2)  << "\n";

    // ---- Задача 4 ----
    TreeNode* bst = new TreeNode(20);
    bst->left  = new TreeNode(10);
    bst->right = new TreeNode(30);
    bst->left->left  = new TreeNode(5);
    bst->left->right = new TreeNode(15);
    cout << "4. 3rd smallest in BST = " << kthSmallestInBST(bst, 3) << "\n";
    cout << "   2nd largest  in BST = " << kthLargestInBST(bst, 2)  << "\n";

    // ---- Задача 5 ----
    fillBalanceFactors(bst);
    cout << "5. balance_factor(root) = " << bst->balance_factor << "\n";

    // ---- Задача 6 ----
    mirrorTree(bst);
    cout << "6. after mirror, root->left = " << bst->left->val << "\n";

    return 0;
}

