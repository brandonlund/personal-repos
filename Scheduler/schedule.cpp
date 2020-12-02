#include "schedule.h"

schedule::schedule( )
{
    headptr = nullptr;
}

schedule::~schedule( )
{
    schedule::clear( );
}

bool schedule::find( int month, int day, int year )
{
    node *n = headptr;

    if ( n == nullptr )
    {
        return false;
    }

    while ( n->next != nullptr 
            && ( n->month != month
            || n->day != day
            || n->year != year ) )
    {
        n = n->next;
    }

    if ( n->month == month && n->day == day && n->year == year )
    {
        return true;
    }

    return false;
}


int schedule::retrievePosition( int month, int day, int year )
{
    node *n = headptr;
    int pos = 0;

    if ( headptr == nullptr )
    {
        return pos;
    }

    pos++;

    while ( n != nullptr
            && ( n->month != month
            || n->day != day
            || n->year != year ) )
    {
        n = n->next;
        pos++;
    }

    if ( n != nullptr && n->month == month && n->day == day && n->year == year )
    {
        return pos;
    }
    return 0;
}


int schedule::size( )
{
    node *n;
    int size = 0;

    if ( headptr == nullptr )
    {
        return size;
    }
    n = headptr;
    size++;
    while ( n->next != nullptr )
    {
        n = n->next;
        size++;
    }
    return size;
}


bool schedule::empty( )
{
    if ( headptr == nullptr )
    {
        return 1;
    }
    return 0;
}


bool schedule::insert_duedate( int month, int day, int year )
{
    node *n;
    node *list;
    node *prev;

    n = new ( nothrow ) node;
    if ( n == nullptr )
    {
        return false;
    }

    n->month = month;
    n->day = day;
    n->year = year;
    list = headptr;
    prev = headptr;

    if ( headptr == nullptr )
    {
        headptr = n;
        n->next = nullptr;

        return true;
    }

    if ( n->year < list->year
         || n->month < list->month && n->year <= list->year
         || n->month <= list->month && n->day < list->day && n->year <= list->year )
    {
        headptr = n;
        n->next = list;

        return true;
    }


    while ( list != nullptr
            && ( n->year > list->year
            || n->month > list->month && n->year >= list->year
            || n->month >= list->month && n->day > list->day && n->year >= list->year ) )
    {
        prev = list;
        list = list->next;
    }


    if ( list == nullptr )
    {
        prev->next = n;
        list = n;
        n->next = nullptr;

        return true;
    }

    if ( list->year == year && list->month == month && list->day == day )
    {
        return false;
    }


    prev->next = n;
    n->next = list;
    
    return true;
}


void schedule::print( ostream &out, string seperator )
{
    node *n = headptr;

    if ( n != nullptr )
    {
        while ( n->next != nullptr )
        {
            out << n->month << "/" << n->day << "/" << n->year << seperator;
            n = n->next;
        }

        out << n->month << "/" << n->day << "/" << n->year;
    }
}

void schedule::print_full( ostream &out, string seperator )
{
    node *n = headptr;

    if ( n != nullptr )
    {
        while ( n->next != nullptr )
        {
            out << n->month << "/" << n->day << "/" << n->year << ": ";
            n->assignment.print( out, "\t" );
            out << seperator << seperator;
            n = n->next;
        }

        out << n->month << "/" << n->day << "/" << n->year << ": ";
        n->assignment.print( out, "\t" );
        out << seperator;
    }
}


bool schedule::remove_duedate( int month, int day, int year )
{
    node *n;
    node *prev;

    if ( headptr == nullptr ) // no items in the list
    {
        return false;
    }

    n = headptr;

    if ( n->month == month
         && n->day == day
         && n->year == year
         && n->next == nullptr )
    {
        // 1 item in the list. delete it and set headptr to nullptr.
        n->assignment.clear( );
        delete n;
        headptr = nullptr;

        return true;
    }

    // the first item in the list and more to follow
    if ( n->month == month
         && n->day == day
         && n->year == year )
    {
        headptr = n->next;
        n->assignment.clear( );
        delete n;
        return true;
    }

    prev = n;
    n = n->next;

    while ( n != nullptr )
    {
        if ( n->month == month
             && n->day == day
             && n->year == year )
        {
            prev->next = n->next;
            n->assignment.clear( );
            delete n;

            return true;
        }
        prev = n;
        n = n->next;
    }

    return false;
}


void schedule::clear( )
{
    node *n = headptr;

    while ( headptr != nullptr )
    {
        headptr = headptr->next;
        n->assignment.clear( );
        delete n;
        n = headptr;
    }
}


bool schedule::insert_assignment( int month, int day, int year, string assignment )
{
    node *list = headptr;
    int i;

    if ( !find( month, day, year ) )
    {
        std::cout << "assignment not inserted." << std::endl;
        return false;
    }

    for ( i = 1; list->next != nullptr && i < retrievePosition( month, day, year ); i++ )
    {
        list = list->next;
    }

    list->assignment.insert( assignment );

    return true;
}


void schedule::write_csvfile( ofstream &fout )
{
    node *n = headptr;

    while ( n != nullptr )
    {
        fout << n->month << "," << n->day << "," << n->year;
        if ( n->assignment.size( ) > 0 )
        {
            fout << ",";
            n->assignment.print_csv( fout, "," );
        }
        fout << std::endl;
        n = n->next;
    }
}

bool schedule::remove_assignment( int month, int day, int year, string assignment )
{
    node *n = headptr;

    while ( n != nullptr && ( n->month != month
            || n->day != day || n->year != year ) )
    {
        n = n->next;
    }

    if ( n == nullptr )
    {
        return false;
    }

    n->assignment.remove( assignment );

    if ( n->assignment.size( ) == 0 )
        remove_duedate( month, day, year );

    return true;
}


void schedule::read_csvfile( schedule &sched, ifstream &fin )
{
    string month;
    string day;
    string year;
    string delimiter = ",";
    string assignments;
    string assignment;
    
    while ( getline( fin, month, ',' ) )
    {
        getline( fin, day, ',' );
        getline( fin, year, ',' );
        sched.insert_duedate( stoi( month ), stoi( day ), stoi( year ) );
        getline( fin, assignments );
        while ( assignments.find( delimiter ) <= assignments.length( ) )
        {
            assignment = assignments.substr( 0, assignments.find( delimiter ) );
            sched.insert_assignment( stoi( month ), stoi( day ), stoi( year ), assignment );
            assignments.erase( 0, assignments.find( delimiter ) + 1 );
        }
        assignment = assignments;
        sched.insert_assignment( stoi( month ), stoi( day ), stoi( year ), assignment );
    }

}


void schedule::check_duedates( )
{
    node *n = headptr;


    if ( headptr == nullptr )
        return;


    while ( n != nullptr )
    {
        if ( n->assignment.size( ) == 0 )
        {
            remove_duedate( n->month, n->day, n->year );
            return;
        }

        n = n->next;
    }
}