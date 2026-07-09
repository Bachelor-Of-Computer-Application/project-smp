#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void writeResultsToFile(int v1, int v2, int v3, int v4, int spoilt, const char* winnerText) {
    FILE *file = fopen("election_result.txt", "w"); 
    if (file == NULL) {
        return; 
    }
    fprintf(file, "========================================\n");
    fprintf(file, "         OFFICIAL ELECTION RESULTS       \n");
    fprintf(file, "========================================\n");
    fprintf(file, "Candidate A  : %d votes\n", v1);
    fprintf(file, "Candidate B  : %d votes\n", v2);
    fprintf(file, "Candidate C  : %d votes\n", v3);
    fprintf(file, "Candidate D  : %d votes\n", v4);
    fprintf(file, "Spoilt Votes : %d\n", spoilt);
    fprintf(file, "----------------------------------------\n");
    fprintf(file, "ELECTION STATUS: %s\n", winnerText);
    fprintf(file, "========================================\n");
    fflush(file);
    fclose(file);
}
void openNotepad() {
    #ifdef _WIN32
        system("notepad election_result.txt");
    #else
        system("open -a TextEdit election_result.txt"); 
    #endif
}
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
    char winnerMessage[100] = "No votes cast yet.";

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

                if (adminChoice == 1) {
                    isInitialized = 1;
                    successfullyVoted = 0;
                    votes1 = 0; votes2 = 0; votes3 = 0; votes4 = 0;
                    spoiltVotes = 0;
                    strcpy(winnerMessage, "No votes cast yet.");
                    for(j = 0; j < totalVoters; j++) {
                        voterHasVoted[j] = 0;
                    }

                    FILE *file = fopen("election_result.txt", "w");
                    if(file != NULL) fclose(file);

                    clearScreen();
                    printf("\n[SYSTEM] Voting session initialized.\n");
                } 
                else if (adminChoice == 2) {
                    if (!isInitialized) {
                        printf("[WARNING] System not initialized yet. No results available.\n");
                        continue;
                    }
                    
                    printf("\n===== Final Voting Results =====\n");
                    printf("Candidate A = %d votes\n", votes1);
                    printf("Candidate B = %d votes\n", votes2);
                    printf("Candidate C = %d votes\n", votes3);
                    printf("Candidate D = %d votes\n", votes4);
                    printf("Spoilt Votes = %d\n", spoiltVotes);
                    printf("Status: %s\n", winnerMessage);

                    printf("\nOpening updated report in Notepad...\n");
                    openNotepad();

                } else {
                    printf("[ERROR] Invalid choice.\n");
                }
            } else {
                printf("[ERROR] Invalid Admin credentials access denied.\n");
            }
        }
        else if (mainChoice == 2) {
            if (!isInitialized) {
                printf("\n[ACCESS DENIED] The election session has not been initialized by the Admin yet.\n");
                continue;
            }
            
            if (successfullyVoted >= totalVoters) {
                printf("\n[NOTICE] All registered voters have already voted. Terminal is locked.\n");
                continue;
            }

            clearScreen(); 
            
            userIndex = -1;
            printf("\n===== [VOTER INTERFACE LOGIN] =====\n");
            printf("Enter Your Voter ID: ");
            scanf("%29s", inputUser);
            printf("Enter Your Password: ");
            scanf("%29s", inputPass);
            while(getchar() != '\n'); 

            for (j = 0; j < totalVoters; j++) {
                if (strcmp(inputUser, voterUsers[j]) == 0 && strcmp(inputPass, voterPasses[j]) == 0) {
                    userIndex = j;
                    break;
                }
            }
            if (userIndex == -1) {
                printf("[ERROR] Invalid voter ID or password.\n");
                continue;
            }
            if (voterHasVoted[userIndex] == 1) {
                printf("[ACCESS DENIED] Security Alert: User '%s' has already casted a ballot!\n", voterUsers[userIndex]);
                continue;
            }

            clearScreen(); 
            
            printf("\n========================================\n");
            printf(" WELCOME, %s! SECURE BALLOT SCREEN\n", voterUsers[userIndex]);
            printf("========================================\n");
            printf("1. Candidate A\n");
            printf("2. Candidate B\n");
            printf("3. Candidate C\n");
            printf("4. Candidate D\n");
            printf("----------------------------------------\n");
            printf("Enter your choice (1-4): ");
            
            if (scanf("%d", &ballotChoice) != 1) {
                ballotChoice = -1; 
            }
            while(getchar() != '\n'); 

            switch(ballotChoice) {
                case 1: votes1++; break;
                case 2: votes2++; break;
                case 3: votes3++; break;
                case 4: votes4++; break;
                default: spoiltVotes++; break;
            }

            if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
                strcpy(winnerMessage, "Candidate A is the winner.");
            }
            else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
                strcpy(winnerMessage, "Candidate B is the winner.");
            }
            else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
                strcpy(winnerMessage, "Candidate C is the winner.");
            }
            else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
                strcpy(winnerMessage, "Candidate D is the winner.");
            }
            else {
                strcpy(winnerMessage, "The election ended in a tie.");
            }

            writeResultsToFile(votes1, votes2, votes3, votes4, spoiltVotes, winnerMessage);

            voterHasVoted[userIndex] = 1; 
            successfullyVoted++;
            
            clearScreen(); 
            printf("\n[SUCCESS] Your vote has been securely recorded and saved to file!\n");
        }
        else if (mainChoice == 3) {
            printf("\nShutting down terminal. Goodbye!\n");
            break;
        } 
        else {
            printf("\n[ERROR] Invalid portal choice selected.\n");
        }
    }
    return 0;
}