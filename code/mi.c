#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUESTIONS 100
#define MAX_LENGTH 256
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password" 
#define QUESTION_FILE "questions.dat"
#define TEXT_FILE "questions.txt"  
#define SCORE_FILE "scores.dat"

// ============================================================================
// DATA STRUCTURES
// ============================================================================
typedef struct {
    char question[MAX_LENGTH];
    char options[4][MAX_LENGTH];
    char correctOption;
} Question;

typedef struct {
    Question questions[MAX_QUESTIONS];
    int count;
} Quiz;

typedef struct {
    char username[MAX_LENGTH];
    int score;
} UserScore;

// ============================================================================
// FUNCTION DECLARATIONS
// ============================================================================
void displayHomePage(Quiz *quiz);
void displayAdminMenu();
void displayUserMenu();
void addQuestion(Quiz *quiz);
void viewQuestion(Quiz *quiz);
void updateQuestion(Quiz *quiz);
void deleteQuestion(Quiz *quiz);
int adminLogin();
void adminProcess(Quiz *quiz);
void userProcess(Quiz *quiz);

// Game Engine Sub-modules
void playMillionaireGame(Quiz *quiz);
void showHelp();
void resetScores();
void viewUserScores();
void saveUserScore(const char *username, int score);
void loadQuestionsFromFile(Quiz *quiz);
void saveQuestionsToFile(Quiz *quiz);
void saveQuestionsToTextFile(Quiz *quiz);

// Safe cross-platform console clearing & buffer handling
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char getChoiceChar() {
    char ch = getchar();
    if (ch != '\n' && ch != EOF) {
        clearInputBuffer();
    }
    return toupper((unsigned char)ch);
}

// ============================================================================
// MAIN EXECUTION ROUTINE
// ============================================================================
int main() {
    Quiz quiz;
    quiz.count = 0;
    loadQuestionsFromFile(&quiz);

    while (1) {
        displayHomePage(&quiz);
    }
    return 0;
}

// ============================================================================
// MENU & ROUTING SYSTEM
// ============================================================================
void displayHomePage(Quiz *quiz) {
    int roleChoice = 0;
    printf("\n                QUIZ Game System\n");
    printf("||===============================================================||\n");
    printf("||                Home Page                                      ||\n");
    printf("||              Your role:                                       ||\n");
    printf("||         1. Admin                                              ||\n");
    printf("||         2. User (Play Millionaire Quiz)                       ||\n");
    printf("||         3. Exit                                               ||\n");
    printf("||         Enter your choice:                                    ||\n");
    printf("||===============================================================||\n");
    printf("Enter choice: ");
    
    if (scanf("%d", &roleChoice) != 1) {
        clearInputBuffer();
        printf("Invalid input. Please enter a number.\n");
        return;
    }
    clearInputBuffer(); 
    
    if (roleChoice == 1) {
        if (adminLogin() == 1) {
            adminProcess(quiz);
        } else {
            printf("Invalid username or password.\n");
        }
    } else if (roleChoice == 2) {
        userProcess(quiz);
    } else if (roleChoice == 3) {
        saveQuestionsToFile(quiz);
        saveQuestionsToTextFile(quiz);
        printf("Exiting...\n");
        exit(0);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

void displayAdminMenu() {
    printf("\n!!================================================================!!\n");
    printf("||             Admin Menu                                        ||\n");
    printf("||             1. Add Question                                   ||\n");
    printf("||             2. View Question                                  ||\n");
    printf("||             3. Update Question                                ||\n");
    printf("||             4. Delete Question                                ||\n");
    printf("||             5. View User Scores Leaderboard                   ||\n");
    printf("||             6. Logout                                         ||\n");
    printf("||      Choose a number according to your requirement            ||\n");
    printf("!!================================================================!!\n");
}

void displayUserMenu() {
    printf("\n||=================== User Menu ===================||\n");
    printf("||  S. Start the Game                              ||\n");
    printf("||  V. View the Leaderboard High Scores            ||\n");
    printf("||  R. Reset Local Score sheets                    ||\n");
    printf("||  H. Read Game Tips / Help                       ||\n");
    printf("||  Q. Quit to Main Menu                           ||\n");
    printf("||=================================================||\n");
}

// ============================================================================
// ADMIN MODERATION OPERATIONS
// ============================================================================
int adminLogin() {
    char username[50];
    char password[50];

    printf("Enter admin username: ");
    scanf("%49s", username);
    printf("Enter admin password: ");
    scanf("%49s", password);
    clearInputBuffer();

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        return 1; 
    } else {
        return 0; 
    }
}

void adminProcess(Quiz *quiz) {
    int choice;
    do {
        displayAdminMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid entry.\n");
            continue;
        }
        clearInputBuffer(); 
        
        switch (choice) {
            case 1: addQuestion(quiz); break;
            case 2: viewQuestion(quiz); break;
            case 3: updateQuestion(quiz); break;
            case 4: deleteQuestion(quiz); break;
            case 5: viewUserScores(); break;
            case 6: printf("Logging out from Admin dashboard...\n"); return;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void addQuestion(Quiz *quiz) {
    int i;
    if (quiz->count >= MAX_QUESTIONS) {
        printf("Question limit reached!\n");
        return;
    }

    Question q;
    printf("Enter the question: ");
    fgets(q.question, MAX_LENGTH, stdin);
    q.question[strcspn(q.question, "\n")] = 0;  

    for (i = 0; i < 4; i++) {
        printf("Enter option %c: ", 'A' + i);
        fgets(q.options[i], MAX_LENGTH, stdin);
        q.options[i][strcspn(q.options[i], "\n")] = 0;  
    }

    printf("Enter the correct option (A, B, C, or D): ");
    q.correctOption = getChoiceChar();

    quiz->questions[quiz->count++] = q;
    printf("Question added successfully!\n");
    saveQuestionsToFile(quiz);
    saveQuestionsToTextFile(quiz);
}

void viewQuestion(Quiz *quiz) {
    int i, j;
    if (quiz->count == 0) {
        printf("No custom questions available inside the storage systems.\n");
        return;
    }

    for (i = 0; i < quiz->count; i++) {
        printf("\nQuestion %d: %s\n", i + 1, quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            printf("  Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        printf("Correct Option: %c\n", quiz->questions[i].correctOption);
    }
}

void updateQuestion(Quiz *quiz) {
    int questionIndex, i;

    printf("Enter question number to update (1 to %d): ", quiz->count);
    if (scanf("%d", &questionIndex) != 1) {
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    questionIndex--; 

    if (questionIndex >= 0 && questionIndex < quiz->count) {
        printf("Enter new question (leave blank to keep current): ");
        char newQuestion[MAX_LENGTH];
        fgets(newQuestion, sizeof(newQuestion), stdin);
        newQuestion[strcspn(newQuestion, "\n")] = 0; 
        if (strlen(newQuestion) > 0) {
            strcpy(quiz->questions[questionIndex].question, newQuestion);
        }

        for (i = 0; i < 4; i++) {
            printf("Enter new option %c (leave blank to keep current): ", 'A' + i);
            char newOption[MAX_LENGTH];
            fgets(newOption, sizeof(newOption), stdin);
            newOption[strcspn(newOption, "\n")] = 0; 
            if (strlen(newOption) > 0) {
                strcpy(quiz->questions[questionIndex].options[i], newOption);
            }
        }

        printf("Enter new correct option (A, B, C, D or leave blank to keep current): ");
        char inputStr[10];
        fgets(inputStr, sizeof(inputStr), stdin);
        if (inputStr[0] != '\n' && (toupper((unsigned char)inputStr[0]) >= 'A' && toupper((unsigned char)inputStr[0]) <= 'D')) {
            quiz->questions[questionIndex].correctOption = toupper((unsigned char)inputStr[0]);
        }

        printf("Question updated successfully.\n");
        saveQuestionsToFile(quiz);
        saveQuestionsToTextFile(quiz);
    } else {
        printf("Invalid question number.\n");
    }
}

void deleteQuestion(Quiz *quiz) {
    int questionIndex, i;

    printf("Enter question number to delete (1 to %d): ", quiz->count);
    if (scanf("%d", &questionIndex) != 1) {
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    questionIndex--; 

    if (questionIndex >= 0 && questionIndex < quiz->count) {
        for (i = questionIndex; i < quiz->count - 1; i++) {
            quiz->questions[i] = quiz->questions[i + 1];
        }

        quiz->count--;
        printf("Question deleted successfully!\n");
        saveQuestionsToFile(quiz);
        saveQuestionsToTextFile(quiz);
    } else {
        printf("Invalid question number.\n");
    }
}

// ============================================================================
// MILLIONAIRE USER GAME ENGINE
// ============================================================================
void userProcess(Quiz *quiz) {
    char choice;
    do {
        displayUserMenu();
        printf("Enter your option: ");
        choice = getChoiceChar();
        
        switch (choice) {
            case 'S': playMillionaireGame(quiz); break;
            case 'V': viewUserScores(); break;
            case 'R': resetScores(); break;
            case 'H': showHelp(); break;
            case 'Q': return;
            default: printf("Invalid option choice. Try again.\n");
        }
    } while (1);
}

void playMillionaireGame(Quiz *quiz) {
    char playername[MAX_LENGTH];
    int count = 0, countr = 0, i;
    double score = 0.0;

    clearScreen();
    printf("\n\n\t\tRegister your profile name: ");
    fgets(playername, sizeof(playername), stdin);
    playername[strcspn(playername, "\n")] = 0;

    clearScreen();
    printf("\n ------------------  Welcome %s to C Program Quiz Game --------------------------", playername);
    printf("\n\n Here are some tips you might wanna know before playing:");
    printf("\n -------------------------------------------------------------------------");
    printf("\n >> There are 2 rounds in this Quiz Game: WARMUP ROUND & CHALLENGE ROUND");
    printf("\n >> In warmup round you will be asked 3 questions. You must answer at least 2");
    printf("\n    correctly to qualify for the high-reward Challenge Round.");
    printf("\n >> In CHALLENGE ROUND, each correct answer rewards you $100,000 progress.");
    printf("\n    Win up to ONE MILLION dollars cash prizes!");
    printf("\n >> Press A, B, C, or D to locking down choices.");
    printf("\n >> No negative marking for wrong answers!");
    printf("\n\n\t!!!!!!!!!!!!! ALL THE BEST !!!!!!!!!!!!!");
    printf("\n\n Press Y to start the game, any other key to abort: ");
    
    if (getChoiceChar() != 'Y') return;

    // --- PHASE 1: WARMUP ROUND ---
    for (i = 1; i <= 3; i++) {
        clearScreen();
        printf("\n--- WARMUP ROUND (Question %d of 3) ---", i);
        if (i == 1) {
            printf("\n\nWhich of the following is a Palindrome number?");
            printf("\n\nA. 42042\t\tB. 101010\n\nC. 23232\t\tD. 01234\n\nYour Answer: ");
            if (getChoiceChar() == 'C') { printf("\nCorrect!!!"); count++; } 
            else { printf("\nWrong!!! The correct answer was C.23232"); }
        } else if (i == 2) {
            printf("\n\nThe country with the highest environmental performance index is...");
            printf("\n\nA. France\t\tB. Denmark\n\nC. Switzerland\t\tD. Finland\n\nYour Answer: ");
            if (getChoiceChar() == 'C') { printf("\nCorrect!!!"); count++; } 
            else { printf("\nWrong!!! The correct answer was C.Switzerland"); }
        } else if (i == 3) {
            printf("\n\nWhich animal laughs like a human being?");
            printf("\n\nA. Polar Bear\t\tB. Hyena\n\nC. Donkey\t\tD. Chimpanzee\n\nYour Answer: ");
            if (getChoiceChar() == 'B') { printf("\nCorrect!!!"); count++; } 
            else { printf("\nWrong!!! The correct answer was B.Hyena"); }
        }
        printf("\n\nPress Enter to continue...");
        getchar();
    }

    if (count < 2) {
        clearScreen();
        printf("\n\nSORRY YOU ARE NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME");
        printf("\nPress Enter to return to menu...");
        getchar();
        return;
    }

    clearScreen();
    printf("\n\n\t*** CONGRATULATIONS %s, you passed the selection filter! ***", playername);
    printf("\n\tPress Enter to launch the CHALLENGE ROUND...");
    getchar();

    // --- PHASE 2: CHALLENGE ROUND ---
    for (i = 1; i <= 10; i++) {
        clearScreen();
        printf("\n--- CHALLENGE ROUND (Question %d of 10) ---", i);
        int wrong = 0;

        switch(i) {
            case 1:
                printf("\n\nWhat is the National Game of England?");
                printf("\n\nA. Football\t\tB. Basketball\n\nC. Cricket\t\tD. Baseball\n\nYour Answer: ");
                if (getChoiceChar() == 'C') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was C.Cricket"); wrong = 1; }
                break;
            case 2:
                printf("\n\nStudy of Earthquake is called............,");
                printf("\n\nA. Seismology\t\tB. Cosmology\n\nC. Orology\t\tD. Etimology\n\nYour Answer: ");
                if (getChoiceChar() == 'A') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was A.Seismology"); wrong = 1; }
                break;
            case 3:
                printf("\n\nAmong the top 10 highest peaks in the world, how many lie in Nepal?");
                printf("\n\nA. 6\t\tB. 7\n\nC. 8\t\tD. 9\n\nYour Answer: ");
                if (getChoiceChar() == 'C') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was C.8"); wrong = 1; }
                break;
            case 4:
                printf("\n\nThe Laws of Electromagnetic Induction were given by?");
                printf("\n\nA. Faraday\t\tB. Tesla\n\nC. Maxwell\t\tD. Coulomb\n\nYour Answer: ");
                if (getChoiceChar() == 'A') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was A.Faraday"); wrong = 1; }
                break;
            case 5:
                printf("\n\nIn what unit is electric power measured?");
                printf("\n\nA. Coulomb\t\tB. Watt\n\nC. Power\t\tD. Units\n\nYour Answer: ");
                if (getChoiceChar() == 'B') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was B.Watt"); wrong = 1; }
                break;
            case 6:
                printf("\n\nWhich element is found in Vitamin B12?");
                printf("\n\nA. Zinc\t\tB. Cobalt\n\nC. Calcium\t\tD. Iron\n\nYour Answer: ");
                if (getChoiceChar() == 'B') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was B.Cobalt"); wrong = 1; }
                break;
            case 7:
                printf("\n\nWhat is the National Name of Japan?");
                printf("\n\nA. Polska\t\tB. Hellas\n\nC. Drukyul\t\tD. Nippon\n\nYour Answer: ");
                if (getChoiceChar() == 'D') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was D.Nippon"); wrong = 1; }
                break;
            case 8:
                printf("\n\nHow many times a piece of paper can be folded at the most?");
                printf("\n\nA. 6\t\tB. 7\n\nC. 8\t\tD. Paper Size Dependent\n\nYour Answer: ");
                if (getChoiceChar() == 'B') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was B.7"); wrong = 1; }
                break;
            case 9:
                printf("\n\nWhat is the capital of Denmark?");
                printf("\n\nA. Copenhagen\t\tB. Helsinki\n\nC. Ajax\t\tD. Galatasaray\n\nYour Answer: ");
                if (getChoiceChar() == 'A') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was A.Copenhagen"); wrong = 1; }
                break;
            case 10:
                printf("\n\nWhich is the longest River in the world?");
                printf("\n\nA. Nile\t\tB. Koshi\n\nC. Ganga\t\tD. Amazon\n\nYour Answer: ");
                if (getChoiceChar() == 'A') { printf("\nCorrect!!!"); countr++; }
                else { printf("\nWrong!!! The correct answer was A.Nile"); wrong = 1; }
                break;
        }

        printf("\n\nPress Enter to continue...");
        getchar();
        if (wrong) break; 
    }

    // Calculate score
    score = countr * 100000;
    clearScreen();
    if (score > 0 && score < 1000000) {
        printf("\n\n\t\t**************** CONGRATULATIONS *****************");
        printf("\n\t You won $%.2f", score);
    } else if (score == 1000000) {
        printf("\n\n\n \t\t**************** CONGRATULATIONS ****************");
        printf("\n\t\t\t\t YOU ARE A MILLIONAIRE!!!!!!!!!");
        printf("\n\t\t You won $%.2f", score);
    } else {
        printf("\n\n\t******** SORRY YOU DIDN'T WIN ANY CASH ********");
        printf("\n\t\t Thanks for your participation.");
    }

    saveUserScore(playername, (int)score);

    printf("\n\nPress Enter to continue...");
    getchar();
}

// ============================================================================
// AUXILIARY STORAGE MANAGEMENT & HISTORIES
// ============================================================================
void showHelp() {
    clearScreen();
    printf("\n\n                              HELP MANUAL");
    printf("\n -------------------------------------------------------------------------");
    printf("\n >> Warmup round presents 3 questions. Give 2 right answers to qualify.");
    printf("\n >> Challenge round scales up with 10 questions. Each counts for $100,000.");
    printf("\n >> Striking out an answer drops out execution directly to score tracking windows.");
    printf("\n -------------------------------------------------------------------------");
    printf("\n\n Press Enter to return to choices...");
    getchar();
}

void resetScores() {
    clearScreen();
    FILE *fp = fopen(SCORE_FILE, "w");
    if (fp != NULL) {
        fclose(fp);
        printf("\nDatabase scores logs cleared successfully.\n");
    } else {
        printf("\nError accessing storage system files.\n");
    }
    printf("\nPress Enter to return...");
    getchar();
}

void viewUserScores() {
    clearScreen();
    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp == NULL) {
        printf("\nNo leaderboard historical configurations registered yet.\n");
        return;
    }

    printf("\n===== User Scores Leaderboard =====\n");
    char username[MAX_LENGTH];
    int score;

    while (fscanf(fp, "%255s %d", username, &score) == 2) {
        printf("Player: %-20s | Prize Won: $%d\n", username, score);
    }

    fclose(fp);
    printf("\nPress Enter to safely exit history loops...");
    getchar();
}

void saveUserScore(const char *username, int score) {
    FILE *fp = fopen(SCORE_FILE, "a");
    if (fp == NULL) {
        return;
    }
    fprintf(fp, "%s %d\n", username, score);
    fclose(fp);
}

void loadQuestionsFromFile(Quiz *quiz) {
    FILE *fp = fopen(QUESTION_FILE, "rb");
    if (fp == NULL) {
        return;
    }
    quiz->count = 0;
    while (quiz->count < MAX_QUESTIONS && fread(&quiz->questions[quiz->count], sizeof(Question), 1, fp) == 1) {
        quiz->count++;
    }
    fclose(fp);
}

void saveQuestionsToFile(Quiz *quiz) {
    FILE *fp = fopen(QUESTION_FILE, "wb");
    if (fp == NULL) return;
    fwrite(quiz->questions, sizeof(Question), quiz->count, fp);
    fclose(fp);
}

void saveQuestionsToTextFile(Quiz *quiz) {
    int i, j;
    FILE *fp = fopen(TEXT_FILE, "w");
    if (fp == NULL) return;

    for (i = 0; i < quiz->count; i++) {
        fprintf(fp, "Question: %s\n", quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            fprintf(fp, "Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        fprintf(fp, "Correct Option: %c\n\n", quiz->questions[i].correctOption);
    }
    fclose(fp);
}
