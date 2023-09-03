#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

int userExists(const char *username, FILE *file) {
    struct User user;
    rewind(file); 
    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        if (strcmp(username, user.username) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void addUser(FILE *file) {
    struct User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);

    if (userExists(newUser.username, file)) {
        printf("User already exists\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);

    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    printf("User added successfully!\n");
}

int authenticateUser(FILE *file, char *username, char *password) {
    struct User user;
    rewind(file); 
    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void displayAllPasswords(FILE *file) {
    struct User user;
    rewind(file);
    printf("All passwords:\n");
    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        printf("Username: %s, Password: %s\n", user.username, user.password);
    }
}

int main() {
    FILE *file = fopen("passwords.txt", "a+"); 

    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    int choice;
    char username[50], password[50];

    while (1) {
        printf("1. Log in\n");
        printf("2. Create a new user\n");
        printf("3. Exit\n");
        printf("4. Admin login\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (authenticateUser(file, username, password)) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed!\n");
                }
                break;

            case 2:
                addUser(file);
                break;

            case 3:
                fclose(file);
                return 0;

            case 4:     
                printf("Admin Username: ");
                scanf("%s", username);
                printf("Admin Password: ");
                scanf("%s", password);

                if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
                    displayAllPasswords(file);
                } else {
                    printf("Admin login failed!\n");
                }
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    fclose(file);
    return 0;
}
