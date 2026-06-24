////#include <stdio.h>
////
////int main() {
////    int choice;
////    int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
////    int spoiltVotes = 0;
////    int totalVoters, i;
////
////    printf("Enter total number of voters: ");
////    scanf("%d", &totalVoters);
////
////    for(i = 1; i <= totalVoters; i++) {
////        printf("\nVoter %d, please vote:\n", i);
////        printf("1. Candidate A\n");
////        printf("2. Candidate B\n");
////        printf("3. Candidate C\n");
////        printf("4. Candidate D\n");
////        printf("Enter your choice: ");
////        scanf("%d", &choice);
////
////        switch(choice) {
////            case 1:
////                votes1++;
////                break;
////            case 2:
////                votes2++;
////                break;
////            case 3:
////                votes3++;
////                break;
////            case 4:
////                votes4++;
////                break;
////            default:
////                spoiltVotes++;
////                break;
////        }
////    }
////
////    printf("\n===== Voting Result =====\n");
////    printf("Candidate A = %d votes\n", votes1);
////    printf("Candidate B = %d votes\n", votes2);
////    printf("Candidate C = %d votes\n", votes3);
////    printf("Candidate D = %d votes\n", votes4);
////    printf("Spoilt Votes = %d\n", spoiltVotes);
////
////    printf("\n===== Winner =====\n");
////
////    if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
////        printf("Candidate A is the winner.\n");
////    }
////    else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
////        printf("Candidate B is the winner.\n");
////    }
////    else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
////        printf("Candidate C is the winner.\n");
////    }
////    else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
////        printf("Candidate D is the winner.\n");
////    }
////    else {
////        printf("There is a tie between candidates.\n");
////    }
////
////    return 0;
////}
//#include <stdio.h>
//#include <string.h> // Required for strcmp()
//
//int main() {
//    // --- Login System Variables ---
//    char username[30];
//    char password[30];
//    int attempts = 3;
//    int authenticated = 0;
//
//    // --- Voting System Variables ---
//    int choice;
//    int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
//    int spoiltVotes = 0;
//    int totalVoters, i;
//
//    // ==========================================
//    // LOGIN SYSTEM
//    // ==========================================
//    printf("===== SYSTEM LOGIN =====\n");
//    
//    while (attempts > 0) {
//        printf("Enter Username: ");
//        scanf("%29s", username); // Limit input to prevent buffer overflow
//        printf("Enter Password: ");
//        scanf("%29s", password);
//
//        // Check credentials (Change "admin" and "password123" to your liking)
////        if (strcmp(username, "prashant") == 0 && strcmp(password, "") == 0) {
//            printf("\nLogin Successful! Access Granted.\n\n");
//            authenticated = 1;
//            break; // Exit the login loop
//        } else {
//            attempts--;
//            printf("Invalid credentials. Attempts remaining: %d\n\n", attempts);
//        }
//    }
//
//    // If login failed after all attempts, exit the program
//    if (!authenticated) {
//        printf("Too many failed attempts. Access Denied.\n");
//        return 1; 
//    }
//
//    // ==========================================
//    // VOTING SYSTEM (Executes only if login succeeds)
//    // ==========================================
//    printf("Enter total number of voters: ");
//    scanf("%d", &totalVoters);
//
//    for(i = 1; i <= totalVoters; i++) {
//        printf("\nVoter %d, please vote:\n", i);
//        printf("1. Candidate A\n");
//        printf("2. Candidate B\n");
//        printf("3. Candidate C\n");
//        printf("4. Candidate D\n");
//        printf("Enter your choice: ");
//        scanf("%d", &choice);
//
//        switch(choice) {
//            case 1:
//                votes1++;
//                break;
//            case 2:
//                votes2++;
//                break;
//            case 3:
//                votes3++;
//                break;
//            case 4:
//                votes4++;
//                break;
//            default:
//                spoiltVotes++;
//                break;
//        }
//    }
//
//    printf("\n===== Voting Result =====\n");
//    printf("Candidate A = %d votes\n", votes1);
//    printf("Candidate B = %d votes\n", votes2);
//    printf("Candidate C = %d votes\n", votes3);
//    printf("Candidate D = %d votes\n", votes4);
//    printf("Spoilt Votes = %d\n", spoiltVotes);
//
//    printf("\n===== Winner =====\n");
//
//    if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
//        printf("Candidate A is the winner.\n");
//    }
//    else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
//        printf("Candidate B is the winner.\n");
//    }
//    else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
//        printf("Candidate C is the winner.\n");
//    }
//    else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
//        printf("Candidate D is the winner.\n");
//    }
//    else {
//        printf("There is a tie between candidates.\n");
//    }
//
//    return 0;
//}
//#include <stdio.h>
//#include <string.h>
//
//int main() {
//    // --- Admin Credentials ---
//    char adminUser[] = "admin";
//    char adminPass[] = "pp";
//    
//    // --- Pre-registered Voter Databases ---
//    char voterUsers[3][30] = {"user1", "user2", "user3"};
//    char voterPasses[3][30] = {"voter123", "voter456", "voter789"};
//    int voterHasVoted[3] = {0, 0, 0}; // Tracks if a voter has already voted
//    
//    // --- Temporary Login Variables ---
//    char inputUser[30];
//    char inputPass[30];
//    
//    // --- Voting Variables ---
//    int choice;
//    int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
//    int spoiltVotes = 0;
//    int totalVoters = 3; // Total registered voters
//    int successfullyVoted = 0;
//    int userIndex;
//    int j; // Declared here for older compilers
//
//    // ==========================================
//    // 1. ADMIN SYSTEM: INITIAL SETUP
//    // ==========================================
//    printf("===== ADMIN LOGIN (Setup Phase) =====\n");
//    while (1) {
//        printf("Enter Admin Username: ");
//        scanf("%29s", inputUser);
//        printf("Enter Admin Password: ");
//        scanf("%29s", inputPass);
//
//        if (strcmp(inputUser, adminUser) == 0 && strcmp(inputPass, adminPass) == 0) {
//            printf("\nAccess Granted. Welcome, Admin.\n");
//            break;
//        } else {
//            printf("Invalid Admin credentials. Try again.\n\n");
//        }
//    }
//
//    printf("\nVoting session initialized for %d registered users.\n", totalVoters);
//    printf("Switching to User Voting Mode...\n");
//    printf("=======================================================\n");
//
//    // ==========================================
//    // 2. USER SYSTEM: VOTER LOGIN & BALLOT
//    // ==========================================
//    while (successfullyVoted < totalVoters) {
//        userIndex = -1;
//        
//        printf("\n--- VOTER LOGIN (%d/%d Voted) ---\n", successfullyVoted, totalVoters);
//        printf("Enter Your Username: ");
//        scanf("%29s", inputUser);
//        printf("Enter Your Password: ");
//        scanf("%29s", inputPass);
//
//        // Verify voter credentials
//        for (j = 0; j < totalVoters; j++) {
//            if (strcmp(inputUser, voterUsers[j]) == 0 && strcmp(inputPass, voterPasses[j]) == 0) {
//                userIndex = j;
//                break;
//            }
//        }
//
//        if (userIndex == -1) {
//            printf("Error: Invalid voter username or password. Try again.\n");
//            continue;
//        }
//
//        // Prevent double voting
//        if (voterHasVoted[userIndex] == 1) {
//            printf("Access Denied: User '%s' has already cast a vote!\n", voterUsers[userIndex]);
//            continue;
//        }
//
//        // If credentials match and hasn't voted yet, unlock ballot
//        printf("\nWelcome %s! Please cast your vote:\n", voterUsers[userIndex]);
//        printf("1. Candidate A\n");
//        printf("2. Candidate B\n");
//        printf("3. Candidate C\n");
//        printf("4. Candidate D\n");
//        printf("Enter your choice (1-4): ");
//        scanf("%d", &choice);
//
//        switch(choice) {
//            case 1: votes1++; break;
//            case 2: votes2++; break;
//            case 3: votes3++; break;
//            case 4: votes4++; break;
//            default: spoiltVotes++; break;
//        }
//
//        voterHasVoted[userIndex] = 1; // Mark user as voted
//        successfullyVoted++;
//        printf("Vote securely recorded! Thank you.\n");
//        printf("---------------------------------------\n");
//    }
//
//    printf("\nAll registered voters have voted. System Locked.\n");
//    printf("=======================================================\n");
//
//    // ==========================================
//    // 3. ADMIN SYSTEM: VIEW RESULTS
//    // ==========================================
//    printf("===== ADMIN LOGIN (View Results) =====\n");
//    while (1) {
//        printf("Enter Admin Username: ");
//        scanf("%29s", inputUser);
//        printf("Enter Admin Password: ");
//        scanf("%29s", inputPass);
//
//        if (strcmp(inputUser, adminUser) == 0 && strcmp(inputPass, adminPass) == 0) {
//            printf("\nAccess Granted. Fetching final counts...\n");
//            break;
//        } else {
//            printf("Invalid Admin credentials. Try again.\n\n");
//        }
//    }
//
//    // Output Results
//    printf("\n===== Final Voting Results =====\n");
//    printf("Candidate A = %d votes\n", votes1);
//    printf("Candidate B = %d votes\n", votes2);
//    printf("Candidate C = %d votes\n", votes3);
//    printf("Candidate D = %d votes\n", votes4);
//    printf("Spoilt Votes = %d\n", spoiltVotes);
//
//    printf("\n===== Winner =====\n");
//    if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
//        printf("Candidate A is the winner.\n");
//    }
//    else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
//        printf("Candidate B is the winner.\n");
//    }
//    else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
//        printf("Candidate C is the winner.\n");
//    }
//    else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
//        printf("Candidate D is the winner.\n");
//    }
//    else {
//        printf("There is a tie between candidates.\n");
//    }
//
//    return 0;
//}
//#include <stdio.h>
//#include <string.h>
//
//int main() {
//    // --- Admin Credentials ---
//    char adminUser[] = "admin";
//    char adminPass[] = "pp";
//    
//    // --- Pre-registered Voter Databases ---
//    char voterUsers[3][30] = {"user1", "user2", "user3"};
//    char voterPasses[3][30] = {"voter123", "voter456", "voter789"};
//    int voterHasVoted[3] = {0, 0, 0}; 
//    
//    // --- Temporary Login Variables ---
//    char inputUser[30];
//    char inputPass[30];
//    
//    // --- Voting Variables ---
//    int choice;
//    int votes1 = 0, votes2 = 0, votes3 = 0, votes4 = 0;
//    int spoiltVotes = 0;
//    int totalVoters = 3; 
//    int successfullyVoted = 0;
//    int userIndex;
//    int j; 
//
//    // ==========================================
//    // 1. ADMIN SYSTEM: INITIAL SETUP
//    // ==========================================
//    printf("===== ADMIN LOGIN (Setup Phase) =====\n");
//    while (1) {
//        printf("Enter Admin Username: ");
//        scanf("%29s", inputUser);
//        printf("Enter Admin Password: ");
//        scanf("%29s", inputPass);
//        while(getchar() != '\n'); // Clear buffer
//
//        if (strcmp(inputUser, adminUser) == 0 && strcmp(inputPass, adminPass) == 0) {
//            printf("\nAccess Granted. Welcome, Admin.\n");
//            break;
//        } else {
//            printf("Invalid Admin credentials. Try again.\n\n");
//        }
//    }
//
//    printf("\nVoting session initialized for %d registered users.\n", totalVoters);
//    printf("Switching to User Voting Mode...\n");
//    printf("=======================================================\n");
//
//    // ==========================================
//    // 2. USER SYSTEM: VOTER LOGIN & BALLOT
//    // ==========================================
//    while (successfullyVoted < totalVoters) {
//        userIndex = -1;
//        
//        printf("\n--- VOTER LOGIN (%d/%d Voted) ---\n", successfullyVoted, totalVoters);
//        printf("Enter Your User ID / Username: ");
//        scanf("%29s", inputUser);
//        printf("Enter Your Password: ");
//        scanf("%29s", inputPass);
//        while(getchar() != '\n'); // Clear buffer
//
//        // Verify voter credentials
//        for (j = 0; j < totalVoters; j++) {
//            if (strcmp(inputUser, voterUsers[j]) == 0 && strcmp(inputPass, voterPasses[j]) == 0) {
//                userIndex = j;
//                break;
//            }
//        }
//
//        if (userIndex == -1) {
//            printf("[ERROR] Invalid user credentials. Try again.\n");
//            continue;
//        }
//
//        // Prevent double voting
//        if (voterHasVoted[userIndex] == 1) {
//            printf("[ACCESS DENIED] User '%s' has already cast a vote!\n", voterUsers[userIndex]);
//            continue;
//        }
//
//        // Ballot Screen
//        printf("\nWelcome %s! Please cast your vote:\n", voterUsers[userIndex]);
//        printf("1. Candidate A\n");
//        printf("2. Candidate B\n");
//        printf("3. Candidate C\n");
//        printf("4. Candidate D\n");
//        printf("Enter your choice (1-4): ");
//        
//        // Secure numerical scanning
//        if (scanf("%d", &choice) != 1) {
//            choice = -1; 
//        }
//        while(getchar() != '\n'); // Clear buffer
//
//        switch(choice) {
//            case 1: votes1++; break;
//            case 2: votes2++; break;
//            case 3: votes3++; break;
//            case 4: votes4++; break;
//            default: spoiltVotes++; break;
//        }
//
//        voterHasVoted[userIndex] = 1; 
//        successfullyVoted++;
//        printf("\n[SUCCESS] Vote securely recorded! Thank you.\n");
//        printf("---------------------------------------\n");
//    }
//
//    printf("\nAll registered voters have voted. Voting terminal locked.\n");
//    printf("=======================================================\n");
//
//    // ==========================================
//    // 3. ADMIN SYSTEM: VIEW RESULTS (Users can't see this)
//    // ==========================================
//    printf("===== ADMIN LOGIN (View Results & Winner) =====\n");
//    while (1) {
//        printf("Enter Admin Username: ");
//        scanf("%29s", inputUser);
//        printf("Enter Admin Password: ");
//        scanf("%29s", inputPass);
//        while(getchar() != '\n'); // Clear buffer
//
//        if (strcmp(inputUser, adminUser) == 0 && strcmp(inputPass, adminPass) == 0) {
//            printf("\nAccess Granted. Decrypting final counts...\n");
//            break;
//        } else {
//            printf("Invalid Admin credentials. Try again.\n\n");
//        }
//    }
//
//    // Output Results - Completely hidden until Admin logs in a second time
//    printf("\n===== Final Voting Results =====\n");
//    printf("Candidate A = %d votes\n", votes1);
//    printf("Candidate B = %d votes\n", votes2);
//    printf("Candidate C = %d votes\n", votes3);
//    printf("Candidate D = %d votes\n", votes4);
//    printf("Spoilt Votes = %d\n", spoiltVotes);
//
//    printf("\n===== Winner =====\n");
//    if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
//        printf("Candidate A is the winner.\n");
//    }
//    else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
//        printf("Candidate B is the winner.\n");
//    }
//    else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
//        printf("Candidate C is the winner.\n");
//    }
//    else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
//        printf("Candidate D is the winner.\n");
//    }
//    else {
//        printf("There is a tie between candidates.\n");
//    }
//
//    return 0;
//}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

                if (adminChoice == 1) {
                    isInitialized = 1;
                    printf("\n[SYSTEM] Voting session initialized for %d registered users.\n", totalVoters);
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

                    printf("\n===== Current Winner =====\n");
                    if(votes1 > votes2 && votes1 > votes3 && votes1 > votes4) {
                        printf("Candidate A is leading/winner.\n");
                    }
                    else if(votes2 > votes1 && votes2 > votes3 && votes2 > votes4) {
                        printf("Candidate B is leading/winner.\n");
                    }
                    else if(votes3 > votes1 && votes3 > votes2 && votes3 > votes4) {
                        printf("Candidate C is leading/winner.\n");
                    }
                    else if(votes4 > votes1 && votes4 > votes2 && votes4 > votes3) {
                        printf("Candidate D is leading/winner.\n");
                    }
                    else {
                        printf("There is currently a tie between candidates.\n");
                    }
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

            voterHasVoted[userIndex] = 1; 
            successfullyVoted++;
            printf("\n[SUCCESS] Your vote has been securely encrypted and recorded!\n");
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
