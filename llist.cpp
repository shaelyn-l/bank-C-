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
//  FILE:        database.c
//    
//  DESCRIPTION:
//  This file holds the function definition of the database
//  functions for project 2
//    
***********************************************************************/

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "llist.h"
#include "record.h"

/*****************************************************************
//
//  Function name: llist()
// 
//  DESCRIPTION:   Constructor for llist object. sets the filename
//                 where database will be written to as "records.txt" if
//                 user does not specify what they want the file name to be
//  
//  Parameters:    no parameters
//  
//  Return values:  no return values
//  
*******************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename, "records.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist()
//  
//  DESCRIPTION:   Constructor for llist object. Takes the parameter
//                 as the filename where the linked list will be 
//                 written to
//
//  Parameters:    file (char [ ]) : the file name where the database
//                 will be written to
//  
//  Return values:  no return values
//  
********************************************************************/

llist::llist(char file[20])
{
    start = NULL;
    strcpy(filename, file);
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist()
//  
//  DESCRIPTION:   Destructor for llist object and calls writefile
//                 and clean up methods
// 
//  Parameters:    no parameters
//  
//  Return values:  no return values
//  
*******************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//   
//  DESCRIPTION:   adds a new record to the database in descending 
//                 order and does not allow duplicates
//    
//  Parameters:    accountNo (int) : the account number that is used when
//                                   creating and adding a new record
//                 name (char []) : the name used when creating and
//                                  adding a new record
//                 address (char []) : the addressed used when creating
//                                     and adding a new record
// 
//  
//  Return values:  -1 : record could not be added
//                   0 : record successfully added 
//    
************************************************************************/

int llist::addRecord(int accountNo, char name[ ], char address[ ])
{
    record *temp;
    record *tracker;
    record *back;
    int result;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: addRecord\n";
    cout << "PARAMETER NAME: accountNo\n";
    cout << "VALUE OF accountNo: " << accountNo << endl;
    cout << "PARAMETER NAME: name\n";
    cout << "VALUE OF name: " << name << endl;
    cout << "PARAMETER NAME: address \n";
    cout << "VALUE OF address: " << address << endl;
    cout << "===================================================\n";
    cout << endl;
    #endif

    if (start == NULL)
    {
        start = new record;
        start->accountno = accountNo;
        strcpy((start)->name, name);
        strcpy((start)->address, address);
        (start)->next = NULL;
        result = 0;
    }
    else if (start != NULL)
    {
        if ((start)->accountno == accountNo)
        {
            result = -1;
        }
        if ((start)->accountno < accountNo)
        {
            temp = new record;
            temp->accountno = accountNo;
            strcpy(temp->name, name);
            strcpy(temp->address, address);
            temp->next = start;
            start = temp;
            result = 0;
        }
        else if ((start)->accountno > accountNo)
        {
            tracker = start;
            while (tracker != NULL)
            {
                if (accountNo == tracker->accountno)
                {
                    result = -1;
                    tracker = NULL;
                }
                else if ((accountNo < tracker->accountno) && (tracker->next !=NULL))
                {
                    back = tracker;
                    tracker = tracker->next;
                }
                else if ((accountNo < tracker->accountno) && (tracker->next == NULL))
                {
                    temp = new record;
                    temp->accountno = accountNo;
                    strcpy(temp->name, name);
                    strcpy(temp->address, address);
                    tracker->next = temp;
                    temp->next = NULL;
                    result = 0;
                    tracker = NULL;
                }
                else if (accountNo > tracker->accountno)
                {
                    temp = new record;
                    temp->accountno = accountNo;
                    strcpy(temp->name, name);
                    strcpy(temp->address, address);
                    back->next = temp;
                    temp->next = tracker;
                    result = 0;
                    tracker = NULL;
                }
            }
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: printAllRecords
//      
//  DESCRIPTION:   a function that prints all records in the database
//      
//  Parameters:    no parameters
//    
//  Return values:  no return values
//      
***************************************************************************/

void llist::printAllRecords()
{
    record *temp;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: printAllRecords\n";
    cout << "===================================================\n";
    cout << endl;
    #endif

    if (start == NULL)
    {
        cout << "no records to print\n";
    }
    else if (start != NULL)
    {
        temp = start;
        while (temp != NULL)
        {
            cout << "account number: " << temp->accountno << endl;
            cout << "name: " << temp->name << endl;
            cout << "address: " << temp->address << endl;
            cout << endl;

            temp = temp->next;
        }
    }
}

/*****************************************************************
//
//  Function name: findRecord
//      
//  DESCRIPTION:   a function that finds the record specified
//                 by the account number
//      
//  Parameters:    accountNo (int) : account number used to find the
//                                   corresponding record
//      
//  Return values:  0 : record found
//                 -1 : record could not be found
//      
****************************************************************************/

int llist::findRecord(int accountNo)
{
    record *temp;
    int result;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: findRecord\n";
    cout << "PARAMETER NAME: accountNo\n";
    cout << "VALUE OF accountNo: " << accountNo << endl;
    cout << "===================================================\n";
    cout << endl;
    #endif

    if (start == NULL)
    {
        result = -1;
    }
    else if (start != NULL)
    {
        if (accountNo > start->accountno)
        {
            result = -1;
        }
        if (accountNo == start->accountno)
        {
            cout << "account number: " << start->accountno << endl;
            cout << "name: " << start->name << endl;
            cout << "address: " << start->address << endl;
            cout << endl;
        }
        else if (accountNo < start->accountno)
        {
            temp = start;
            result = -1;

            while (temp != NULL)
            {
                if (accountNo < temp->accountno)
                {
                    temp = temp->next;
                }
                else if (accountNo == temp->accountno)
                {
                    cout << "account number: " << temp->accountno << endl;
                    cout << "name: " << temp->name << endl;
                    cout << "address: " << temp->address << endl;
                    cout << endl;
                    result = 0;
                    temp = NULL;
                }
                else if (accountNo > temp->accountno)
                {
                    temp = NULL;
                }
            }
        }
    }
    return result;
}

/*****************************************************************
//
//  Function name: deleteRecord
//     
//  DESCRIPTION:   a function that deletes a record
//                 specified by the account number
//    
//  Parameters:    accountNo (int) : account number used to find the
//                                   corresponding record
//     
//  Return values:  0 : record successfully deleted
//                 -1 : record could not be deleted
//    
****************************************************************************/

int llist::deleteRecord(int accountNo)
{
    record *temp;
    record *back;
    int result;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: deleteRecord\n";
    cout << "PARAMETER NAME: accountNo\n";
    cout << "VALUE OF accountNo: " << accountNo << endl;
    cout << "===================================================\n";
    cout << endl;
    #endif

    if (start == NULL)
    {
        result = -1;
    }
    else if (start !=NULL)
    {
        if (accountNo > (start)->accountno)
        {
            result = -1;
        }
        if (accountNo == (start)->accountno)
        {
            temp = start;
            start = (start)->next;
            delete temp;
            result = 0;
        }
        else if (accountNo < (start)->accountno)
        {
            temp = start;
            result = -1;

            while (temp!= NULL)
            {
                if (accountNo < temp->accountno)
                {
                    back = temp;
                    temp = temp->next;
                }
                else if (accountNo == temp->accountno)
                {
                    back->next = temp->next;
                    delete temp;
                    result = 0;
                    temp = NULL;
                }
                else if (accountNo > temp->accountno)
                {
                    temp = NULL;
                }
            }
        }
    }
    return result;
}

/*****************************************************************
//
//  Function name: writefile
//        
//  DESCRIPTION:   a function that writes all of the contents of the
//                 linked list to a file
//      
//  Parameters:    no parameters
//       
//  Return values:  0 : file was able to be accessed
//                 -1 : file was not able to be accessed
//     
*********************************************************************************/

int llist::writefile()
{
    int success = 0;
    record *temp;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: writefile\n";
    cout << "===================================================\n";
    cout << endl;
    #endif
    ofstream outfile(filename, std::ofstream::out);

    if (!outfile.is_open())
    {
        success = -1;
    }
    else
    {
        temp = start;
        while (temp != NULL)
        {
            outfile << temp->accountno << endl;
            outfile << temp->name << endl;
            outfile << temp->address << "]" << endl;

            temp = temp->next;
        }
        outfile.close();
    }
    return success;
}

/*****************************************************************
//
//  Function name: readfile
//          
//  DESCRIPTION:   a function that reads from the file the records are
//                 stored into and puts into the linked list
//      
//  Parameters:    no parameters
//        
//  Return values:  0 : file successfully opened
//                 -1 : file could not be opened
//       
*********************************************************************************/

int llist::readfile()
{
    int success = 0;
    int accountNo;
    int index = 0;
    char character;
    int length;

    char name[30];
    char address[50];
    char hold[100];

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: readfile\n";
    cout << "===================================================\n";
    cout << endl;
    #endif

    ifstream infile(filename, std::ifstream::in);

    if (!infile.is_open())
    {
        success = -1;
    }
    else
    {
        while (infile >> accountNo)
        {
            infile.getline(hold, 100);

            infile.getline(name, 30);
            length = strlen(name);
            if (length > 0 && name[length - 1] == '\n')
            {
                name[length - 1] = '\0';
            }

            for (index = 0; index < 50; index++)
            {
                character = infile.get();
                address[index] = character;

                if (character == ']')
                {
                    address[index] = '\0';
                    index = 50;
                }
            }
            index = 0;
            addRecord(accountNo, name, address);
        }
        infile.close();
    }
    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//        
//  DESCRIPTION:   a function that releases all records on the heap
//                 before the user exists the program and sets start
//                 back to NULL
//      
//  Parameters:    no parameters
//      
//  Return values:  No return values
//       
*********************************************************************************/

void llist::cleanup()
{
    record *temp;
    record *back;

    #ifdef DEBUG
    cout << "===================================================\n";
    cout << "FUNCTION NAME: cleanup\n";
    cout << "===================================================\n";
    cout << endl;
    #endif

    if (start != NULL)
    {
        temp = start;
        while (temp != NULL)
        {
            back = temp;
            temp = temp->next;
            delete back;
        }
    }
    start = NULL;
}
