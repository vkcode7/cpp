#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int largestVariance(string s) {
    int total = 0;
    unordered_set<char> unique;
    unique.insert('a');
    unique.insert('b');

    for(char c: unique)
        cout << c << endl;

    int i =1;
    for (char a: unique) {
        for (char b: unique) {
            if (a == b) continue;

            int countA = 0, countB = 0; //aababbb
            for (auto ch: s) {
                countA += (ch == a) ? 1 : 0;
                countB += (ch == b) ? 1 : 0;

                total = max(total, countB > 0 ? countA - countB : countA - countB - 1);

                cout << i++ << ". ("<< ch << ") countA=" << countA << ", countB=" << countB << ", total = "<<total<< endl;

                if (countA - countB < 0) {
                    countA = 0;
                    countB = 0;
                }
            }
        }
    }

    return total;
}

int main()
{

    cout << largestVariance("aababbb") << endl; 


    return 0;
}