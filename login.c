#include <stdio.h>
#include <string.h>
int main() {
    char adminUser[] = "admin";
    char adminPass[] = "pp";
    char voterUsers[3][30] = {"user1", "user2", "user3"};
    char voterPasses[3][30] = {"voter123", "voter456", "voter789"};
    int voterHasVoted[3] = {0, 0, 0}; 
    char inputUser[30];
    char inputPass[30];
    int mainChoice;
    int ballotChoice;
    int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
    int spoiltVotes = 0;
    int totalVoters = 3; 
    int successfullyVoted = 0;
    int userIndex;
    int j; 
    int isInitialized = 0;
    while (1) {
        printf("\n=======================================================\n");
        printf("          WELCOME TO THE DIGITAL VOTING SYSTEM          \n");
        printf("=======================================================\n");
        printf("1. Admin \n");
        printf("2. Voter \n");
        printf("3. Exit Terminal\n");
        printf("Enter your choice: ");
        if (scanf("%d", &mainChoice) != 1) {
            mainChoice = -1;
        }
        while(getchar() != '\n'); 
        if (mainChoice == 1) {
            printf("\n===== [ADMIN LOGIN] =====\n");
            printf("Enter Admin Username: ");
            scanf("%29s", inputUser);
            printf("Enter Admin Password: ");
            scanf("%29s", inputPass);
            while(getchar() != '\n'); 
            if (strcmp(inputUser, adminUser) == 0 && strcmp(inputPass, adminPass) == 0) {
                printf("\n[SUCCESS] Access Granted. Welcome, Admin.\n");
                int adminChoice;
                printf("\n--- Admin Controls ---\n");
                printf("1. Initialize/Reset Election Session\n");
                printf("2. View Real-Time Live Results\n");
                printf("Enter choice: ");
                if (scanf("%d", &adminChoice) != 1) adminChoice = -1;
                while(getchar() != '\n');


