#include <stdio.h>
#include <stdlib.h>
#include "Hashtable.h"


// Function to write the contents of the hashtable to a file
void WritetoFile(Hashtable *ht)
{
    //open file, catch error
    FILE *file = fopen("Hashtable.txt", "w");

    //handle error
    if (file == NULL)
    {
        return;
    }

    // Iterate through the hashtable and write each user's information to the file
    User *p_user;
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        p_user = ht->table[i];

        while(p_user != NULL)
        {
            // Write user information to the file in the format "username password email phone"
            fprintf(file, "%s %s %s %s\n", p_user->username, p_user->password, p_user->email, p_user->phone);
            p_user = p_user->next;
        }
    }
    //close file
    fclose(file);
}


void Load(Hashtable *ht)
{
    //load the hashtable with the data from the Hashtable.txt file
    FILE *file = fopen("Hashtable.txt", "r");

    //check if file opening was successful
    if (file == NULL)
    {
        printf("Error with opening the file\n");
        return;
    }

    User *p_user = (User*) malloc(sizeof(User));
    // Read user data from the file and insert into the hashtable until the end of the file is reached
    while(fscanf(file, "%s %s %s %s", p_user->username, p_user->password, p_user->email, p_user->phone) == 4)
    {
        insert(ht, p_user);
        p_user = (User*) malloc(sizeof(User));
    }
    //free the last allocated memory when the loop returns
    free(p_user);
    // Close the file after reading
    fclose(file);
}