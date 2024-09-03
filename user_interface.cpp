/*****************************************************************
//
//  NAME:        Shaelyn Loo
//  
//  HOMEWORK:    project 2
//  
//  CLASS:       ICS 212
//  
//  INSTRUCTOR:  Ravi Narayan
// 
//  DATE:        November 21, 2023
//
//  FILE:        user_interface.c
//  
//  DESCRIPTION:
//   This file holds the user interface for the bank records
//   database. It also holds the getaddress function that is
//   used when adding new records to the database and the
//   getAccountNum function that is used when checking for valid
//   account numbers
//  
********************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

#include "record.h"
#include "llist.h"

void getAccountNum(int*);
void getaddress(char[], int);

using namespace std;

/*****************************************************************
//
//  Function name: main
//  
//  DESCRIPTION:   This function acts as the user interface and menu 
//                 option for the bank record database assignment
//  
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//  
//  Return values:  0 : success
//  
********************************************************************/

int main(int argc, char* argv[])
{
    llist mylist;

    int run = 1;
    int repeat = 0;
    int length;

    string userInput;
    string newString;
    char hold[100];
    char address[50];
    int newAccNo;
    int findAccNo;
    int delAccNo;
    char newName[30];

    string acceptedAdd = "add";
    string acceptedPrintall = "printall";
    string acceptedFind = "find";
    string acceptedDelete = "delete";
    string acceptedQuit = "quit";

    while (run == 1)
    {
        if (repeat == 0)
        {
            cout << "Welcome to the user interface of this banking systems record tracker!\n";
            repeat = 1;
        }
        cout << endl;
        cout << "Please enter one of the following options for what you would like to do:\n";
        cout << endl;
        cout << "add: if you would like to add a record\n";
        cout << "printall: if you would like to print all reccords currently in the database\n";
        cout << "find: if you would like to find a certain record\n";
        cout << "delete: if you would like to delete a record\n";
        cout << "quit: if you would like to quit the program\n";

        cin >> userInput;
        cin.getline(hold, 100, '\n');

        if (acceptedAdd.compare(0, userInput.length(), userInput) == 0)
        {
            cout <<"please enter your account number: \n";
            getAccountNum(&newAccNo);
            cin.getline(hold, 100, '\n');

            cout << "please enter your name: \n";
            cin.getline(newName, 30, '\n');
            newString = newName;
            length = newString.length();

            if (length > 0 && newName[length -1] == '\n')
            {
                newName[length - 1] = '\0';
            }

            cout << "please enter your address: ";
            cout << "(you must hit the ']' key and the enter key when you are done)\n";
            getaddress(address, 50);

            if (mylist.addRecord(newAccNo, newName, address) == -1)
            {
                cout << "record could not be added because of duplicate account numbers\n";
            }
            else
            {
                cout << "record was successfully added\n";
            }
        }
        else if (acceptedPrintall.compare(0, userInput.length(), userInput) == 0)
        {
            mylist.printAllRecords();
        }
        else if (acceptedFind.compare(0, userInput.length(), userInput) == 0)
        {
            cout << "enter the account number you want to find:\n";

            getAccountNum(&findAccNo);

            cin.getline(hold, 100, '\n');

            if (mylist.findRecord(findAccNo) == -1)
            {
                cout << "record could not be found\n";
            }
        }
        else if (acceptedDelete.compare(0, userInput.length(), userInput) == 0)
        {
            cout << "enter the account number you would like to delete:\n";

            getAccountNum(&delAccNo);

            cin.getline(hold, 100, '\n');

            if (mylist.deleteRecord(delAccNo) == -1)
            {
                cout << "record could not be deleted\n";
            }
            else
            {
                cout << "record was successfully deleted\n";
            }
        }
        else if (acceptedQuit.compare(0, userInput.length(), userInput) == 0)
        {
            run = 0;
        }
        else
        {
            cout << "Please enter a valid input\n";
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getAccountNum
//   
//  DESCRIPTION:   This function checks the user inputs account number
//                 to make sure it is a valid account number 
//  
//  Parameters:    AccNo (int *) : the pointer which points to the
//                                 integer being checked
//
//  Return values:  no return values
//    
************************************************************************/

void getAccountNum(int *AccNo)
{
    int valid = 0;
    char hold[100];

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: getAccountNum\n";
    cout << "PARAMETER NAME: AccNo\n";
    cout << "VALUE of AccNo: " << *AccNo << endl;
    cout << "===================================================\n";
    cout << endl;
    #endif

    while (!valid)
    {
        cin >> *AccNo;
        if (cin.fail())
        {
            cout << "not an integer, try again" <<endl;
            cin.clear();
            cin.getline(hold, 100, '\n');
        }
        else if (*AccNo <= 0)
        {
            cout << "please put a positive value" << endl;
        }
        else
        {
            valid = 1;
        }
    }
}

/*****************************************************************
//
//  Function name: getaddress
//  
//  DESCRIPTION:   This function takes user input for their address 
//                 and allows the user to enter a multi line address
// 
//  Parameters:    address (char[]) : starting address of the array 'address'
//                                    that gets passed so the array can update and 
//                                    hold the necessary characters
//                 length (int) : the length of the array passed
//  
//  Return values:  no return values
//  
*******************************************************************/

void getaddress(char address[], int length)
{
    int i;
    char character;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: getaddress\n";
    cout << "PARAMETER NAME: address\n";
    for (i = 0; i < 50; i++)
    {
        cout << address[i];
    }
    cout << endl;
    cout << "PARAMETER NAME: length\n";
    cout << "VALUE OF length: " << length << endl;
    cout << "===================================================\n";
    cout << endl;
    #endif

    cin.getline(address, length, ']');

    for (i = 0; i < length; i++)
    {
        character = address[i];

        if (character == ']')
        {
            address[i] = '\0';
        }
    }
}
