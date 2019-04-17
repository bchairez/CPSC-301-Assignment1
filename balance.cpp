//Brian Chairez
//CPSC 301 Section 2

// Brian Chairez
// 301 Section 2

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

struct Person{
  char name[20];
  float balance;
};

// Function Prototypes
void mainMenu();
int findNum();
Person * readData(int &N);
void Display(Person *P, int N);                            // displays all people in array: shows full name and balance
void FindRichest(Person *P, int N);                       // shows which person in the array is the richest
void Deposit(string CustName, Person *P, int  N);      // Deposits money into an existing person in the array
void newCopy(string file, Person *P, int N);

void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records"<< endl;
    cout << "2. Deposit funds"<< endl;
    cout << "3. Find Highest Balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

int main()
{
    int N = 0;
    string CustName;
    Person *P = readData(N);
    int choice;
    do
    {
        printmenu();
        cin.clear();
        cin >> choice;
        cin.clear();
        switch(choice)
        {
            case 1:
                Display(P,N);
                break;

            case 2:
                Deposit(CustName, P, N);
                break;

            case 3:
                FindRichest(P, N);
                break;

            case 4:
                newCopy("data.txt", P, N);
                break;

            case 5:
                newCopy("data.txt", P, N);
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 5);
   delete P;
      return 0;
}


// I have no idea
Person * readData(int &N)
{
  ifstream infile;
  string fname;
  string lname;
  string fullname;
  int i = 0;

  N = findNum();

  infile.open("data.txt");
  if (!infile)
  {
    cout << "Could not open file." << endl;
    exit(1);
  }

  Person *P = new Person[N];

  while(infile)
  {
    infile >> fname >> lname;
    fullname = fname + " " + lname;
    strcpy(P[i].name, fullname.c_str());
    infile >> P[i].balance;
    i++;
  }

  infile.close();
  return P;
}

// Finds the number of people in the file to create the array of structs; returns an int
int findNum()
{
  ifstream infile;
  string fname;
  int i = 0;
  infile.open("data.txt");
  if(!infile)
  {
    cout<< "Could not open file."<<endl;
    exit(1);
  }

  while(getline(infile, fname))
  {
    i++;
  }

  infile.close();
  return i;
}


// Displays all current people in Person array along with their balance
void Display(Person *P, int N)
{
  cout << "Name:";
  cout << right << setw(30) << "Balance:" << endl;
  cout << "--------------------------------------" << endl;
  for(int i = 0; i < N; i++)
  {
    cout << left << setw(18) << P[i].name << " ";
    cout << " ";
    cout << right << setw(18) << fixed << setprecision(2) << P[i].balance;
    cout << endl;
  }
}


// Compares everybody's balance and displays person who has the highest
void FindRichest(Person *P, int N)
{
  int person = 0;
  float max = 0.0;

  for (int o = 0; o < N; o++)
  {
    if (max < P[o].balance)
    {
      max = P[o].balance;
      person = o;
    }
  }

  cout<< "The customer with max balance is: "
      << P[person].name << endl;
}


// Asks user to enter a name; looks for person in array; updates balance
void Deposit(string CustName, Person *P, int  N)
{
  int deposit;
  string name;

  cout << "Enter your full name to deposit money: "<<endl;
  getline(cin, CustName);
  cout<< "after";

  for (int i = 0; i < N; i++)
  {
      if (CustName == P[i].name)
      {
            cout<< endl << CustName << ", how much would you like to add in?"<<endl;
            cout<<"$";
            cin >> deposit;
            P[i].balance = P[i].balance + deposit;
            cout<< P[i].name << "'s balance has been updated to $" << P[i].balance<<endl<<endl;
            break;
      }
      else
      {
            if (i == N)
            {
                  cout<< CustName << " has not been found in the array."<<endl;
            }
      }
  }
}

void newCopy(string file, Person *P, int N)
{
  ofstream outfile;
  outfile.open(file);


  for (int i = 0; i < N; i++)
  {
    outfile << P[i].name << " ";
    outfile << fixed<<  setprecision(2)<< P[i].balance << endl;
  }

  cout << "The data.txt file is now updated." << endl;

  outfile.close();
}
