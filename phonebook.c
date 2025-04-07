#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15

// Contact structure to hold information
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Contact;

// Function declarations
void addContact(Contact *contacts, int *contactCount);
void displayContacts(Contact *contacts, int contactCount);
int searchContact(Contact *contacts, int contactCount, const char *name);
void saveContacts(Contact *contacts, int contactCount);
void loadContacts(Contact *contacts, int *contactCount);

int main() {
    Contact contacts[MAX_CONTACTS];
    int contactCount = 0;
    int choice;
    
    // Load contacts from file
    loadContacts(contacts, &contactCount);

    while (1) {
        printf("\nPhonebook Application\n");
        printf("1. Add a new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                addContact(contacts, &contactCount);
                break;
            case 2:
                displayContacts(contacts, contactCount);
                break;
            case 3: {
                char searchName[MAX_NAME_LENGTH];
                printf("Enter name to search: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';  // Remove newline character
                int index = searchContact(contacts, contactCount, searchName);
                if (index != -1) {
                    printf("Found: %s - %s\n", contacts[index].name, contacts[index].phone);
                } else {
                    printf("Contact not found.\n");
                }
                break;
            }
            case 4:
                saveContacts(contacts, contactCount);
                printf("Exiting phonebook...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Add a new contact to the phonebook
void addContact(Contact *contacts, int *contactCount) {
    if (*contactCount >= MAX_CONTACTS) {
        printf("Phonebook is full. Cannot add more contacts.\n");
        return;
    }
    printf("Enter name: ");
    fgets(contacts[*contactCount].name, sizeof(contacts[*contactCount].name), stdin);
    contacts[*contactCount].name[strcspn(contacts[*contactCount].name, "\n")] = '\0'; // Remove newline character
    
    printf("Enter phone number: ");
    fgets(contacts[*contactCount].phone, sizeof(contacts[*contactCount].phone), stdin);
    contacts[*contactCount].phone[strcspn(contacts[*contactCount].phone, "\n")] = '\0'; // Remove newline character

    (*contactCount)++;
    printf("Contact added successfully!\n");
}

// Display all contacts in the phonebook
void displayContacts(Contact *contacts, int contactCount) {
    if (contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }
    printf("\nList of Contacts:\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
}

// Search for a contact by name
int searchContact(Contact *contacts, int contactCount, const char *name) {
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if not found
}

// Save all contacts to a file
void saveContacts(Contact *contacts, int contactCount) {
    FILE *file = fopen("contacts.txt", "w");
    if (!file) {
        printf("Error opening file for saving.\n");
        return;
    }
    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s,%s\n", contacts[i].name, contacts[i].phone);
    }
    fclose(file);
    printf("Contacts saved to file.\n");
}

// Load contacts from a file
void loadContacts(Contact *contacts, int *contactCount) {
    FILE *file = fopen("contacts.txt", "r");
    if (!file) {
        printf("No existing contacts found.\n");
        return;
    }
    while (fscanf(file, "%49[^,],%14[^\n]\n", contacts[*contactCount].name, contacts[*contactCount].phone) == 2) {
        (*contactCount)++;
    }
    fclose(file);
}
