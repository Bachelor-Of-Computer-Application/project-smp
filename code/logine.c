#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 100
#define MAX_LENGTH 256
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"
#define QUESTION_FILE "questions.dat"
#define TEXT_FILE "questions.txt"

typedef struct {
    char question[MAX_LENGTH];
    char options[4][MAX_LENGTH];
    char correctOption;
    int id;
} Question;

typedef struct {
    Question questions[MAX_QUESTIONS];
    int count;
} Quiz;

void displayHomePage(Quiz *quiz);
void displayAdminMenu();
void displayUserMenu();
void addQuestion(Quiz *quiz);
void viewQuestion(Quiz *quiz);
void updateQuestion(Quiz *quiz);
void deleteQuestion(Quiz *quiz);
int adminLogin();
void userViewQuestion(Quiz *quiz);
void adminProcess(Quiz *quiz);
void loadQuestionsFromFile(Quiz *quiz);
void saveQuestionsToFile(Quiz *quiz);
void saveQuestionsToTextFile(Quiz *quiz);

int main() {
    Quiz quiz;
    quiz.count = 0;
    loadQuestionsFromFile(&quiz);

    while (1) {
        displayHomePage(&quiz);
    }

    return 0;
}

void displayHomePage(Quiz *quiz) {
    int roleChoice;
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
    scanf("%d", &roleChoice);
    
    if (roleChoice == 1) {
        if (adminLogin() == 1) {
            adminProcess(quiz);
        } else {
            printf("Invalid username or password.\n");
        }
    } else if (roleChoice == 2) {
        userViewQuestion(quiz);
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
    printf("||             5. Logout                                         ||\n");
    printf("||      Choose a number according to your requirement            ||\n");
    printf("!!================================================================!!\n");    
}

void displayUserMenu() {
    printf("||====User Menu====||\n");
    printf("||  1. View Question  ||\n");
    printf("||  2. Logout         ||\n");
    printf("||===================||\n");
}

int adminLogin() {
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
    q.id = quiz->count + 1; // Assign ID to the question
    printf("Enter the question: ");
    getchar();  // Consume the newline character left by the previous input
    fgets(q.question, MAX_LENGTH, stdin);
    q.question[strcspn(q.question, "\n")] = 0;  // Remove the newline character

    for (i = 0; i < 4; i++) {
        printf("Enter option %c: ", 'A' + i);
        fgets(q.options[i], MAX_LENGTH, stdin);
        q.options[i][strcspn(q.options[i], "\n")] = 0;  
    }

    printf("Enter the correct option (A, B, C, or D): ");
    scanf(" %c", &q.correctOption);

    quiz->questions[quiz->count++] = q;
    printf("Question added successfully with ID: %d\n", q.id);
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
        printf("\nID: %d | Question: %s\n", quiz->questions[i].id, quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            printf("  Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        printf("Correct Option: %c\n", quiz->questions[i].correctOption);
    }
}

void updateQuestion(Quiz *quiz) {
    int id, i;
    
    printf("Enter the Question ID to update: ");
    scanf("%d", &id);

    int index = -1;
    for (i = 0; i < quiz->count; i++) {
        if (quiz->questions[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Enter new question (leave blank to keep current): ");
        getchar(); // clear newline buffer
        char newQuestion[MAX_LENGTH];
        fgets(newQuestion, sizeof(newQuestion), stdin);
        newQuestion[strcspn(newQuestion, "\n")] = 0; 
        if (strlen(newQuestion) > 0) {
            strcpy(quiz->questions[index].question, newQuestion);
        }

        for (i = 0; i < 4; i++) {
            printf("Enter new option %c (leave blank to keep current): ", 'A' + i);
            char newOption[MAX_LENGTH];
            fgets(newOption, sizeof(newOption), stdin);
            newOption[strcspn(newOption, "\n")] = 0; 
            if (strlen(newOption) > 0) {
                strcpy(quiz->questions[index].options[i], newOption);
            }
        }

        printf("Enter new correct option (A,B,C,D or space to keep current): ");
        char newCorrectOption;
        scanf(" %c", &newCorrectOption);
        if (newCorrectOption >= 'A' && newCorrectOption <= 'D') {
            quiz->questions[index].correctOption = newCorrectOption;
        }

        printf("Question updated successfully.\n");
        saveQuestionsToFile(quiz);
        saveQuestionsToTextFile(quiz);
    } else {
        printf("Question not found.\n");
    }
}

void deleteQuestion(Quiz *quiz) {
    int id, i;
    printf("Enter the Question ID to delete: ");
    scanf("%d", &id);

    int index = -1;
    for (i = 0; i < quiz->count; i++) {
        if (quiz->questions[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (i = index; i < quiz->count - 1; i++) {
            quiz->questions[i] = quiz->questions[i + 1];
            // Readjust subsequent IDs so they match the structural tracking array index
            quiz->questions[i].id = i + 1; 
        }

        quiz->count--;
        printf("Question deleted successfully!\n");
        saveQuestionsToFile(quiz);
        saveQuestionsToTextFile(quiz);
    } else {
        printf("Question not found.\n");
    }
}

void userViewQuestion(Quiz *quiz) {
    viewQuestion(quiz);
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
        fprintf(fp, "ID: %d | Question: %s\n", quiz->questions[i].id, quiz->questions[i].question);
        for (j = 0; j < 4; j++) {
            fprintf(fp, "Option %c: %s\n", 'A' + j, quiz->questions[i].options[j]);
        }
        fprintf(fp, "Correct Option: %c\n\n", quiz->questions[i].correctOption);
    }

    fclose(fp);
}

