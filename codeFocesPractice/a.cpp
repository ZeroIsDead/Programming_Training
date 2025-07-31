#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> memo;

int findPoints(int seg, bool turn = true) {
    if (turn && memo.find(seg) != memo.end()) {
        return memo[seg];
    }

    if (seg <= 2) {
        return 1;
    }

    if (seg % 2 == 0) {
        int points = seg / 2;
        int result = findPoints(points, !turn) + (turn ? points : 0);
        if (turn) {
            memo[seg] = result;
        }
        return result;
    }

    int result = findPoints(seg - 1, !turn) + (turn ? 1 : 0);
    if (turn) {
        memo[seg] = result;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a <= 0)
            cout << 0 << endl;
        else
            cout << findPoints(a) << endl;
    }

    return 0;
}