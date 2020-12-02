#pragma once
#include <iostream>
#include <string>
using std::ostream;
using std::string;
using std::nothrow;

class assignments
{
    public:

    assignments( );
    ~assignments( ); 
    bool find( string name );
    int retrievePosition( string name );
    int size( );
    bool empty( );

    bool insert( string name );
    void print( ostream &out, string seperator = ", " );
    void print_csv( ostream &out, string seperator = ", " );

    bool remove( string name );
    void clear( );


    private:

    struct node
    {
        string name;
        node *next;
    };
    node *headptr;
};