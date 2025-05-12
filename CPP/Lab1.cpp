#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <random>

using namespace std;

int dayNumber(int day, int month, int year)
{
 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year/4 - year/100 +
             year/400 + t[month-1] + day) % 7;
}
 

string getMonthName(int monthNumber)
{
    string months[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };
 
    return (months[monthNumber]);
}
 

int numberOfDays (int monthNumber, int year)
{
    if (monthNumber == 0) {
      return (31);
    }
    if (monthNumber == 1)
    {
        if (year % 400 == 0 ||
                (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }
    if (monthNumber == 2) {
      return (31);
    }
    if (monthNumber == 3) {
      return (30);
    }
    if (monthNumber == 4) {
      return (31);
    }
    if (monthNumber == 5) {
      return (30);
    }
    if (monthNumber == 6) {
      return (31);
    }
    if (monthNumber == 7) {
      return (31);
    }
    if (monthNumber == 8) {
      return (30);
    }
    if (monthNumber == 9) {
      return (31);
    }
    if (monthNumber == 10) {
      return (30);
    }
    if (monthNumber == 11) {
      return (31);
    }

    return 0;
}
 
void printCalendar(int year, int month)
{
    printf ("         Calendar - %d\n\n", year);
    int days;
    int current = dayNumber (1, 1, year);
    int i = month-1;
      days = numberOfDays (i, year);
      printf("\n  ------------%s-------------\n",
              getMonthName (i).c_str());

      printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

      int k;
      for (k = 0; k < current; k++)
          printf("     ");

      for (int j = 1; j <= days; j++)
      {
          printf("%5d", j);

          if (++k > 6)
          {
              k = 0;
              printf("\n");
          }
      }

      if (k)
          printf("\n");

      current = k;
 
    return;
}

int main() {

  // No 1
  cout << "Student Name\t\t:Mien May\nStudent Gender\t\t:Female\nStudent Age\t\t:23\nStudent Home Address\t:Selangor\nE-wallet Amount\t\t:RM 23.12\n\nStudent details as below:\n-----------------------------------------------------------------\n|Name\t\t|Age\t|Gender\t|Address\t|E-wallet amount|\n-----------------------------------------------------------------\n|Mien May\t|23\t|Female\t|Selangor\t|RM23.12\t|\n-----------------------------------------------------------------" << endl;

  system("pause");

  cout << "-------------------------------------------------\n|Student Details as below:\t\t\t|\n-------------------------------------------------\n|Name\t\t:\t\t\tTest\t|\n|Age\t\t:\t\t\t23\t|\n|Gender\t\t:\t\t\tFemale\t|\n|Address\t:\t\t\tSelangor|\n|E-wallet\t:\t\t\tRM 25.77|\n-------------------------------------------------" << endl;

  cout << "Enter 3 scores:";

  int a, b, c;

  cin >> a >> b >> c;

  float avg = a + b + c / 3;

  if (avg >= 90) {
    cout << "Grade A" << endl;
  } else if (avg >= 70) {
    cout << "Grade B" << endl;
  } else if (avg >= 50) {
    cout << "Grade C" << endl;
  } else {
    cout << "Grade F" << endl;
  }

  system("pause");

  string s;

  cout << "Please enter your elapsed (in HH:MM:SS format) = ";
  cin >> s;

  stringstream deltaTime(s);

  int h, m, sec;
  char colon1, colon2;

  if ((deltaTime >> h >> colon1 >> m >> colon2 >> sec) &&
      (colon1 == ':' && colon2 == ':') &&
      (0 <= h && h <= 60) &&
      (0 <= m && m <= 60) &&
      (0 <= sec && sec <= 60)) {
      cout << "Elapsed Time in Seconds : " << h * 3600 + m * 60 + sec << endl;
  } else {
      cout << "Invalid Time" << endl;
  }


  srand(time(0)); // Seed the random number generator

  int low = 1;
  int high = 10;

  int random = rand() % 33 + 1;

  cout << "Guess Number Between 1 to 33" << endl << "Your answer is: ";
  int ans222;
  cin >> ans222;

  if (ans222 == random) {
    cout << "Congratulations! you Won!"<< endl;
  } else {
    cout << "You Lost" << endl;
  }


  int y1, m1;
  

  while (true) {
    cout << "Enter calender's year: ";
    cin >> y1;

    cout << "Enter calender's month: ";
    cin >> m1;
    printCalendar(y1, m1);
    cout << endl << endl << "Do you want to see another month? 1= Yes, Others = No: ";
    int resp;
    cin >> resp;

    if (resp != 1) {
      break;
    }
  }

  string mnd;
  cout << "Enter Your Month (e.g. August): ";
  cin >> mnd;

  char weather;
  int hot = 0, rainy = 0, cloudy = 0;
  for (int i = 0; i< 28; i++) {
    cout << "Day " << i << ": Enter H for Hot, R for Rainy, C for Cloudy, E to end: ";
    cin >> weather;

    if (weather == 'H') {
      hot++;
    }
    if (weather == 'R') {
      rainy++;
    }
    if (weather == 'C') {
      cloudy++;
    }
    if (weather == 'E') {
      break;
    } 

  }

  cout << "Number of hot days this month: " << hot << endl << "Number of rainy days this month: " << rainy << endl << "Number of cloudy days this month: " << cloudy << endl;
  system("pause");

  int rate, rateresp, amm;
  cout << "Enter the exchange rate from dollars to RMB: ";
  cin >> rate;

  cout << "Enter 0 to convert dollars to RMB and 1 vice versa: ";
  cin >> rateresp;

  if (rateresp == 1) {
    cout << "Enter the dollar amount: ";
    cin >> amm;
    cout << amm * rate << endl;
  } else {
    cout << "Enter the RMB amount: ";
    cin >> amm;
    cout << amm / rate << endl;
  }

  int dimensions;
  cout << "Enter number of rows (for diamonds (triangle dimension)) : ";
  cin >> dimensions;
  int n = dimensions;
  int space = n - 1; 

  for (int i = 0; i < n; i++) 
  { 
      for (int j = 0;j < space; j++) 
          cout << " "; 

      for (int j = 0; j <= i; j++) 
          cout << "* "; 

      cout << endl; 
      space--; 
  } 

  space = 1; 

  for (int i = n - 1; i > 0; i--) 
  { 
      for (int j = 0; j < space; j++) 
          cout << " "; 

      for (int j = 0;j < i;j++) 
          cout << "* ";

      cout << endl;
      space++; 
  } 

    for (int i=0; i <5; i++) {
      for (int j=2+10*i; j <10*(i+1); j+=2) {
        if (j % 2 == 0) {
          cout << j << "\t";
        }
      }
      cout << endl;
    }


    // N
    int awidth, aheight, bwidth, bheight;
    cout << "Rect A:" << endl;
    cout << "Width=";
    cin >> awidth;
    cout << "Height=";
    cin >> aheight;

    cout << "Rect B:" << endl;
    cout << "Width=";
    cin >> bwidth;
    cout << "Height=";
    cin >> bheight;

    if (awidth * aheight > bwidth * bheight) {
      cout << "Area in rectangle A is bigger than Rectangle B" << endl;
    } else {
      cout << "Area in rectangle B is bigger than Rectangle A" << endl;
    }

    int cost, tip;
    cout << "Cost of Meal: ";
    cin >> cost;
    cout << "Tip: ";
    cin >> tip;

    cout << "Cost Before GST + Tip: " << cost << endl;
    cout << "Cost After GST: " << cost * 1.06 << endl;
    cout << "Cost After GST + Tip: " << (cost * 1.06) + tip << endl;
}