//
// Created by SonwDao on 16/7/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    int priority;
    char deadline[100];
}Task;

typedef struct SNode{
    Task tasks;
    struct SNode* next;
}SNode;

typedef struct DNode{
    Task tasks;
    struct DNode* next;
    struct DNode* prev;
}DNode;

SNode* Shead = NULL;
DNode* Dhead = NULL;

SNode* createNode(Task task) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    newNode->tasks = task;
    newNode->next = NULL;
    return newNode;
}

void addMission(Task task) {
    SNode* newNode = createNode(task);
    if (Shead == NULL) {
        Shead = newNode;
        return;
    }
    SNode* temp = Shead;
    while (temp->next != NULL ) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Thêm nhiệm vụ thành công!\n");
}

void displayMission() {
    SNode* temp = Shead;
    if (Shead == NULL) {
        printf("Chưa có nhiệm vụ nào!\n");
        return;
    }
    printf("Danh Sách Nhiệm Vụ : \n");
    while (temp != NULL) {
        printf("---------------------------\n");
        printf("ID : %d\n",temp->tasks.id);
        printf("Title : %s\n",temp->tasks.title);
        printf("Priority : %d\n",temp->tasks.priority);
        printf("Deadline : %s\n",temp->tasks.deadline);
        printf("---------------------------\n");
        temp = temp->next;
    }
}

SNode* deleteBook(int id) {
    SNode* temp = Shead;
    SNode* prev = NULL;
    if (temp == NULL) {
        printf("Danh sách nhiệm vụ trống!\n");
        return Shead;
    }
    if (Shead->tasks.id == id) {
        SNode* deleteHead = Shead;
        Shead = Shead->next;
        free(deleteHead);
        printf("Đã xoá thành công!\n");
        return Shead;
    }
    while (temp != NULL && temp->tasks.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Không tìm thấy nhiệm vụ!\n");
        return Shead;
    }
    prev->next = temp->next;
    free(temp);
    printf("Đã xoá thành công!\n");
    return Shead;
}

void updateTask(int id) {
    SNode* temp = Shead;
    if (temp == NULL) {
        printf("Danh sách nhiệm vụ trống!\n");
        return;
    }
    while (temp != NULL && temp->tasks.id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Không tìm thấy nhiệm vụ!\n");
        return;
    }
    getchar();
    printf("Nhập tên nhiệm vụ : ");
    fgets(temp->tasks.title, 100, stdin);
    temp->tasks.title[strcspn(temp->tasks.title, "\n")] = '\0';
    do {
        printf("Nhập mức độ ưu tiên (1-5) : ");
        scanf("%d",&temp->tasks.priority);
        if (temp->tasks.priority > 5 || temp->tasks.priority < 1) {
            printf("Mức độ ưu tiên không phù hợp!Nhập lại\n");
        }
    } while (temp->tasks.priority > 5 || temp->tasks.priority < 1);
    getchar();
    printf("Nhập thời gian hoàn thành (DD-MM-YY) : ");
    fgets(temp->tasks.deadline, 100, stdin);
    temp->tasks.deadline[strcspn(temp->tasks.deadline, "\n")] = '\0';
    printf("Đã cập nhật thành công!\n");
}

DNode* createDNode(Task task) {
    DNode* newNode = malloc(sizeof(DNode));
    newNode->tasks = task;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void markAsComplete(int id) {
    if (Shead == NULL) {
        printf("Danh sách nhiệm vụ trống!\n");
        return;
    }
    SNode* temp = Shead;
    SNode* prev = NULL;
    while (temp != NULL && temp->tasks.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Không tìm thấy nhiệm vụ!\n");
        return;
    }
    Task tempTask = temp->tasks;
    if (prev == NULL) {
        Shead = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);

    DNode* newDNode = createDNode(tempTask);
    if (Dhead == NULL) {
        Dhead = newDNode;
    } else {
        DNode* dTemp = Dhead;
        while (dTemp->next != NULL) {
            dTemp = dTemp->next;
        }
        dTemp->next = newDNode;
        newDNode->prev = dTemp;
    }

    printf("Đã đánh dấu nhiệm vụ hoàn thành!\n");
}

void sort() {
    if (Shead == NULL || Shead->next == NULL) return;
    int swapped;
    SNode* ptr1;
    SNode* ptr2 = NULL;

    do {
        swapped = 0;
        ptr1 = Shead;

        while (ptr1->next != ptr2) {
            if (ptr1->tasks.priority > ptr1->next->tasks.priority) {
                Task tempTask = ptr1->tasks;
                ptr1->tasks = ptr1->next->tasks;
                ptr1->next->tasks = tempTask;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        ptr2 = ptr1;
    } while (swapped);
    printf("Đã sắp xếp nhiệm vụ theo mức độ ưu tiên\n");
}

void searchByTitle(char searchTitle[100]) {
    SNode* temp = Shead;
    int found = 0;

    if (Shead == NULL) {
        printf("Danh sách nhiệm vụ trống!\n");
        return;
    }
    printf("\n--- Nhiệm vụ cần tìm ---\n");
    while (temp != NULL) {
        if (strstr(temp->tasks.title, searchTitle) != NULL) {
            printf("---------------------------\n");
            printf("ID : %d\n",temp->tasks.id);
            printf("Title : %s\n",temp->tasks.title);
            printf("Priority : %d\n",temp->tasks.priority);
            printf("Deadline : %s\n",temp->tasks.deadline);
            printf("---------------------------\n");
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Không tìm thấy nhiệm vụ\n");
        return;
    }
}

int main() {
    int choice,searchValue;
    char searchTitle[100];
    do {
        Task newTask;
        printf("1. Thêm mới nhiệm vụ\n");
        printf("2. Hiển thị nhiệm vụ\n");
        printf("3. Xoá nhiệm vụ\n");
        printf("4. Cập nhật nhiệm vụ\n");
        printf("5. Đánh dấu nhiệm vụ hoàn thành\n");
        printf("6. Sắp xếp nhiệm vụ\n");
        printf("7. Tìm kiếm nhiệm vụ\n");
        printf("8. Thoát\n");
        printf("Lựa chọn của bạn : ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("Nhập id : ");
                scanf("%d",&newTask.id);
                getchar();
                printf("Nhập tên nhiệm vụ : ");
                fgets(newTask.title, 100, stdin);
                newTask.title[strcspn(newTask.title, "\n")] = '\0';
                do {
                    printf("Nhập mức độ ưu tiên (1-5) : ");
                    scanf("%d",&newTask.priority);
                    if (newTask.priority > 5 || newTask.priority < 1) {
                        printf("Mức độ ưu tiên không phù hợp!Nhập lại\n");
                    }
                } while (newTask.priority > 5 || newTask.priority < 1);

                printf("Nhập thời gian hoàn thành (DD-MM-YY) : ");
                getchar();
                fgets(newTask.deadline, 100, stdin);
                newTask.deadline[strcspn(newTask.deadline, "\n")] = '\0';
                addMission(newTask);
                break;
            case 2:
                displayMission();
                break;
            case 3:
                printf("Nhập id muốn xoá : ");
                scanf("%d",&searchValue);
                Shead = deleteBook(searchValue);
                break;
            case 4:
                printf("Nhập id muốn cập nhật : ");
                scanf("%d",&searchValue);
                updateTask(searchValue);
                break;
            case 5:
                printf("Nhập id muốn đánh dấu : ");
                scanf("%d",&searchValue);
                markAsComplete(searchValue);
                break;
            case 6:
                sort();
                break;
            case 7:
                getchar();
                printf("Nhập tên nhiệm vụ muốn tìm : ");
                fgets(searchTitle, 100, stdin);
                searchTitle[strcspn(searchTitle, "\n")] = '\0';
                searchByTitle(searchTitle);
                break;
            case 8:
                printf("Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
                break;
        }
    } while (choice != 8);
}