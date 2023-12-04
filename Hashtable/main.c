#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "Hashtable.h"
#include "visual.h"
#include "file.h"

int main(void)
{
    //start program
    //initialize the hashtable, load the data from the file and print out the main screen
    Hashtable *ht = (Hashtable*) malloc(sizeof(Hashtable));
    init(ht);
    Load(ht);
    print_main();
    //initialize input and exit variables
    bool state = true;
    char input;

    //gets user input until the input is matched with 5 (exit value)
    while(state)
    {
        scanf("%c", &input);
        switch (input)
        {
            case '1':
                new_user(ht); //call function to add a new user
                print_main(); //call the main menu
                break;
            case '2':
                user_data(ht);  //call function to list user's data
                print_main();   //call tha main menu
                break;
            case '3':
                delete_user(ht);  //call function to delete a user
                print_main();     //call the main menu
                break;
            case '4':
                edit_user(ht);    //call function to edit a user's data
                print_main();     //call the main menu
                break;
            case '5':
                state = false;    //while loops breaks
                WritetoFile(ht);    //write existing data to Hashtable.txt
                printf("Exiting\n");    //print out
                sleep(2);   //give time for the user to read
                break;
            default:
                print_main(); //if anything else is given as the input refresh the screen
                break;
        }
    }
    //Free allocated memory for the hashtable and its content
    free_table(ht);
    free(ht);

    return 0;
}