//quiz game
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 100
#define MAX_LENGTH 256
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "*****"
#define QUESTION_FILE "questions.dat"
#define TEXT_FILE "save/questions.txt"
#define SCORE_FILE "scores.dat"
//
typedef struct {
    char question[MAX_LENGTH];
    char options[4][MAX_LENGTH];
    char correctOption;
} Question;
////
typedef struct {
    Question questions[MAX_QUESTIONS];
    int count;
} Quiz;

typedef struct {
    char username[MAX_LENGTH];
    int score;
} UserScore;
//
// Function declaration 
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
int loadUserScore(const char *username);

int main() {
    Quiz quiz;
    quiz.count = 0;
    loadQuestionsFromFile(&quiz);

    while (1) {
        displayHomePage(&quiz);
    }

    return 0;
}
//homepage
void displayHomePage(Quiz *quiz) {//enter home page
    introleChoice;
    printf("                QUIZ Game System\n");
    printf("||===============================================================||\n");
    printf("||                Home Page                                      ||\n");
    printf("||              Your role:                                       ||\n");
    printf("||         1. Admin                                              ||\n");
    printf("||         2. User                                               ||\n");
    printf("||         3. Exit                                               ||\n");
    printf("||         Enter your choice:                                    ||\n");
    printf("||===============================================================||\n");
    scanf("%d", &roleChoice);
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

void displayAdminMenu(){//enter admin section 
    printf("!!================================================================!!\n");
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
    printf("||====User Menu====||\n");
    printf("||  1. View Questions ||\n");
    printf("||  2. Logout         ||\n");
    printf("||===================||\n");
}

int adminLogin()//admin login page {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}

void adminProcess(Quiz *quiz) {
    int choice;
    do {
        displayAdminMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addQuestion(quiz);
                break;
            case 2:
                viewQuestion(quiz);
                break;
            case 3:
                updateQuestion(quiz);
                break;
            case 4:
                deleteQuestion(quiz);
                break;
            case 5:
                viewUserScores();
                break;
            case 6:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
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
    getchar();  // to consume the newline character left by the previous input
    fgets(q.question, MAX_LENGTH, stdin);
    q.question[strcspn(q.question, "\n")] = 0;  // Remove the newline character

    for (i = 0; i < 4; i++) {
        printf("Enter option %c: ", 'A' + i);
        fgets(q.options[i], MAX_LENGTH, stdin);
        q.options[i][strcspn(q.options[i], "\n")] = 0;  // Remove the newline character
    }

    printf("Enter the correct option (A, B, C, or D): ");
    scanf(" %c", &q.correctOption);

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
        printf("Question %d: %s\n", i + 1, quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            printf("Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        printf("Correct Option: %c\n\n", quiz->questions[i].correctOption);
    }
}

void updateQuestion(Quiz *quiz) {
    int questionIndex, i;

    printf("Enter question number to update (1 to %d): ", quiz->count);
    scanf("%d", &questionIndex);
    questionIndex--; // to convert to zero-based index

    if (questionIndex >= 0 && questionIndex < quiz->count) {
        printf("Enter new question (leave blank to keep current): ");
        getchar(); // to consume the newline character left by scanf
        char newQuestion[MAX_LENGTH];
        fgets(newQuestion, sizeof(newQuestion), stdin);
        newQuestion[strcspn(newQuestion, "\n")] = 0; // Remove trailing newline
        if (strlen(newQuestion) > 0) {
            strcpy(quiz->questions[questionIndex].question, newQuestion);
        }

        for (i = 0; i < 4; i++) {
            printf("Enter new option %c (leave blank to keep current): ", 'A' + i);
            char newOption[MAX_LENGTH];
            fgets(newOption, sizeof(newOption), stdin);
            newOption[strcspn(newOption, "\n")] = 0; // Remove trailing newline
            if (strlen(newOption) > 0) {
                strcpy(quiz->questions[questionIndex].options[i], newOption);
            }
        }

        printf("Enter new correct option (A, B, C, or D, leave blank to keep current): ");
        char newCorrectOption = getchar();
        getchar(); // to consume the newline character left by getchar
        if (newCorrectOption != '\n') {
            quiz->questions[questionIndex].correctOption = newCorrectOption;
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
    scanf("%d", &questionIndex);
    questionIndex--; // to convert to zero-based index

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
    getchar();  // to consume the newline character left by the previous input
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;  // Remove the newline character
    printf("Welcome, %s! You can start the quiz now.\n\n", username);
}

void userProcess(Quiz *quiz) {
    int choice;
    char username[MAX_LENGTH];
    userRegister(username);

    do {
        displayUserMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                userViewQuestion(quiz, username);
                break;
            case 2:
                printf("Logging out...\n");
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
        printf("No questions available.\n");
        return;
    }

    for (i = 0; i < quiz->count; i++) {
        printf("Question %d: %s\n", i + 1, quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            printf("Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        char userOption;
        printf("Enter your answer (A, B, C, or D): ");
        scanf(" %c", &userOption);
        if (userOption == quiz->questions[i].correctOption) {
            printf("Correct!\n");
            score += 5;  // Increment score by 5 for a correct answer
        } else {
            printf("Wrong. The correct answer is %c.\n", quiz->questions[i].correctOption);
        }
        printf("\n");
    }

    saveUserScore(username, score);
    printf("%s, your final score is: %d\n", username, score);
}

void loadQuestionsFromFile(Quiz *quiz) {
    FILE *fp = fopen(QUESTION_FILE, "rb");
    if (fp == NULL) {
        printf("No existing data file found. Starting with an empty question list.\n");
        return;
    }

    quiz->count = 0;
    while (fread(&quiz->questions[quiz->count], sizeof(Question), 1, fp) == 1) {
        quiz->count++;
    }
    fclose(fp);
}

void saveQuestionsToFile(Quiz *quiz) {
    FILE *fp = fopen(QUESTION_FILE, "wb");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(quiz->questions, sizeof(Question), quiz->count, fp);
    fclose(fp);
}

void saveQuestionsToTextFile(Quiz *quiz) {
    int i, j;
    FILE *fp = fopen(TEXT_FILE, "w");
    if (fp == NULL) {
        perror("Error opening text file for writing");
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
        perror("Error opening score file for appending");
        return;
    }

    fprintf(fp, "%s %d\n", username, score);
    fclose(fp);
}

void viewUserScores() {
    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp == NULL) {
        printf("No user scores available.\n");
        return;
    }

    printf("===== User Scores =====\n");
    char username[MAX_LENGTH];
    int score;

    while (fscanf(fp, "%s %d", username, &score) == 2) {
        printf("%s: %d\n", username, score);
    }

    fclose(fp);
}

int loadUserScore(const char *username) {
    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp == NULL) {
        return 0; // No score found
    }

    char user[MAX_LENGTH];
    int score;

    while (fscanf(fp, "%s %d", user, &score) == 2) {
        if (strcmp(username, user) == 0) {
            fclose(fp);
            return score;
        }
    }

    fclose(fp);
    return 0; // Username not found
}
