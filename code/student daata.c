#include <stdio.h>
#include <string.h>

struct Address {
    int ward;
    char district[50];
};
struct Student {
    char name[50];
    struct Address addr;  
};
int main() {
    struct Student s[5];
    int i;
    for(i = 0; i < 5; i++) {
        printf("\nEnter details of student %d:\n", i);

        printf("Name");
        scanf(" %s", s[i].name);

        printf("Ward No ");
        scanf("%d", &s[i].addr.ward);

        printf("District ");
        scanf(" %s", s[i].addr.district);
    }

    printf("\nStudents living in Kaski:\n");

    for(i = 0; i < 5; i++) {
        if(strcmp(s[i].addr.district, "Kaski") == 0) {
            printf("\nName: %s", s[i].name);
            printf("\nWard No: %d", s[i].addr.ward);
            printf("\nDistrict: %s\n", s[i].addr.district);
        }
    }

    return 0;
}
