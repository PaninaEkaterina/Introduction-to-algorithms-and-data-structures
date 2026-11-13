#include <iostream>
#include <vector>

using namespace std;

// ЗАДАЧА 5. Метод двух указателей (поиск пары)

bool hasPairWithSum(const vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int currentSum = nums[left] + nums[right];
        
        if (currentSum == target) {
            return true;
        } else if (currentSum < target) {
            left++;
        } else {
            right--;
        }
    }
    return false;
}


// ЗАДАЧА 7. Метод двух указателей (удаление дубликатов)

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int slow = 0;

    for (int fast = 1; fast < nums.size(); ++fast) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    
    return slow + 1; 
}


int main() {
    vector<int> nums1 = {1, 2, 3, 4, 6};
    int target = 6;
    cout << "Task 5 (Pair sum " << target << " exists?): " 
         << (hasPairWithSum(nums1, target) ? "Yes" : "No") << endl;

    vector<int> nums2 = {1, 1, 2, 2, 3, 4, 4, 5};
    int newLength = removeDuplicates(nums2);
    cout << "Task 7 (New length): " << newLength << endl;
    cout << "Array after removing duplicates: ";
    for (int i = 0; i < newLength; ++i) {
        cout << nums2[i] << " ";
    }
    cout << endl;

    return 0;
}