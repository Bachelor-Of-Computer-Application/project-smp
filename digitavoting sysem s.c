//#include <stdio.h>
//#include <string.h>
//void clearScreen() {
//    #ifdef _WIN32
//        system("cls");
//    #else
//        system("clear");
//    #endif
//}
//void saveFinalResultsToFile(int v1, int v2, int v3, int v4, int spoilt, const char* winnerText) {
//    FILE *file = fopen("election_result.txt", "w"); 
//    if (file == NULL) {
//        printf("[ERROR] Cannot create file. Try running your IDE as Administrator.\n");
//        return;
//    }
//    fprintf(file, "========================================\n");
//    fprintf(file, "         OFFICIAL ELECTION RESULTS       \n");
//    fprintf(file, "========================================\n");
//    fprintf(file, "Candidate A  : %d votes\n", v1);
//    fprintf(file, "Candidate B  : %d votes\n", v2);
//    fprintf(file, "Candidate C  : %d votes\n", v3);
//    fprintf(file, "Candidate D  : %d votes\n", v4);
//    fprintf(file, "Spoilt Votes : %d\n", spoilt);
//    fprintf(file, "----------------------------------------\n");
//    fprintf(file, "ELECTION STATUS: %s\n", winnerText);
//    fprintf(file, "========================================\n");
//    fflush(file); 
//    fclose(file);
//    printf("\n[SYSTEM] Results successfully recorded inside 'election_result.txt'.\n");
//    printf("Opening Notepad now...\n");
//    #ifdef _WIN32
//        system("election_result.txt");
//    #else
//        system("open -a TextEdit election_result.txt"); 
//    #endif
//}
//int main() {
//    char adminUser[] = "admin";
//    char adminPass[] = "pp";
//    char voterUsers[3][30] = {"user1", "user2", "user3"};
//    char voterPasses[3][30] = {"voter123", "voter456", "voter789"};
//    int voterHasVoted[3] = {0, 0, 0}; 
//    char inputUser[30];
//    char inputPass[30];
//    int mainChoice;
//    int ballotChoice;
//    int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
//    int spoiltVotes = 0;
//    int totalVoters = 3; 
//    int successfullyVoted = 0;
//    int userIndex;
//    int j; 
//    int isInitialized = 0;
//    while (1) {
//        printf("\n=======================================================\n");
//        printf("          WELCOME TO THE DIGITAL VOTING SYSTEM          \n");
//        printf("=======================================================\n");
//        printf("1. Admin \n");
//        printf("2. Voter \n");
//        printf("3. Exit Terminal\n");
//        printf("Enter your choice: ");
//        
//        if (scanf("%d", &mainChoice) != 1) {
//            mainChoice = -1;
//        }
//        while(getchar() != '\n'); 
//        if (mainChoice == 1) {
//            printf("\n===== [ADMIN LOGIN] =====\n");
//            printf("Enter Admin Username: ");
//            scanf("%29s", inputUser);
//            printf("Enter Admin Password: ");
//            scanf("%29s", inputPass);
//            while(getchar() != '\n'); 
//            if (strcmp(inputUser, adminUser) == 0 && strcmp(inputPass, adminPass) == 0) {
//                printf("\n[SUCCESS] Access Granted. Welcome, Admin.\n");
//                int adminChoice;
//                printf("\n--- Admin Controls ---\n");
//                printf("1. Initialize/Reset Election Session\n");
//                printf("2. View Real-Time Live Results\n");
//                printf("Enter choice: ");
//                if (scanf("%d", &adminChoice) != 1) adminChoice = -1;
//                while(getchar() != '\n');
//                if (adminChoice == 1) {
//                    isInitialized = 1;
//                    successfullyVoted = 0;
//                    votes1 = 0; votes2 = 0; votes3 = 0; votes4 = 0;
//                    spoiltVotes = 0;
//                    for(j = 0; j < totalVoters; j++) {
//                        voterHasVoted[j] = 0;
//                    }
//                    FILE *file = fopen("election_result.txt", "w");
//                    if(file != NULL) fclose(file);
//                    clearScreen();
//                    printf("\n[SYSTEM] Voting session initialized.\n");
//                } 
//                else if (adminChoice == 2) {
//                    if (!isInitialized) {
//                        printf("[WARNING] System not initialized yet. No results available.\n");
//                        continue;
//                    }
//                    char winnerMessage[100];
//                    printf("\n===== Final Voting Results =====\n");
//                    printf("Candidate A = %d votes\n", votes1);
//                    printf("Candidate B = %d votes\n", votes2);
//                    printf("Candidate C = %d votes\n", votes3);
//                    printf("Candidate D = %d votes\n", votes4);
//                    printf("Spoilt Votes = %d\n", spoiltVotes);
//                    printf("\n===== Current Winner =====\n");
//                    if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
//                        strcpy(winnerMessage, "Candidate A is the winner.");
//                    }
//                    else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
//                        strcpy(winnerMessage, "Candidate B is the winner.");
//                    }
//                    else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
//                        strcpy(winnerMessage, "Candidate C is the winner.");
//                    }
//                    else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
//                        strcpy(winnerMessage, "Candidate D is the winner.");
//                    }
//                    else {
//                        strcpy(winnerMessage, "The election ended in a tie.");
//                    }
//                    printf("%s\n", winnerMessage);
//                    saveFinalResultsToFile(votes1, votes2, votes3, votes4, spoiltVotes, winnerMessage);
//
//                } else {
//                    printf("[ERROR] Invalid choice.\n");
//                }
//            } else {
//                printf("[ERROR] Invalid Admin credentials access denied.\n");
//            }
//        }
//        else if (mainChoice == 2) {
//            if (!isInitialized) {
//                printf("\n[ACCESS DENIED] The election session has not been initialized by the Admin yet.\n");
//                continue;
//            }
//            
//            if (successfullyVoted >= totalVoters) {
//                printf("\n[NOTICE] All registered voters have already voted. Terminal is locked.\n");
//                continue;
//            }
//            clearScreen(); 
//            userIndex = -1;
//            printf("\n===== [VOTER INTERFACE LOGIN] =====\n");
//            printf("Enter Your Voter ID: ");
//            scanf("%29s", inputUser);
//            printf("Enter Your Password: ");
//            scanf("%29s", inputPass);
//            while(getchar() != '\n'); 
//
//            for (j = 0; j < totalVoters; j++) {
//                if (strcmp(inputUser, voterUsers[j]) == 0 && strcmp(inputPass, voterPasses[j]) == 0) {
//                    userIndex = j;
//                    break;
//                }
//            }
//            if (userIndex == -1) {
//                printf("[ERROR] Invalid voter ID or password.\n");
//                continue;
//            }
//            if (voterHasVoted[userIndex] == 1) {
//                printf("[ACCESS DENIED] Security Alert: User '%s' has already casted a ballot!\n", voterUsers[userIndex]);
//                continue;
//            }
//            clearScreen(); 
//            printf("\n========================================\n");
//            printf(" WELCOME, %s! SECURE BALLOT SCREEN\n", voterUsers[userIndex]);
//            printf("========================================\n");
//            printf("1. Candidate A\n");
//            printf("2. Candidate B\n");
//            printf("3. Candidate C\n");
//            printf("4. Candidate D\n");
//            printf("----------------------------------------\n");
//            printf("Enter your choice (1-4): ");
//            if (scanf("%d", &ballotChoice) != 1) {
//                ballotChoice = -1; 
//            }
//            while(getchar() != '\n'); 
//            switch(ballotChoice) {
//                case 1: votes1++; break;
//                case 2: votes2++; break;
//                case 3: votes3++; break;
//                case 4: votes4++; break;
//                default: spoiltVotes++; break;
//            }
//            voterHasVoted[userIndex] = 1; 
//            successfullyVoted++;
//            clearScreen(); 
//            printf("\n[SUCCESS] Your vote has been securely recorded!\n");
//        }
//        else if (mainChoice == 3) {
//            printf("\nShutting down terminal. Goodbye!\n");
//            break;
//        } 
//        else {
//            printf("\n[ERROR] Invalid portal choice selected.\n");
//        }
//    }
//    return 0;
//}
////#include <stdio.h>
////#include <string.h>
////#include <stdlib.h>
////
////void saveResults(int v1, int v2, int v3, int v4, int sp, const char* win) {
////    FILE *f = fopen("election_result.txt", "w");
////    if (!f) return;
////    
////    fprintf(f, "RESULTS:\nCand A: %d\nCand B: %d\nCand C: %d\nCand D: %d\nSpoilt: %d\n\nWINNER: %s\n", v1, v2, v3, v4, sp, win);
////    fclose(f);
////
////    printf("\nSaved! Opening Notepad...\n");
////    system("notepad election_result.txt");
////}
////
////int main() {
////    char voters[3][30] = {"user1", "user2", "user3"}, passes[3][30] = {"voter123", "voter456", "voter789"};
////    char uIn[30], pIn[30], winMsg[50];
////    int voted[3] = {0, 0, 0}, cv1 = 0, cv2 = 0, cv3 = 0, cv4 = 0, sp = 0;
////    int ch, bCh, total = 0, init = 0, idx, i;
////
////    while (1) {
////        printf("\n1. Admin\n2. Voter\n3. Exit\nChoice: ");
////        if (scanf("%d", &ch) != 1) ch = -1;
////        while(getchar() != '\n');
////
////        if (ch == 1) {
////            printf("User: "); scanf("%29s", uIn);
////            printf("Pass: "); scanf("%29s", pIn);
////            while(getchar() != '\n');
////
////            if (strcmp(uIn, "admin") == 0 && strcmp(pIn, "pp") == 0) {
////                printf("\n1. Init/Reset\n2. Results\nChoice: ");
////                scanf("%d", &ch); while(getchar() != '\n');
////
////                if (ch == 1) {
////                    init = 1; total = 0; cv1 = cv2 = cv3 = cv4 = sp = 0;
////                    for(i=0; i<3; i++) voted[i] = 0;
////                    remove("election_result.txt");
////                    system("cls");
////                    printf("[System Initialized]\n");
////                } 
////                else if (ch == 2 && init) {
////                    if (cv1 > cv2 && cv1 > cv3 && cv1 > cv4) strcpy(winMsg, "Candidate A");
////                    else if (cv2 > cv1 && cv2 > cv3 && cv2 > cv4) strcpy(winMsg, "Candidate B");
////                    else if (cv3 > cv1 && cv3 > cv2 && cv3 > cv4) strcpy(winMsg, "Candidate C");
////                    else if (cv4 > cv1 && cv4 > cv2 && cv4 > cv3) strcpy(winMsg, "Candidate D");
////                    else strcpy(winMsg, "Tie / No clear winner");
////
////                    saveResults(cv1, cv2, cv3, cv4, sp, winMsg);
////                }
////            }
////        } 
////        else if (ch == 2 && init && total < 3) {
////            system("cls");
////            printf("Voter ID: "); scanf("%29s", uIn);
////            printf("Password: "); scanf("%29s", pIn);
////            while(getchar() != '\n');
////
////            idx = -1;
////            for (i = 0; i < 3; i++) {
////                if (strcmp(uIn, voters[i]) == 0 && strcmp(pIn, passes[i]) == 0) { idx = i; break; }
////            }
////
////            if (idx == -1 || voted[idx]) {
////                printf("[Error: Invalid login or already voted]\n");
////                continue;
////            }
////
////            system("cls");
////            printf("1. A\n2. B\n3. C\n4. D\nVote (1-4): ");
////            if (scanf("%d", &bCh) != 1) bCh = -1;
////            while(getchar() != '\n');
////
////            if (bCh == 1) cv1++;
////            else if (bCh == 2) cv2++;
////            else if (bCh == 3) cv3++;
////            else if (bCh == 4) cv4++;
////            else sp++;
////
////            voted[idx] = 1; total++;
////            system("cls");
////            printf("[Vote Registered Successfully]\n");
////        } 
////        else if (ch == 3) break;
////    }
////    return 0;
////}
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

// Function to cleanly rewrite the final results to the file after each vote
void writeResultsToFile(int v1, int v2, int v3, int v4, int spoilt, const char* winnerText) {
    FILE *file = fopen("election_result.txt", "w"); // "w" overwrites with the latest fresh tallies
    if (file == NULL) {
        return; // Silently fail if file system is locked to avoid breaking the voter screen
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

// Simple function for Admin to launch and look at the notepad file
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

            // Recalculate winner state immediately after vote selection
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

            // === INSTANT SAVING TO FILE HAPPENS HERE ===
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
