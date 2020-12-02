#include "schedule.h"
#include "catch.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

TEST_CASE( "empty" )
{
    schedule date;

    REQUIRE( date.empty( ) == true );
}

TEST_CASE( "empty, but not" )
{
    schedule date;

    date.insert_duedate( 12, 1, 2020 );

    REQUIRE( date.empty( ) == false );
}

TEST_CASE( "add single date" )
{
    schedule date;
    ostringstream sout;

    date.insert_duedate( 12, 1, 2020 );
    date.print( sout, ", " );
    //cout << sout.str() << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020" ) == 0 );
}

TEST_CASE( "add multiple dates" )
{
    schedule date;
    ostringstream sout;

    date.insert_duedate( 12, 1, 2020 );
    date.insert_duedate( 11, 25, 2020 );
    date.insert_duedate( 12, 15, 2020 );
    date.insert_duedate( 1, 20, 2021 );
    date.insert_duedate( 6, 1, 2019 );
    
    date.print( sout, ", " );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "6/1/2019, 11/25/2020, 12/1/2020, 12/15/2020, 1/20/2021" ) == 0 );
}

TEST_CASE( "insert assignment" )
{
    assignments assign;
    ostringstream sout;

    assign.insert( "CSC Final Project" );
    
    assign.print( sout, ", " );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "CSC Final Project" ) == 0 );
}

TEST_CASE( "insert assignment multiple" )
{
    assignments assign;
    ostringstream sout;

    assign.insert( "CSC Final Project" );
    assign.insert( "Tech Comm Blog" );
    assign.insert( "Diff Eq Final" );
    
    assign.print( sout, ", " );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "CSC Final Project, Tech Comm Blog, Diff Eq Final" ) == 0 );
}

TEST_CASE( "insert due date and assignment" )
{
    schedule date;
    ostringstream sout;
    ofstream fout;

    fout.open( "duedates.txt" );
    if ( !fout.is_open( ) )
    {
        exit( 0 );
    }

    date.insert_duedate( 12, 1, 2020 );
    date.insert_duedate( 12, 2, 2020 );
    date.insert_duedate( 12, 7, 2020 );
    date.insert_assignment( 12, 1, 2020, "CSC Final Project #1" );
    date.insert_assignment( 12, 1, 2020, "CSC Final Project #2" );
    date.insert_assignment( 12, 2, 2020, "Tech Comm Blog" );
    date.insert_assignment( 12, 7, 2020, "Diff Eq Final" );
    
    date.print_full( fout, "\n" );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020: CSC Final Project #1, CSC Final Project #2\n12/2/2020: Tech Comm Blog\n12/7/2020: Diff Eq Final" ) == 0 );
    fout.close( );
}

TEST_CASE( "write to csv" )
{
    schedule date;
    ostringstream sout;
    ofstream fout;

    fout.open( "duedates.csv" );
    if ( !fout.is_open( ) )
    {
        exit( 0 );
    }

    date.insert_duedate( 12, 1, 2020 );
    date.insert_duedate( 12, 2, 2020 );
    date.insert_duedate( 12, 7, 2020 );
    date.insert_assignment( 12, 1, 2020, "CSC Final Project #1" );
    date.insert_assignment( 12, 1, 2020, "CSC Final Project #2" );
    date.insert_assignment( 12, 2, 2020, "Tech Comm Blog" );
    date.insert_assignment( 12, 7, 2020, "Diff Eq Final" );
    
    date.write_csvfile( fout );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020: CSC Final Project #1, CSC Final Project #2\n12/2/2020: Tech Comm Blog\n12/7/2020: Diff Eq Final" ) == 0 );
    fout.close( );
}


TEST_CASE( "read csv" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }
    
    date.read_csvfile( date, fin );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020: CSC Final Project #1, CSC Final Project #2\n12/2/2020: Tech Comm Blog\n12/7/2020: Diff Eq Final" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove assignment" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_assignment( 12, 1, 2020, "CSC Final Project #1" );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020: CSC Final Project #2\n12/2/2020: Tech Comm Blog\n12/7/2020: Diff Eq Final" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove 2 assignments" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_assignment( 12, 1, 2020, "CSC Final Project #1" );
    date.remove_assignment( 12, 1, 2020, "CSC Final Project #2" );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/2/2020: Tech Comm Blog\n12/7/2020: Diff Eq Final" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove due date" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_duedate( 12, 1, 2020 );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/2/2020: Tech Comm Blog\n12/7/2020: Diff Eq Final" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove 2 due dates" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_duedate( 12, 1, 2020 );
    date.remove_duedate( 12, 2, 2020 );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/7/2020: Diff Eq Final" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove all due dates" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_duedate( 12, 1, 2020 );
    date.remove_duedate( 12, 2, 2020 );
    date.remove_duedate( 12, 7, 2020 );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove middle due date" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_duedate( 12, 2, 2020 );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020: CSC Final Project #1, CSC Final Project #2\n12/7/2020: Diff Eq Final" ) == 0 );
    fin.close( );
}

TEST_CASE( "remove end due date" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.remove_duedate( 12, 7, 2020 );
    date.print_full( sout, "\n" );
    //cout << sout.str( ) << endl;
    REQUIRE( sout.str( ).compare( "12/1/2020: CSC Final Project #1, CSC Final Project #2\n12/2/2020: Tech Comm Blog" ) == 0 );
    fin.close( );
}

TEST_CASE( "size 3 dates" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    REQUIRE( date.size( ) == 3 );
    fin.close( );
}

TEST_CASE( "size 1" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    date.insert_duedate( 12, 15, 2020 );

    REQUIRE( date.size( ) == 1 );
}

TEST_CASE( "size empty" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    REQUIRE( date.size( ) == 0 );
}

TEST_CASE( "clear 3 due dates" )
{
    schedule date;
    ostringstream sout;
    ifstream fin;

    fin.open( "duedates.csv" );
    if ( !fin.is_open( ) )
    {
        exit( 0 );
    }

    date.read_csvfile( date, fin );
    date.clear( );
    REQUIRE( date.size( ) == 0 );
    fin.close( );
}

TEST_CASE( "file generator" )
{
    schedule sched;
    ofstream fout;
    ofstream ostringstream;

    sched.insert_duedate( 8, 16, 1945 );
    sched.insert_duedate( 6, 14, 1958 );
    sched.insert_duedate( 1, 28, 1962 );
    sched.insert_duedate( 3, 14, 1975 );
    sched.insert_duedate( 12, 15, 1965 );
    sched.insert_duedate( 5, 12, 2015 );
    sched.insert_duedate( 4, 18, 1925 );
    sched.insert_duedate( 3, 4, 1966 );
    sched.insert_duedate( 5, 18, 1938 );
    sched.insert_duedate( 10, 14, 1925 );

    sched.insert_assignment( 8, 16, 1945, "Make dinner" );
    sched.insert_assignment( 8, 16, 1945, "Go to the movie" );
    sched.insert_assignment( 8, 16, 1945, "Clean the house" );
    sched.insert_assignment( 8, 16, 1945, "Go to work" );
    sched.insert_assignment( 6, 14, 1958, "Figure out the equation" );
    sched.insert_assignment( 6, 14, 1958, "Apply the equation" );
    sched.insert_assignment( 6, 14, 1958, "Find more uses for the equation" );
    sched.insert_assignment( 6, 14, 1958, "Sell the equation" );
    sched.insert_assignment( 6, 14, 1958, "Go down in history" );
    sched.insert_assignment( 3, 14, 1975, "CSC 215 Homework" );
    sched.insert_assignment( 3, 14, 1975, "CSC 215 Program" );
    sched.insert_assignment( 12, 15, 1965, "Make dinner" );
    sched.insert_assignment( 5, 12, 2015, "Pay loan" );
    sched.insert_assignment( 5, 12, 2015, "Make more money" );
    sched.insert_assignment( 5, 12, 2015, "Put money in savings" );
    sched.insert_assignment( 5, 12, 2015, "Pay Frank" );
    sched.insert_assignment( 4, 18, 1925, "Birth" );
    sched.insert_assignment( 3, 4, 1966, "Build Saturn V" );
    sched.insert_assignment( 5, 18, 1938, "Get driver's license" );
    sched.insert_assignment( 5, 18, 1938, "Get a car" );
    sched.insert_assignment( 5, 18, 1938, "Drive around" );
    sched.insert_assignment( 10, 14, 1925, "Half-year anniversary" );
    sched.check_duedates( );

    fout.open( "life_schedule.csv" );
    if ( !fout.is_open( ) )
    {
        exit( 1 );
    }
    sched.write_csvfile( fout );
    fout.close( );

    fout.open( "life_schedule.txt" );
    if ( !fout.is_open( ) )
    {
        exit( 1 );
    }
    sched.print_full( fout, "\n" );
    fout.close( );
}