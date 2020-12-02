#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "assignments.h"
using std::ostream;
using std::string;
using std::ifstream;
using std::ofstream;
using std::string;
using std::nothrow;


class schedule
{
    public:

    schedule( );
    ~schedule( );
    bool find( int month, int day, int year );
    int retrievePosition( int month, int day, int year );
    int size( );
    bool empty( );
    bool insert_assignment( int month, int day, int year, string assignment );
    bool insert_duedate( int month, int day, int year );
    void print( ostream &out, string seperator = ", " );
    void print_full( ostream &out, string seperator = ", " );
    void read_csvfile( schedule &sched, ifstream &fin );
    void write_csvfile( ofstream &fout );
    bool remove_assignment( int month, int day, int year, string assignment );
    bool remove_duedate( int month, int day, int year );
    void check_duedates( );
    void clear( );


    private:

    struct node
    {
        int day;
        int month;
        int year;
        assignments assignment;
        node *next;
    };
    node *headptr;
};