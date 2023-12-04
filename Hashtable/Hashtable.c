#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "Hashtable.h"

//Function to initialize the hashtable
void init(Hashtable *ht)
{
    //Set all elements to NULL
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }
}

//Hash function
int hash(const char *email)
{
    //Sums up the characters of the email and modulo divide it with the TABLE_SIZE
    int sum = 0;
    for (int i = 0; email[i] != '\0'; i++)
    {
        sum += email[i];
    }

    return sum % TABLE_SIZE;
}

//Function to search for a user by email
User *search(Hashtable *ht, char const *email)
{
    int index = hash(email);

    if(ht->table[index] == NULL)
    {
        return NULL;
    }

    User *current = ht->table[index];

    while(current != NULL)
    {
        if (strcmp(current->email, email) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//Function to search for a user by username
int username_search(Hashtable *ht, char const *username)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        User *current = ht->table[i];
        while(current != NULL)
        {
            if (strcmp(current->username, username) == 0)
            {
                return 1; //User exists with that username
            }
            current = current->next;
        }
    }
    return 0; //No user with that username
}

//Function to insert a new user into the hashtable return 0 if successful
int insert(Hashtable *ht, User *p_user)
{
    int index = hash(p_user->email);

    //Check if there's a user with the given username or email
    if(search(ht, p_user->email) !=NULL)
    {
        printf("Already a user with this email.\n");
        sleep(2);
        return 1;
    }
    else if(username_search(ht, p_user->username) != 0)
    {
        printf("Already a user with this username\n");
        sleep(2);
        return 1;
    }

    //Set user pointer next to NULL for the next insert
    p_user->next = NULL;
    //If hashed section is free put it there
    if(ht->table[index] == NULL)
    {
        ht->table[index] = p_user;
    }
    //Otherwise iterate through the chain and put it as the last element
    else
    {

        User *current = ht->table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = p_user;
    }
    return 0; //If successful
}

//Function to delete a user by email
void delete(Hashtable *ht, const char *email)
{
    //Hash the email and search for the user
    int index = hash(email);
    User *current = search(ht, email);

    //If there's no user return
    if (current == NULL)
    {
        printf("No user with this email\n");
        sleep(2);
        return;
    }
    //Set a previous pointer
    User *prev = ht->table[index];

    //Iterate through chain
    while (current != NULL)
    {
        //Skip the deleted user with its next element and free it
        if (prev->next == current)
        {
            prev->next = current->next;
            free(current);
            return;
        }
        //If first element is the deleted make its next the first element
        else if(prev == current)
        {
            ht->table[index] = current->next;
            free(current);
            return;
        }
        //Set previous to the next
        prev = prev->next;
    }
    //Print out success
    printf("No user with this email\n");
    sleep(2);
}

//Function to free the hashtable
void free_table(Hashtable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        User *current = ht->table[i];
        User *tmp;
        while (current != NULL)
        {
            tmp = current->next;
            free(current);
            current = tmp;
        }
    }
}