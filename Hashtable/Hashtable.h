#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H

#define TABLE_SIZE 10000

typedef struct User
{
    char username[51];
    char password[51];
    char email[51];
    char phone[51];
    struct User *next;
}User;

typedef struct Hashtable
{
    struct User *table[TABLE_SIZE];
}Hashtable;

void init(Hashtable *ht);
int insert(Hashtable *ht, User *p_user);
User *search(Hashtable *ht, const char * email);
int username_search(Hashtable *ht, char const *username);
void delete(Hashtable *ht, const char * email);
void free_table(Hashtable *ht);
#endif //UNTITLED_HASHTABLE_H