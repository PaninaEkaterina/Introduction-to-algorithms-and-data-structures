#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int v = 0, ListNode* n = nullptr) : val(v), next(n) {}
};

// 1. Проверить является ли список циклическим
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

// 2. Развернуть односвязный список
ListNode* reverseLinkedList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;

    while (cur != nullptr) {
        ListNode* next = cur->next;
        cur->next = prev;

        prev = cur;
        cur = next;
    }

    return prev;
}

// 3. Найти середину списка
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// 4. Удалить все элементы со значением val
ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(0, head);

    ListNode* prev = &dummy;
    ListNode* cur = head;

    while (cur != nullptr) {
        if (cur->val == val) {
            prev->next = cur->next;
            ListNode* temp = cur; 
            cur = cur->next;      
            delete temp;          
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

    return dummy.next;
}

// 5. Удалить n-ый элемент с конца списка
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr || n <= 0) {
        return head;
    }

    ListNode dummy(0, head);
    ListNode* fast = &dummy;

    for (int i = 0; i <= n; ++i) {
        if (fast == nullptr) {
            return head;
        }

        fast = fast->next;
    }

    ListNode* slow = &dummy;

    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    if (slow->next != nullptr) {
        ListNode* temp = slow->next;           
        slow->next = slow->next->next;         
        delete temp;                           
    }

    return dummy.next;
}

// 6. Является ли строка a подпоследовательностью строки b, вариант с очередью
bool isSubsequenceQueue(const string& a, const string& b) {
    queue<char> q;

    for (char c : a) {
        q.push(c);
    }

    for (char c : b) {
        if (!q.empty() && q.front() == c) {
            q.pop();
        }
    }

    return q.empty();
}

// 6. Является ли строка a подпоследовательностью строки b, два указателя
bool isSubsequence(const string& a, const string& b) {
    size_t i = 0;
    size_t j = 0;

    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            ++i;
        }

        ++j;
    }

    return i == a.size();
}

// 7. Палиндром через стек
bool isPalindromeStack(const string& s) {
    stack<char> st;

    for (char c : s) {
        st.push(c);
    }

    for (char c : s) {
        if (c != st.top()) {
            return false;
        }

        st.pop();
    }

    return true;
}

// 7. Палиндром через deque
bool isPalindromeDeque(const string& s) {
    deque<char> dq(s.begin(), s.end());

    while (dq.size() > 1) {
        if (dq.front() != dq.back()) {
            return false;
        }

        dq.pop_front();
        dq.pop_back();
    }

    return true;
}

// 7. Палиндром через два указателя
bool isPalindrome(const string& s) {
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

// 8. Сортировка массива через дополнительный стек
vector<int> sortArrayUsingStack(vector<int> input) {
    vector<int> st;

    while (!input.empty()) {
        int current = input.back();
        input.pop_back();

        while (!st.empty() && st.back() > current) {
            input.push_back(st.back());
            st.pop_back();
        }

        st.push_back(current);
    }

    return st;
}

// 9. Слияние двух отсортированных списков
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy;
    ListNode* tail = &dummy;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }

        tail = tail->next;
    }

    tail->next = (list1 != nullptr) ? list1 : list2;

    return dummy.next;
}

ListNode* createList(const vector<int>& values) {
    ListNode dummy;
    ListNode* tail = &dummy;

    for (int value : values) {
        tail->next = new ListNode(value);
        tail = tail->next;
    }

    return dummy.next;
}

void printList(const ListNode* head) {
    while (head != nullptr) {
        cout << head->val << ' ';
        head = head->next;
    }

    cout << '\n';
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}