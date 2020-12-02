#include "schedule.h"

assignments::assignments( )
{
    headptr = nullptr;
}

assignments::~assignments( )
{
    assignments::clear( );
}

bool assignments::find( string name )
{
    node n = *headptr;

    if ( headptr == nullptr )
    {
        return false;
    }

    while ( &n != nullptr
            && n.name.compare( name ) == 0 )
    {
        n = *n.next;
    }

    if ( n.name.compare( name ) == 0 )
    {
        return true;
    }

    return false;
}


int assignments::retrievePosition( string name )
{
    node n;
    int pos = 0;

    if ( headptr == nullptr )
    {
        return pos;
    }

    n = *headptr;
    pos++;

    while ( &n != nullptr
            && n.name.compare( name ) == 0 )
    {
        n = *n.next;
        pos++;
    }

    if ( n.name.compare( name ) == 0 )
    {
        return pos;
    }
    return 0;
}


int assignments::size( )
{
    node n;
    int size = 0;

    if ( headptr == nullptr )
    {
        return size;
    }
    n = *headptr;
    size++;
    while ( n.next != nullptr )
    {
        n = *n.next;
        size++;
    }
    return size;
}


bool assignments::empty( )
{
    if ( headptr == nullptr )
    {
        return 1;
    }
    return 0;
}


bool assignments::insert( string name )
{
    node *n;
    node *list;

    n = new ( nothrow ) node;
    if ( n == nullptr )
    {
        return false;
    }

    n->name = name;
    list = headptr;

    if ( headptr == nullptr )
    {
        headptr = n;
        n->next = nullptr;

        return true;
    }

    while ( list->next != nullptr )
    {
        list = list->next;
    }

    list->next = n;
    n->next = nullptr;
    return true;
}


void assignments::print( ostream &out, string seperator )
{
    node *n = headptr;

    if ( n != nullptr )
    {
        out << std::endl << seperator;
        while ( n->next != nullptr )
        {
            out << n->name << std::endl << seperator;
            n = n->next;
        }

        out << n->name;
    }
}


void assignments::print_csv( ostream &out, string seperator )
{
    node *n = headptr;

    if ( n != nullptr )
    {
        while ( n->next != nullptr )
        {
            out << n->name << seperator;
            n = n->next;
        }

        out << n->name;
    }
}



bool assignments::remove( string name )
{
    node *n;
    node *prev;

    if ( headptr == nullptr ) // no items in the list
    {
        return false;
    }

    n = headptr;

    if ( n->name.compare( name ) == 0
         && n->next == nullptr )
    {
        // 1 item in the list. delete it and set headptr to nullptr.
        delete n;
        headptr = nullptr;

        return true;
    }

    // the first item in the list and more to follow
    if ( n->name.compare( name ) == 0 )
    {
        headptr = n->next;
        delete n;
        return true;
    }

    prev = n;
    n = n->next;

    while ( n != nullptr )
    {
        if ( n->name.compare( name ) == 0 )
        {
            prev->next = n->next;
            delete n;

            return true;
        }
        prev = n;
        n = n->next;
    }

    return false;
}


void assignments::clear( )
{
    node *n = headptr;

    while ( headptr != nullptr )
    {
        headptr = headptr->next;
        delete n;
        n = headptr;
    }
}
