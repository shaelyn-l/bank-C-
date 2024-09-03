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
//  FILE:        record.h
//    
//  DESCRIPTION:
//  defines the datatype 'record' and what it holds
// 
************************************************************************/

#ifndef RECORD_H
#define RECORD_H
struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record* next;
};
#endif
