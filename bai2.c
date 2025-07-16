#include <stdio.h>
#include <string.h>

typedef struct Operation {
    char value;
} Operation;

typedef struct Stack {
    Operation data[100];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == 100;
}

void push(Stack* s, Operation data) {
    if (!isFull(s)) {
        s->data[++s->top] = data;
    }
}

Operation pop(Stack* s) {
    Operation nullOp = {'\0'};
    if (isEmpty(s)) return nullOp;
    return s->data[s->top--];
}

void insertChar(char* text, char c, Stack* undoStack) {
    int len = strlen(text);
    text[len] = c;
    text[len + 1] = '\0';

    Operation op = {c};
    push(undoStack, op);
}

void undo(char* text, Stack* undoStack, Stack* redoStack) {
    if (isEmpty(undoStack)) {
        printf("Không có ký tự\n");
        return;
    }

    Operation op = pop(undoStack);
    int len = strlen(text);
    if (len > 0) {
        text[len - 1] = '\0';
    }
    push(redoStack, op);
    printf("Đã UNDO thành công\n");
}

void redo(char* text, Stack* undoStack, Stack* redoStack) {
    if (isEmpty(redoStack)) {
        printf("Không có ký tự\n");
        return;
    }

    Operation op = pop(redoStack);
    int len = strlen(text);
    text[len] = op.value;
    text[len + 1] = '\0';
    push(undoStack, op);
    printf("Đã REDO thành công\n");
}

void displayText(char* text) {
    printf("Text hiện tại: %s\n", text);
}

int main() {
    int choice;
    Stack undoStack, redoStack;
    char text[1000] = "";
    initStack(&undoStack);
    initStack(&redoStack);

    do {
        printf("1. INSERT X\n");
        printf("2. UNDO\n");
        printf("3. REDO\n");
        printf("4. HIỂN THỊ\n");
        printf("5. THOÁT\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                char c;
                printf("Nhập ký tự muốn thêm: ");
                scanf("%c", &c);
                getchar();
                insertChar(text, c, &undoStack);
                initStack(&redoStack);
                break;
            }
            case 2:
                undo(text, &undoStack, &redoStack);
                break;
            case 3:
                redo(text, &undoStack, &redoStack);
                break;
            case 4:
                displayText(text);
                break;
            case 5:
                printf("Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
                break;
        }
    } while (choice != 5);
}
