#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char username[50];
    char password[50];
} User;

void login();
void registerPatient();
void adminDashboard();
void patientDashboard(char username[]);
int authenticate(char role[], char username[], char password[]);

void main() 
{
    int choice;
    while (1) 
	{
        printf("\nHospital Management System \n");
        printf("1. Login\n");
        printf("2. Register (Patients Only)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) 
		{
            case 1:
                login();
                break;
            case 2:
                registerPatient();
                break;
            case 3:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void registerPatient() 
{
    FILE *fp = fopen("patients.dat", "ab");
    User newUser;

    printf("\nPatient Registration \n");
    printf("Enter Username: ");
    scanf("%s", newUser.username);
    printf("Enter Password: ");
    scanf("%s", newUser.password);

    fwrite(&newUser, sizeof(User), 1, fp);
    fclose(fp);
    printf("Patient registered successfully!\n");
}

void login() 
{
    char role[10], username[50], password[50];

    printf("\n Login \n");
    printf("Enter role (admin/patient): ");
    scanf("%s", role);
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(role, username, password)) 
	{
        if (strcmp(role, "admin") == 0) 
		{
            adminDashboard();
        } else {
            patientDashboard(username);
        }
    } 
	else 
	{
        printf("Invalid credentials. Login failed.\n");
    }
}

int authenticate(char role[], char username[], char password[]) 
{
    if (strcmp(role, "admin") == 0) 
	{
        return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
    } 
	else 
	{
        FILE *fp = fopen("patients.dat", "rb");
        if (!fp) return 0;
        User temp;
        while (fread(&temp, sizeof(User), 1, fp)) 
		{
            if (strcmp(temp.username, username) == 0 && strcmp(temp.password, password) == 0) {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }
}

void adminDashboard() 
{
    int choice;
    while (1) 
	{
        printf("\nAdmin Dashboard \n");
        printf("1. Manage Patient Records\n");
        printf("2. Manage Appointments\n");
        printf("3. Manage Doctors\n");
        printf("4. Room Management\n");
        printf("5. Financial Reports\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                printf("Patient Records Management (Add/Update/Delete/View)\n");
                break;
            case 2:
                printf("Appointments Management (Schedule/Cancel/View)\n");
                break;
            case 3:
                printf("Doctor Schedules (Add/Update/View)\n");
                break;
            case 4:
                printf("Room Allocation and Availability\n");
                break;
            case 5:
                printf("Financial Reports (Billing Info)\n");
                break;
            case 6:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void patientDashboard(char username[]) 
{
    int choice;
    while (1) 
	{
        printf("\nPatient Dashboard (%s) \n", username);
        printf("1. View Personal Details\n");
        printf("2. Book Appointment\n");
        printf("3. Cancel Appointment\n");
        printf("4. View Visit History\n");
        printf("5. View Room Status\n");
        printf("6. View Billing Information\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                printf("Viewing Personal Details...\n");
                break;
            case 2:
                printf("Booking Appointment...\n");
                break;
            case 3:
                printf("Cancelling Appointment...\n");
                break;
            case 4:
                printf("Visit History...\n");
                break;
            case 5:
                printf("Room Allocation Status...\n");
                break;
            case 6:
                printf("Billing Information...\n");
                break;
            case 7:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}
