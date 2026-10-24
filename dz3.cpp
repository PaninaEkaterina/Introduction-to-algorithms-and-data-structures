#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;


// 1. Найти корень числа (ближайшее целое, округление вниз)
long long floor_sqrt(long long n) {
    if (n < 0) {
        throw invalid_argument("n must be non-negative");
    }

    if (n < 2) {
        return n;
    }

    long long left = 1;
    long long right = n;
    long long answer = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (mid <= n / mid) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}


// 2. Очень лёгкая задача (два ксерокса)
long long min_time_to_make_copies(long long n, long long x, long long y) {
    if (n < 0) {
        throw invalid_argument("n must be non-negative");
    }

    if (n == 0) {
        return 0;
    }

    if (x <= 0 || y <= 0) {
        throw invalid_argument("x and y must be positive");
    }

    auto enough = [&](long long t) -> bool {
        long long first = t / x;

        if (first >= n) {
            return true;
        }

        long long second = t / y;
        return second >= n - first;
    };

    long long fastest = min(x, y);
    long long max_long_long = numeric_limits<long long>::max();
    long long high;
    if (fastest > max_long_long / n) {
        high = max_long_long;
    } else {
        high = fastest * n;
    }

    if (!enough(high)) {
        throw overflow_error("minimal time does not fit in long long");
    }

    long long low = 0;

    while (low < high) {
        long long mid = low + (high - low) / 2;

        if (enough(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return low;
}

// 3. Накормить животных
int max_fed_animals(vector<int> animals, vector<int> portions) {
    sort(animals.begin(), animals.end());
    sort(portions.begin(), portions.end());

    size_t animal_index = 0;
    size_t portion_index = 0;
    int fed = 0;

    while (animal_index < animals.size() && portion_index < portions.size()) {
        if (portions[portion_index] >= animals[animal_index]) {
            ++fed;
            ++animal_index;
            ++portion_index;
        } else {
            ++portion_index;
        }
    }

    return fed;
}


// 4. Найти разницу между двумя строками
char find_added_letter(const string& a, const string& b) {
    unsigned char result = 0;

    for (unsigned char c : a) {
        result ^= c;
    }

    for (unsigned char c : b) {
        result ^= c;
    }

    return static_cast<char>(result);
}


// 5. Сумма двух элементов массива
vector<int> two_sum(const vector<int>& nums, long long target) {
    unordered_map<long long, int> seen;
    seen.reserve(nums.size() * 2 + 1);

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        long long need = target - static_cast<long long>(nums[i]);

        auto it = seen.find(need);
        if (it != seen.end()) {
            return {it->second, i};
        }

        seen[static_cast<long long>(nums[i])] = i;
    }

    return {};
}


// 6. Массив анаграмм
vector<vector<string>> group_anagrams(const vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    groups.reserve(strs.size());

    for (const string& s : strs) {
        bool lowercase_only = true;

        for (unsigned char ch : s) {
            if (ch < 'a' || ch > 'z') {
                lowercase_only = false;
                break;
            }
        }

        string key;

        if (lowercase_only) {
            array<int, 26> counter{};

            for (unsigned char ch : s) {
                ++counter[ch - 'a'];
            }

            key.reserve(4 + 26 * 12);
            key = "cnt:";

            for (int count : counter) {
                key += to_string(count);
                key.push_back('#');
            }
        } else {
            string sorted = s;
            sort(sorted.begin(), sorted.end());

            key = "sorted:";
            key += sorted;
        }

        groups[key].push_back(s);
    }

    vector<vector<string>> answer;
    answer.reserve(groups.size());

    for (auto& [key, words] : groups) {
        answer.push_back(move(words));
    }

    return answer;
}


int main() {
    // 1.
    cout << floor_sqrt(26) << '\n';

    // 2.
    cout << min_time_to_make_copies(10, 3, 7) << '\n'; 

    // 3.
    cout << max_fed_animals({3, 1, 4}, {2, 1, 3}) << '\n'; 

    // 4.
    cout << find_added_letter("abcd", "abcde") << '\n'; 

    // 5.
    auto pair_indices = two_sum({2, 7, 11, 15}, 9);
    if (pair_indices.empty()) {
        cout << "[]\n";
    } else {
        cout << '[' << pair_indices[0] << ", " << pair_indices[1] << "]\n";
    }

    // 6.
    auto groups = group_anagrams({"eat", "tea", "tan", "ate", "nat", "bat"});

    cout << '[';
    for (size_t i = 0; i < groups.size(); ++i) {
        cout << '[';
        for (size_t j = 0; j < groups[i].size(); ++j) {
            cout << '"' << groups[i][j] << '"';
            if (j + 1 < groups[i].size()) {
                cout << ", ";
            }
        }
        cout << ']';
        if (i + 1 < groups.size()) {
            cout << ", ";
        }
    }
    cout << "]\n";

    return 0;
}