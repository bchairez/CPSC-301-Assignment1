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
int findNum();                                                     // returns num of people in array
Person fillPerson(Person P[], int N);                    // returns an array of structs of people given a file
void Display(Person P[], int N);                            // displays all people in array: shows full name and balance
void FindRichest(Person P[], int N);                       // shows which person in the array is the richest
void Deposit(string CustName, Person P[], int  N);      // Deposits money into an existing person in the array
void newCopy(string file, Person P[], int N);

int main()
{
  int N = findNum();
  string CustName;

  Person P[N];
  fillPerson(P, N);
  Display(P, N);
  cout << endl;
  FindRichest(P,N);
  cout << endl;
  Deposit(CustName, P, N);
  newCopy("data.txt",P,N);
  cout << "Exiting."<< endl;

  return 0;
}


// Finds the number of people in the file to create the array of structs; returns an int
int findNum()
{
  string fname;
  int N = 0;

  ifstream infile;
  infile.open("data.txt");

  if (!infile)
  {
    cout<<"Could not open file lol"<<endl;
  }

  while(getline(infile, fname))
  {
    N++;
  }

  infile.close();
  return N;
}


// Displays all current people in Person array along with their balance
void Display(Person P[], int N)
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


// Fills array of people with proper information from file; returns a struct
Person fillPerson(Person P[], int N)
{
  string fname;
  string lname;
  string fullname;
  string garbage;

  int i = 0;

  ifstream infile;
  infile.open("data.txt");

  while(!infile.eof())
  {
    infile >> fname >> lname;
    infile >> P[i].balance;
    fullname = fname + " " + lname;
    strcpy(P[i].name, fullname.c_str());
    i++;
    //getline(cin, garbage);

  }

  infile.close();
  return P[N];
}


// Compares everybody's balance and displays person who has the highest
void FindRichest(Person P[], int N)
{
  Person T[N];
  int person = 0;
  float max;

  for (int i = 0; i < N; i++)
  {
    T[i].balance = P[i].balance;
  }
  max = T[0].balance;

  for (int o = 1; o < N; o++)
  {
    if (max < T[o].balance)
    {
      max = T[o].balance;
      person = o;
    }
  }



  cout<< "The customer with max balance is: "
      << P[person].name << endl;
}


// Asks user to enter a name; looks for person in array; updates balance
void Deposit(string CustName, Person P[], int  N)
{
  int deposit;
  string custname;

  cout << "Enter your full name to deposit money: "<<endl;
  getline(cin, custname);

  CustName = custname;

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
            if (i == N-1)
            {
                  cout<< CustName << " has not been found in the array."<<endl;
            }
      }
  }
}

void newCopy(string file, Person P[], int N)
{
  ofstream outfile;
  outfile.open(file);

  cout<<"The data.txt file is now updated."<<endl<<endl;

  for (int i = 0; i < N; i++)
  {
    outfile << P[i].name << " ";
    outfile << fixed<<  setprecision(2)<< P[i].balance << endl;
  }

  outfile.close();
}
