#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[50];
    char bloodGroup[5];
    int age;
} Member;

typedef struct Node{
    Member member;
    struct Node *next;
} Node;

Node *head = NULL;

Node *createNode(Member member){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->member = member;
    newNode->next = NULL;
    return newNode;
}

void addMember(Member member){
    Node *newNode = createNode(member);

    if (head == NULL){
        head = newNode;
        return;
    }

    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL && strcmp(curr->member.bloodGroup, member.bloodGroup) < 0){
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL){
        newNode->next = head;
        head = newNode;
    }
    else{
        prev->next = newNode;
        newNode->next = curr;
    }
}

void deleteMember(char *name){
    if (head == NULL){
        printf("The list is empty.\n");
        return;
    }

    Node *curr = head;
    Node *prev = NULL;

    while (curr != NULL && strcmp(curr->member.name, name) != 0){
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL){
        printf("Member '%s' not found.\n", name);
        return;
    }

    if (prev == NULL){
        head = head->next;
    }
    else{
        prev->next = curr->next;
    }

    free(curr);
    printf("Member '%s' deleted successfully.\n", name);
}

void viewMembers(){
    if (head == NULL){
        printf("The list is empty.\n");
        return;
    }

    Node *curr = head;
    printf("Members:\n");
    while (curr != NULL){
        printf("Name: %s\tBlood Group: %s\tAge: %d\n", curr->member.name, curr->member.bloodGroup, curr->member.age);
        curr = curr->next;
    }
}

void searchMembers(char *bloodGroup){
    if (head == NULL){
        printf("The list is empty.\n");
        return;
    }

    int found = 0;
    Node *curr = head;
    printf("Members with Blood Group '%s':\n", bloodGroup);
    while (curr != NULL && strcmp(curr->member.bloodGroup, bloodGroup) <= 0){
        if (strcmp(curr->member.bloodGroup, bloodGroup) == 0){
            printf("Name: %s\tBlood Group: %s\tAge: %d\n", curr->member.name, curr->member.bloodGroup, curr->member.age);
            found = 1;
        }
        curr = curr->next;
    }

    if (!found){
        printf("No members found with Blood Group '%s'.\n", bloodGroup);
    }
}

void saveData(){
    FILE *file = fopen("members.txt", "w");
    if (file == NULL){
        printf("Error opening file.\n");
        return;
    }

    Node *curr = head;
    while (curr != NULL){
        fprintf(file, "%s;%s;%d\n", curr->member.name, curr->member.bloodGroup, curr->member.age);
        curr = curr->next;
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

void loadData(){
    FILE *file = fopen("members.txt", "r");
    if (file == NULL){
        printf("No data file found.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)){
        char *name = strtok(line, ";");
        char *bloodGroup = strtok(NULL, ";");
        int age = atoi(strtok(NULL, ";\n"));

        Member member;
        strcpy(member.name, name);
        strcpy(member.bloodGroup, bloodGroup);
        member.age = age;

        addMember(member);
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

int main(){
    int choice;
    Member member;
    char name[50];
    char bloodGroup[5];

    loadData();

    while (1){
        printf("\nBlood Group Management System\n");
        printf("1. Add Member\n");
        printf("2. Delete Member\n");
        printf("3. View Members\n");
        printf("4. Search Blood\n");
        printf("5. Save Data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            printf("Enter Name: ");
            scanf("%s", member.name);
            printf("Enter Blood Group: ");
            scanf("%s", member.bloodGroup);
            printf("Enter Age: ");
            scanf("%d", &member.age);
            addMember(member);
            break;
        case 2:
            printf("Enter Name to delete: ");
            scanf("%s", name);
            deleteMember(name);
            break;
        case 3:
            viewMembers();
            break;
        case 4:
            printf("Enter Blood Group to search: ");
            scanf("%s", bloodGroup);
            searchMembers(bloodGroup);
            break;
        case 5:
            saveData();
            break;
        case 6:
            printf("Exiting...\n");
            saveData();
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}