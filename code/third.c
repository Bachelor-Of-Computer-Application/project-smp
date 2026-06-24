//quiz game
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 100
#define MAX_LENGTH 256
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password" // Change to your password
#define QUESTION_FILE "questions.dat"
#define TEXT_FILE "questions.txt"  // Simplified path to avoid missing directory crashes
#define SCORE_FILE "scores.dat"

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

// Function declarations 
void displayHomePage(Quiz *quiz);
void displayAdminMenu();
void displayUserMenu();
void addQuestion(Quiz *quiz);
void viewQuestion(Quiz *quiz);
void updateQuestion(Quiz *quiz);
void deleteQuestion(Quiz *quiz);
int adminLogin();
void userRegister(char *username);
void userViewQuestion(Quiz *quiz, char *username);
void adminProcess(Quiz *quiz);
void loadQuestionsFromFile(Quiz *quiz);
void saveQuestionsToFile(Quiz *quiz);
void saveQuestionsToTextFile(Quiz *quiz);
void userProcess(Quiz *quiz);
void saveUserScore(const char *username, int score);
void viewUserScores();

// Global utility helper to clear remaining input line safely
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Quiz quiz;
    quiz.count = 0;
    loadQuestionsFromFile(&quiz);

    while (1) {
        displayHomePage(&quiz);
    }

    return 0;
}

// Homepage
void displayHomePage(Quiz *quiz) {
    int roleChoice = 0;
    printf("\n                QUIZ Game System\n");
    printf("||===============================================================||\n");
    printf("||                Home Page                                      ||\n");
    printf("||              Your role:                                       ||\n");
    printf("||         1. Admin                                              ||\n");
    printf("||         2. User                                               ||\n");
    printf("||         3. Exit                                               ||\n");
    printf("||         Enter your choice:                                    ||\n");
    printf("||===============================================================||\n");
    printf("Enter choice: ");
    
    if (scanf("%d", &roleChoice) != 1) {
        clearInputBuffer();
        printf("Invalid input. Please enter a valid number.\n");
        return;
    }
    clearInputBuffer(); // clean trailing newline
    
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
    printf("||             5. View User Scores                               ||\n");
    printf("||             6. Logout                                         ||\n");
    printf("||      Choose a number according to your requirement            ||\n");
    printf("!!================================================================!!\n");
}

void displayUserMenu() {
    printf("\n||====User Menu====||\n");
    printf("||  1. Take the Quiz  ||\n");
    printf("||  2. Logout         ||\n");
    printf("||===================||\n");
}

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
    scanf(" %c", &q.correctOption);
    clearInputBuffer();

    quiz->questions[quiz->count++] = q;
    printf("Question added successfully!\n");
    saveQuestionsToFile(quiz);
    saveQuestionsToTextFile(quiz);
}

void viewQuestion(Quiz *quiz) {
    int i, j;
    if (quiz->count == 0) {
        printf("No questions available.\n");
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
        if (inputStr[0] != '\n' && (inputStr[0] >= 'A' && inputStr[0] <= 'D')) {
            quiz->questions[questionIndex].correctOption = inputStr[0];
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

void userRegister(char *username) {
    printf("Enter your name: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;  
    printf("Welcome, %s! You can start the quiz now.\n", username);
}

void userProcess(Quiz *quiz) {
    int choice;
    char username[MAX_LENGTH];
    userRegister(username);

    do {
        displayUserMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid evaluation.\n");
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                userViewQuestion(quiz, username);
                break;
            case 2:
                printf("Logging out user safely...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void userViewQuestion(Quiz *quiz, char *username) {
    int i, j;
    int score = 0;

    if (quiz->count == 0) {
        printf("No questions available at the moment.\n");
        return;
    }

    for (i = 0; i < quiz->count; i++) {
        printf("\nQuestion %d: %s\n", i + 1, quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            printf("  Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        char userOption;
        printf("Enter your answer (A, B, C, or D): ");
        scanf(" %c", &userOption);
        clearInputBuffer();
        
        if (userOption == quiz->questions[i].correctOption) {
            printf("Correct!\n");
            score += 5;  
        } else {
            printf("Wrong. The correct answer was %c.\n", quiz->questions[i].correctOption);
        }
    }

    saveUserScore(username, score);
    printf("\n%s, your final quiz score is: %d\n", username, score);
}

void loadQuestionsFromFile(Quiz *quiz) {
    FILE *fp = fopen(QUESTION_FILE, "rb");
    if (fp == NULL) {
        printf("No existing binary file found. Beginning with an empty list.\n");
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
    if (fp == NULL) {
        perror("Error opening database file for writing");
        return;
    }

    fwrite(quiz->questions, sizeof(Question), quiz->count, fp);
    fclose(fp);
}

void saveQuestionsToTextFile(Quiz *quiz) {
    int i, j;
    FILE *fp = fopen(TEXT_FILE, "w");
    if (fp == NULL) {
        perror("Error creating text file layout backup");
        return;
    }

    for (i = 0; i < quiz->count; i++) {
        fprintf(fp, "Question: %s\n", quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            fprintf(fp, "Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        fprintf(fp, "Correct Option: %c\n\n", quiz->questions[i].correctOption);
    }

    fclose(fp);
}

void saveUserScore(const char *username, int score) {
    FILE *fp = fopen(SCORE_FILE, "a");
    if (fp == NULL) {
        perror("Error opening score data sheet");
        return;
    }

    fprintf(fp, "%s %d\n", username, score);
    fclose(fp);
}

void viewUserScores() {
    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp == NULL) {
        printf("No user logs or scores recorded yet.\n");
        return;
    }

    printf("\n===== User Scores Leaderboard =====\n");
    char username[MAX_LENGTH];
    int score;

    while (fscanf(fp, "%255s %d", username, &score) == 2) {
        printf("%s: %d points\n", username, score);
    }

    fclose(fp);
}
