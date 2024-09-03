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
//  DATE:        November 21, 2112
//      
//  FILE:        llist.h
//     
//  DESCRIPTION:
//  defines the class 'llist' and what it holds
//   
****************************************************************************/

#ifndef RECORD_I
#define RECORD_I
#include "record.h"
#endif

#ifndef LLIST_H
#define LLIST_H
class llist
{
    private:
        record *    start;
        char        filename[20];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char[ ], char[ ]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};
#endif
