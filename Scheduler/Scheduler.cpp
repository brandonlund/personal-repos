/**/
#include "assignments.h"
#include "schedule.h"
#include <iostream>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>



using namespace std;


bool open_fin( ifstream &fin, string fin_name );
bool open_csv( fstream &fout, string fout_name );
bool open_txt( ofstream &fout, string fout_name );


int main( )
{
    ifstream fin;
    ifstream fincsv;
    ofstream ftxt;
    string csv_name;
    string csv_filename = "Schedules\\";
    string txt_name;
    string txt_filename;
    string sched_name;
    schedule sched;
    char response;
    int month, day, year;
    string assignment;
    string notepad_name;

    _mkdir( "Schedules" );

    cout << "Welcome to your schedule program, Brandon! Which schedule would you like to look at today?" << endl;
    cout << "Please enter your schedule CSV file, or if you would like to create a new schedule, type \"new\"." << endl;
    cout << endl;
    system( "dir /b /o Schedules" );
    
    cout << endl;
    cout << "Response: ";
    cin >> csv_name;

    csv_filename += csv_name;

    if ( csv_name.compare( "new" ) == 0 )
    {
        cout << "Please add an assignment, sir." << endl;
        cout << "Enter assignment: ";
        getline( cin >> ws, assignment );
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter day: ";
        cin >> day;
        cout << "Enter year: ";
        cin >> year;

        sched.insert_duedate( month, day, year );
        sched.insert_assignment( month, day, year, assignment );

        system( "cls" );
        cout << "Here is your schedule, sir:" << endl << endl;
        sched.print_full( cout, "\n" );
        cout << endl;
        cout << "Would you like to make further changes?" << endl;
        cout << "Response (y/n): ";
        cin >> response;
        while ( !( response == 'y' || response == 'n' ) )
        {
            cout << "I'm sorry, sir. I didn't catch that." << endl;
            cout << "Would you like to make changes to your schedule?" << endl;
            cout << "Response (y/n): ";
            cin >> response;
        }

        while ( response == 'y' )
        {
            system( "cls" );
            cout << "Here is your schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;
            cout << "What changes would you like to make to your schedule?" << endl;
            cout << "a - Add an assignment" << endl;
            cout << "d - Add a due date" << endl;
            cout << "q - Remove an assignment" << endl;
            cout << "e - Remove a due date" << endl;
            cout << "n - None" << endl;
            cout << "Your response, sir: ";
            cin >> response;
            while ( !( response == 'a' || response == 'd' || response == 'q' || response == 'e' || response == 'n' ) )
            {
                system( "cls" );
                cout << "Here is your schedule, sir:" << endl << endl;
                sched.print_full( cout, "\n" );
                cout << endl;
                cout << "What changes would you like to make to your schedule?" << endl;
                cout << "a - Add an assignment" << endl;
                cout << "d - Add a due date" << endl;
                cout << "q - Remove an assignment" << endl;
                cout << "e - Remove a due date" << endl;
                cout << "n - None" << endl;
                cout << "Your response, sir: ";
                cin >> response;
            }

            if ( response == 'n' )
            {
                system( "cls" );
                cout << "Here is your schedule, sir:" << endl << endl;
                sched.print_full( cout, "\n" );
                cout << endl;

                cout << "Would you like to save your schedule, sir?" << endl;
                cout << "Response (y/n): ";
                cin >> response;
                if ( response != 'y' )
                {
                    cout << "Are you sure you do not want to save your schedule, sir?" << endl;
                    cout << "Response (y/n): ";
                    cin >> response;

                    if ( response == 'y' )
                    {
                        cout << "You may press any key to exit." << endl;
                        cout << "Response: ";
                        cin >> response;

                        if ( response )
                            return 0;
                    }
                }
                if ( response == 'y' )
                {
                    sched.check_duedates( );
                    cout << "Your prefered text file sir: ";
                    cin >> txt_name;
                    txt_filename = "Schedules\\" + txt_name;
                    while ( !open_txt( ftxt, txt_filename ) )
                    {
                        cout << "I could not open that text file, sir." << endl;
                        cout << "Please enter a text file: ";
                        cin >> txt_name;
                        txt_filename = "Schedules\\" + txt_name;
                    }
                    notepad_name = "notepad \"" + txt_filename + "\"";

                    sched.print_full( ftxt, "\n" );
                    ftxt.close( );

                    cout << "Your prefered csv file sir: ";
                    cin >> txt_name;
                    txt_filename = "Schedules\\" + txt_name;
                    while ( !open_txt( ftxt, txt_filename ) )
                    {
                        cout << "I could not open that csv file, sir." << endl;
                        cout << "Please enter a csv file: ";
                        cin >> txt_name;
                        txt_filename = "Schedules\\" + txt_name;
                    }
                    sched.write_csvfile( ftxt );

                    ftxt.close( );

                    system( notepad_name.c_str( ) );
                    return 0;
                }

                cout << "You may press any key to exit." << endl;
                cout << "Response: ";
                cin >> response;
                
                if ( response )
                    return 0;
            }

            while ( response == 'a' || response == 'd' || response == 'q' || response == 'e' || response == 'n' )
            {
                if ( response == 'n' )
                {
                    sched.check_duedates( );

                    system( "cls" );
                    cout << "Here is your schedule, sir:" << endl << endl;
                    sched.print_full( cout, "\n" );
                    cout << endl;

                    cout << "Would you like to save your schedule, sir?" << endl;
                    cout << "Response (y/n): ";
                    cin >> response;
                    if ( response != 'y' )
                    {
                        cout << "Are you sure you do not want to save your schedule, sir?" << endl;
                        cout << "Response (y/n): ";
                        cin >> response;

                        if ( response == 'y' )
                        {
                            cout << "You may press any key to exit." << endl;
                            cout << "Response: ";
                            cin >> response;

                            if ( response )
                                return 0;
                        }
                    }
                    if ( response == 'y' )
                    {
                        sched.check_duedates( );
                        cout << "Your prefered text file sir: ";
                        cin >> txt_name;
                        txt_filename = "Schedules\\" + txt_name;
                        while ( !open_txt( ftxt, txt_filename ) )
                        {
                            cout << "I could not open that text file, sir." << endl;
                            cout << "Please enter a text file: ";
                            cin >> txt_name;
                            txt_filename = "Schedules\\" + txt_name;
                        }
                        notepad_name = "notepad \"" + txt_filename + "\"";
                        sched.print_full( ftxt, "\n" );
                        ftxt.close( );

                        cout << "Your prefered csv file sir: ";
                        cin >> txt_name;
                        txt_filename = "Schedules\\" + txt_name;
                        while ( !open_txt( ftxt, txt_filename ) )
                        {
                            cout << "I could not open that csv file, sir." << endl;
                            cout << "Please enter a csv file: ";
                            cin >> txt_name;
                            txt_filename = "Schedules\\" + txt_name;
                        }
                        sched.write_csvfile( ftxt );
                        ftxt.close( );
                        system( notepad_name.c_str( ) );
                        return 0;
                    }

                    cout << "You may press any key to exit." << endl;
                    cout << "Response: ";
                    cin >> response;

                    if ( response )
                        return 0;
                }


                if ( response == 'd' )
                {
                    system( "cls" );
                    cout << "Here is your schedule, sir:" << endl << endl;
                    sched.print_full( cout, "\n" );
                    cout << endl;

                    cout << "What date would you like to add, sir?" << endl;
                    cout << "Enter month: ";
                    cin >> month;
                    cout << "Enter day: ";
                    cin >> day;
                    cout << "Enter year: ";
                    cin >> year;
                    sched.insert_duedate( month, day, year );
                }


                if ( response == 'a' )
                {
                    system( "cls" );
                    cout << "Here is your schedule, sir:" << endl << endl;
                    sched.print_full( cout, "\n" );
                    cout << endl;

                    cout << "What assignment would you like to add and on what day, sir?" << endl;
                    cout << "Enter the assignment: ";
                    getline( cin >> ws, assignment );
                    cout << "Enter month: ";
                    cin >> month;
                    cout << "Enter day: ";
                    cin >> day;
                    cout << "Enter year: ";
                    cin >> year;
                    sched.insert_duedate( month, day, year );
                    sched.insert_assignment( month, day, year, assignment );
                }


                if ( response == 'q' )
                {
                    system( "cls" );
                    cout << "Here is your schedule, sir:" << endl << endl;
                    sched.print_full( cout, "\n" );
                    cout << endl;

                    cout << "What assignment would you like to remove and on what day, sir?" << endl;
                    cout << "Enter the assignment: ";
                    getline( cin >> ws, assignment );
                    cout << "Enter month: ";
                    cin >> month;
                    cout << "Enter day: ";
                    cin >> day;
                    cout << "Enter year: ";
                    cin >> year;
                    sched.remove_assignment( month, day, year, assignment );
                }


                if ( response == 'e' )
                {
                    system( "cls" );
                    cout << "Here is your schedule, sir:" << endl << endl;
                    sched.print_full( cout, "\n" );
                    cout << endl;

                    cout << "What date would you like to remove, sir?" << endl;
                    cout << "Enter month: ";
                    cin >> month;
                    cout << "Enter day: ";
                    cin >> day;
                    cout << "Enter year: ";
                    cin >> year;
                    sched.remove_duedate( month, day, year );
                }

                system( "cls" );
                cout << "Here is your schedule, sir:" << endl << endl;
                sched.print_full( cout, "\n" );
                cout << endl;
                cout << "Would you like to continue editing your schedule?" << endl;
                cout << "a - Add an assignment" << endl;
                cout << "d - Add a due date" << endl;
                cout << "q - Remove an assignment" << endl;
                cout << "e - Remove a due date" << endl;
                cout << "n - None" << endl;
                cout << "Your response, sir: ";
                cin >> response;
            }
        }


        cout << "Would you like to save your schedule, sir?" << endl;
        cout << "Response (y/n): ";
        cin >> response;
        if ( response != 'y' )
        {
            cout << "Are you sure you do not want to save your schedule, sir?" << endl;
            cout << "Response (y/n): ";
            cin >> response;

            if ( response == 'y' )
            {
                cout << "You may press any key to exit." << endl;
                cout << "Response: ";
                cin >> response;

                if ( response )
                    return 0;
            }
            
        }
        if ( response == 'y' )
        {
            sched.check_duedates( );
            cout << "Your prefered text file sir: ";
            cin >> txt_name;
            txt_filename = "Schedules\\" + txt_name;
            while ( !open_txt( ftxt, txt_filename ) )
            {
                cout << "I could not open that text file, sir." << endl;
                cout << "Please enter a text file: ";
                cin >> txt_name;
                txt_filename = "Schedules\\" + txt_name;
            }
            notepad_name = "notepad \"" + txt_filename + "\"";
            sched.print_full( ftxt, "\n" );
            ftxt.close( );

            cout << "Your prefered csv file sir: ";
            cin >> txt_name;
            txt_filename = "Schedules\\" + txt_name;
            while ( !open_txt( ftxt, txt_filename ) )
            {
                cout << "I could not open that csv file, sir." << endl;
                cout << "Please enter a csv file: ";
                cin >> txt_name;
                txt_filename = "Schedules\\" + txt_name;
            }
            sched.write_csvfile( ftxt );
            ftxt.close( );
            system( notepad_name.c_str( ) );
            return 0;
        }

        return 0;
    }


    sched_name = csv_name;
    sched_name.erase( sched_name.length( ) - 1 );
    sched_name.erase( sched_name.length( ) - 1 );
    sched_name.erase( sched_name.length( ) - 1 );
    sched_name.erase( sched_name.length( ) - 1 );

    while ( !open_fin( fincsv, csv_filename ) )
    {
        system( "cls" );
        cout << "Unable to open CSV file. Please try again." << endl;
        cout << csv_filename << endl;
        cout << endl;
        system( "dir /b /o Schedules" );
        cout << endl;
        cout << "Please enter your schedule CSV file: ";
        //system( "dir" );
        cin >> csv_name;
        csv_filename = "Schedules\\" + csv_name;
        sched_name = csv_name;
        sched_name.erase( sched_name.length( ) - 1 );
        sched_name.erase( sched_name.length( ) - 1 );
        sched_name.erase( sched_name.length( ) - 1 );
        sched_name.erase( sched_name.length( ) - 1 );
    }


    system( "cls" );

    sched.read_csvfile( sched, fincsv );

    fincsv.close( );

    cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
    sched.print_full( cout, "\n" );
    cout << endl;


    cout << "Would you like to make changes to your schedule?" << endl;
    cout << "Response (y/n): ";
    cin >> response;
    while ( !( response == 'y' || response == 'n' ) )
    {
        cout << "I'm sorry, sir. I didn't catch that." << endl;
        cout << "Would you like to make changes to your schedule?" << endl;
        cout << "Response (y/n): ";
        cin >> response;
    }

    system( "cls" );
    cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
    sched.print_full( cout, "\n" );
    cout << endl;

    if ( response == 'y' )
    {
        cout << "What changes would you like to make to your schedule?" << endl;
        cout << "a - Add an assignment" << endl;
        cout << "d - Add a due date" << endl;
        cout << "q - Remove an assignment" << endl;
        cout << "e - Remove a due date" << endl;
        cout << "n - None" << endl;
        cout << "Your response, sir: ";
        cin >> response;
        while ( !( response == 'a' || response == 'd' || response == 'q' || response == 'e' || response == 'n' ) )
        {
            system( "cls" );
            cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;
            cout << "What changes would you like to make to your schedule?" << endl;
            cout << "a - Add an assignment" << endl;
            cout << "d - Add a due date" << endl;
            cout << "q - Remove an assignment" << endl;
            cout << "e - Remove a due date" << endl;
            cout << "n - None" << endl;
            cout << "Your response, sir: ";
            cin >> response;
        }
    }
    

    if ( response == 'n' )
    {
        system( "cls" );
        cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
        sched.print_full( cout, "\n" );
        cout << endl;

        cout << "Would you like to save your schedule, sir?" << endl;
        cout << "Response (y/n): ";
        cin >> response;
        if ( response != 'y' )
        {
            cout << "Are you sure you do not want to save your schedule, sir?" << endl;
            cout << "Response (y/n): ";
            cin >> response;

            if ( response == 'y' )
            {
                cout << "You may press any key to exit." << endl;
                cout << "Response: ";
                cin >> response;

                if ( response )
                    return 0;
            }
        }
        if ( response == 'y' )
        {
            sched.check_duedates( );
            cout << "Your prefered text file sir: ";
            cin >> txt_name;
            txt_filename = "Schedules\\" + txt_name;
            while ( !open_txt( ftxt, txt_filename ) )
            {
                cout << "I could not open that text file, sir." << endl;
                cout << "Please enter a text file: ";
                cin >> txt_name;
                txt_filename = "Schedules\\" + txt_name;
            }
            notepad_name = "notepad \"" + txt_filename + "\"";
            sched.print_full( ftxt, "\n" );
            ftxt.close( );

            cout << "Your prefered csv file sir: ";
            cin >> txt_name;
            txt_filename = "Schedules\\" + txt_name;
            while ( !open_txt( ftxt, txt_filename ) )
            {
                cout << "I could not open that csv file, sir." << endl;
                cout << "Please enter a csv file: ";
                cin >> txt_name;
                txt_filename = "Schedules\\" + txt_name;
            }
            sched.write_csvfile( ftxt );

            ftxt.close( );
            system( notepad_name.c_str( ) );
            return 0;
        }

        cout << "You may press any key to exit." << endl;
        cout << "Response: ";
        cin >> response;

        return 0;
    }

    while ( response == 'a' || response == 'd' || response == 'q' || response == 'e' || response == 'n' )
    {
        if ( response == 'n' )
        {
            sched.check_duedates( );

            system( "cls" );
            cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;

            cout << "Would you like to save your schedule, sir?" << endl;
            cout << "Response (y/n): ";
            cin >> response;
            if ( response != 'y' )
            {
                cout << "Are you sure you do not want to save your schedule, sir?" << endl;
                cout << "Response (y/n): ";
                cin >> response;
            }
            if ( response == 'y' )
            {
                sched.check_duedates( );
                cout << "Your prefered text file sir: ";
                cin >> txt_name;
                txt_filename = "Schedules\\" + txt_name;
                while ( !open_txt( ftxt, txt_filename ) )
                {
                    cout << "I could not open that text file, sir." << endl;
                    cout << "Please enter a text file: ";
                    cin >> txt_name;
                    txt_filename = "Schedules\\" + txt_name;
                }
                notepad_name = "notepad \"" + txt_filename + "\"";
                sched.print_full( ftxt, "\n" );
                ftxt.close( );

                cout << "Your prefered csv file sir: ";
                cin >> txt_name;
                txt_filename = "Schedules\\" + txt_name;
                while ( !open_txt( ftxt, txt_filename ) )
                {
                    cout << "I could not open that csv file, sir." << endl;
                    cout << "Please enter a csv file: ";
                    cin >> txt_name;
                    txt_filename = "Schedules\\" + txt_name;
                }
                sched.write_csvfile( ftxt );
                ftxt.close( );
                system( notepad_name.c_str( ) );
                return 0;
            }

            cout << "You may press any key to exit." << endl;
            cout << "Response: ";
            cin >> response;

            if ( response )
                return 0;
        }


        if ( response == 'd' )
        {
            system( "cls" );
            cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;

            cout << "What date would you like to add, sir?" << endl;
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter year: ";
            cin >> year;
            sched.insert_duedate( month, day, year );
        }


        if ( response == 'a' )
        {
            system( "cls" );
            cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;

            cout << "What assignment would you like to add and on what day, sir?" << endl;
            cout << "Enter the assignment: ";
            getline( cin >> ws, assignment );
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter year: ";
            cin >> year;
            sched.insert_duedate( month, day, year );
            sched.insert_assignment( month, day, year, assignment );
        }

        
        if ( response == 'q' )
        {
            system( "cls" );
            cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;

            cout << "What assignment would you like to remove and on what day, sir?" << endl;
            cout << "Enter the assignment: ";
            getline( cin >> ws, assignment );
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter year: ";
            cin >> year;
            sched.remove_assignment( month, day, year, assignment );
        }

        
        if ( response == 'e' )
        {
            system( "cls" );
            cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
            sched.print_full( cout, "\n" );
            cout << endl;

            cout << "What date would you like to remove, sir?" << endl;
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter year: ";
            cin >> year;
            sched.remove_duedate( month, day, year );
        }


        system( "cls" );
        cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
        sched.print_full( cout, "\n" );
        cout << endl;
        cout << "Would you like to continue editing your schedule?" << endl;
        cout << "a - Add an assignment" << endl;
        cout << "d - Add a due date" << endl;
        cout << "q - Remove an assignment" << endl;
        cout << "e - Remove a due date" << endl;
        cout << "n - None" << endl;
        cout << "Your response, sir: ";
        cin >> response;
    }
    
    sched.check_duedates( );

    system( "cls" );
    cout << "Here is your " << sched_name << " schedule, sir:" << endl << endl;
    sched.print_full( cout, "\n" );
    cout << endl;

    cout << "Would you like to save your schedule, sir?" << endl;
    cout << "Response (y/n): ";
    cin >> response;
    if ( response != 'y' )
    {
        cout << "Are you sure you do not want to save your schedule, sir?" << endl;
        cout << "Response (y/n): ";
        cin >> response;
        if ( response == 'y' )
        {
            cout << "You may press any key to exit." << endl;
            cout << "Response: ";
            cin >> response;

            if ( response )
                return 0;
        }
    }
    if ( response == 'y' )
    {
        sched.check_duedates( );
        cout << "Your prefered text file sir: ";
        cin >> txt_name;
        txt_filename = "Schedules\\" + txt_name;
        while ( !open_txt( ftxt, txt_filename ) )
        {
            cout << "I could not open that text file, sir." << endl;
            cout << "Please enter a text file: ";
            cin >> txt_name;
            txt_filename = "Schedules\\" + txt_name;
        }
        notepad_name = "notepad \"" + txt_filename + "\"";
        sched.print_full( ftxt, "\n" );
        ftxt.close( );

        cout << "Your prefered csv file sir: ";
        cin >> txt_name;
        txt_filename = "Schedules\\" + txt_name;
        while ( !open_txt( ftxt, txt_filename ) )
        {
            cout << "I could not open that csv file, sir." << endl;
            cout << "Please enter a csv file: ";
            cin >> txt_name;
            txt_filename = "Schedules\\" + txt_name;
        }
        sched.write_csvfile( ftxt );
        ftxt.close( );
        system( notepad_name.c_str( ) );
        return 0;
    }

    cout << "You may press any key to exit." << endl;
    cout << "Response: ";
    cin >> response;

    return 0;
}


bool open_fin( ifstream &fin, string fin_name )
{
    fin.open( fin_name );
    if ( !fin.is_open( ) )
        return false;
    return true;
}


bool open_csv( fstream &fout, string fout_name )
{
    fout.open( fout_name );
    if ( !fout.is_open( ) )
        return false;
    return true;
}


bool open_txt( ofstream &fout, string fout_name )
{
    fout.open( fout_name );
    if ( !fout.is_open( ) )
        return false;
    return true;
}
/**/