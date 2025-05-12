#include <string>
#include <sstream>
#include <iostream>

using namespace std;


int main() {
    string fullWord;

    cout << "Enter words: ";
    cin >> fullWord;
    
    stringstream ss(fullWord);
    
    char buffer;
    int count = 0;
    while (ss >> buffer) {
      if (isupper(buffer)) {
        count++;
      }
    }

    cout << count << endl;
    
    int nums[5];
    int sum = 0;

    for (int i=1; i<=5; i++) {
      cout << "Enter your number " << i << " : ";
      cin >> nums[i];
      sum += nums[i];
    }

    cout << sum << endl;

    int arrays[4][5];
    for (int i=0; i < 4; i++) {
      if (i % 2 == 0) {
        for (int j=0; j <= 4; j++) {
          arrays[i][j] = i*5+1+j;
          cout << arrays[i][j] << " ";
        }
      }
      else {
        for (int j=4; j >= 0; j--) {
          arrays[i][j] = i*5+1+j;
          cout << arrays[i][j] << " ";
        }
      }
      cout << endl;
    }


}


