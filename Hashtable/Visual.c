#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "Hashtable.h"
#include "Visual.h"


void print_main()
{
    //clear console and print out the main menu
    system("cls");
    printf("\t\t------------------User management software------------------\n");
    printf("(1) New User\n");
    printf("(2) Search User\n");
    printf("(3) Delete User\n");
    printf("(4) Edit User\n");
    printf("(5) Exit\n");
}

//function to add a new user
void new_user(Hashtable *ht)
{
    system("cls"); //clear console
    User *p_user = (User*)malloc(sizeof(User)); //allocate memory for the new user

    //handle exeption and free the pointer if not
    if(p_user == NULL)
    {
        free(p_user);
        return;
    }

    //get user input and catch the missing enter for the new data
    printf("Username:\n");
    scanf("%s", p_user->username);
    getchar();

    printf("Password:\n");
    scanf("%s", p_user->password);
    getchar();

    printf("Email:\n");
    scanf("%s", p_user->email);
    getchar();

    printf("Phone:\n");
    scanf("%s", p_user->phone);
    getchar();

    //try to insert it and if unsuccessful return and free the pointer
    if (insert(ht, p_user) == 1)
    {
        free(p_user);
        return;
    }
    //alert the user of success and give time to read
    printf("New user has been added.\n");
    sleep(2);
}

//function to get a user's data
void user_data(Hashtable *ht)
{
    system("cls"); //clear console
    //initialize variables for the search and view and get user's input
    char email[51];
    char finished;
    printf("Email of the searched user:\n");
    scanf("%s", email);
    getchar();

    //search for the user
    User *p_user = search(ht, email);

    //if unsuccessful return
    if(p_user == NULL)
    {
        printf("No user with this email\n");
        sleep(2);
        return;
    }
    //if successful print the user's data line by line
    printf("Username :%s\n", p_user->username);
    printf("Password: %s\n", p_user->password);
    printf("Email: %s\n", p_user->email);
    printf("Phone: %s\n", p_user->phone);

    //Prompt the user to finish viewing
    printf("\n\n----Finished viewing?----\n----Type Y or y----\n");

    do {
        scanf("%c", &finished);
    }while(toupper(finished) != 'Y');

}

//Function to delete a user
void delete_user(Hashtable *ht)
{
    system("cls"); //clear the console

    //Get email input from the user
    char delete_email[51];

    printf("Email of the to be deleted user:\n");
    scanf("%s", delete_email);
    getchar();

    //Search for the user
    User *p_user = search(ht, delete_email);

    //If unsuccessful return
    if(p_user == NULL)
    {
        printf("No such user with this email\n");
        sleep(2);
        return;
    }
    //If successful delete and print it our
    delete(ht, delete_email);
    printf("User has been deleted\n");
    sleep(1);
}

//Function to edit a user's data
void edit_user(Hashtable *ht)
{
    system("cls"); //clear the console

    int changed;
    //Get email input from the user
    char searched_email[51];

    printf("Email of the to be edited user:\n");
    scanf("%s", searched_email);

    //Search for the user
    User *p_user = search(ht, searched_email);

    //If unsuccessful return
    if (p_user == NULL)
    {
        perror("No such user with this email\n");
        return;
    }

    //If successfully searched ask what to be edited
    printf("What do you want to be changed?\nUsername: (1)\nPassword: (2)\nEmail: (3)\nPhone: (4)\n");
    scanf("%i", &changed);
    getchar();
    if(changed == 1)
    {
        //Get the new username
        char new_username[51];
        printf("New Username:\n");
        scanf("%s", new_username);
        //Search if new username is free
        if (username_search(ht, new_username) != 0)
        {
            printf("Already a user with this username\n");
            sleep(2);
            return;
        }
        //if free change
        strcpy(p_user->username, new_username);
        printf("Username updated.\n");
        sleep(2);

        return;
    }
    else if (changed == 2)
    {
        //Get the new password and change it
        char new_password[51];
        printf("New password:\n");
        scanf("%s", new_password);
        strcpy(p_user->password, new_password);
        printf("Password updated.\n");
        sleep(2);

        return;
    }
    else if (changed == 3)
    {
        //Get the new email
        char new_email[51];

        printf("New email:\n");
        scanf("%s", new_email);

        //Allocate new memory for the user and copy from the old
        User *new_user = (User*)malloc(sizeof(User));
        strcpy(new_user->username,p_user->username);
        strcpy(new_user->password,p_user->password);
        strcpy(new_user->email,new_email);
        strcpy(new_user->phone,p_user->phone);

        //If there's a user with the new email already return
        if (search(ht, new_user->email) != NULL)
        {
            printf("Already a user with this email\n");
            sleep(2);
            free(new_user);
            return;
        }
        //Otherwise delete the old and insert the new user
        delete(ht, p_user->email);
        insert(ht, new_user);
        //print our success
        printf("Email updated");
        sleep(2);

        return;
    }
    else if(changed == 4)
    {
        //Get new phone number and change it
        char new_phone[51];
        printf("New phone number:\n");
        scanf("%s", new_phone);
        strcpy(p_user->phone, new_phone);
        printf("Phone number updated");
        sleep(2);

        return;
    }
}