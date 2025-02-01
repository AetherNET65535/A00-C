#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // 用于随机数生成
#include <unistd.h> // 用于 usleep 函数

#define MAX_LENGTH_FILENAME 256
#define MAX_LENGTH_CONTENT 1024

struct Node;
typedef struct Node Node;
char input[1024];

Node* root = NULL;
Node* current = NULL;

Node* findNode(Node* parent, const char* name);

typedef enum {
    DIRECTORY = 0,
    FILES = 1
} NodeType;

typedef struct Node {
    char name[MAX_LENGTH_FILENAME];
    NodeType type;
    struct Node* parent;
    struct Node* children;
    struct Node* sibling;
    char content[MAX_LENGTH_CONTENT];
} Node;

// ANSI 颜色代码
#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"

// 随机字符集合（模拟乱码）
const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_+-=[]{}|;:,.<>?/\\";

// 生成随机字符
char getRandomChar() {
    return charset[rand() % (sizeof(charset) - 1)];
}

// 播放动画
void playCoolAnimation() {
    srand(time(NULL)); // 初始化随机数种子
    int duration = 1; // 动画持续时间 * 100ms = 秒
    int width = 1920; // 终端宽度
    int height = 1080; // 终端高度

    for (int i = 0; i < duration; i++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // 随机选择颜色
                const char* colors[] = {COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};
                const char* color = colors[rand() % 7];

                // 打印随机字符
                printf("%s%c", color, getRandomChar());
            }
            printf("\n");
        }
        usleep(1); // 每帧间隔 ms
        printf("\033[H\033[J"); // 清屏
    }
    printf(COLOR_RESET); // 重置颜色
}

Node* createDirectory(char* inputName) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, inputName);
    newNode->type = DIRECTORY;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->sibling = NULL;
    return newNode;
}

Node* createFile(char* inputName, char* inputContent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, inputName);
    newNode->type = FILES;
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->sibling = NULL;
    strcpy(newNode->content, inputContent);
    return newNode;
}

Node* addChild(char* inputName, char* inputContent, NodeType type, const char* nameParent) {
    Node* parent = findNode(root, nameParent);
    if (parent == NULL) {
        printf("找不到'%s'节点\n", nameParent);
        return NULL;
    }

    Node* newNode = (type == FILES) ? createFile(inputName, inputContent) : createDirectory(inputName);
    newNode->parent = parent;

    if (parent->children == NULL) {
        parent->children = newNode;
    } else {
        Node* current = parent->children;
        while (current->sibling) {
            current = current->sibling;
        }
        current->sibling = newNode;
    }

    return newNode;
}

Node* findNode(Node* parent, const char* name) {
    if (parent == NULL) {
        return NULL;
    }

    if (strcmp(parent->name, name) == 0) {
        return parent;
    }

    Node* child = parent->children;
    while (child) {
        Node* result = findNode(child, name);
        if (result != NULL) {
            return result;
        }
        child = child->sibling;
    }

    return NULL;
}

void deleteNode(Node* node) {
    if (node == NULL) return;

    // 递归删除子节点
    Node* child = node->children;
    while (child) {
        Node* next = child->sibling;
        deleteNode(child);
        child = next;
    }

    // 从父节点中移除
    if (node->parent) {
        Node* parent = node->parent;
        if (parent->children == node) {
            parent->children = node->sibling;
        } else {
            Node* sibling = parent->children;
            while (sibling->sibling != node) {
                sibling = sibling->sibling;
            }
            sibling->sibling = node->sibling;
        }
    }

    free(node);
}

void lsVanila(Node* currentNode, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|-- ");
    }

    printf("%s\n", currentNode->name);
    Node* child = currentNode->children;

    while (child) {
        lsVanila(child, depth + 1);
        child = child->sibling;
    }
}

void lsChoco() {
    lsVanila(root, 0);
}

void cdVanila(char* inputCd) {
    if (strcmp(inputCd, "..") == 0) {
        if (current->parent != NULL) {
            current = current->parent;
            printf("当前目录：%s\n", current->name);
        } else {
            printf("已经在根目录，无法返回上一级\n");
        }
        return;
    }

    Node* child = current->children;

    while (child) {
        if (strcmp(child->name, inputCd) == 0 && child->type == DIRECTORY) {
            current = child;
            printf("当前目录：%s\n", current->name);
            return;
        }
        child = child->sibling;
    }

    printf("无法找到目标目录 '%s'\n", inputCd);
}

void readCommand() {
    char command[MAX_LENGTH_FILENAME];
    char argument1[MAX_LENGTH_FILENAME];
    char argument2[MAX_LENGTH_CONTENT];

    sscanf(input, "%s %s %[^\n]", command, argument1, argument2);

    if (strcmp(command, "cd") == 0) {
        cdVanila(argument1);
    } else if (strcmp(command, "ls") == 0) {
        printf("\n");
        lsVanila(current, 0);
        printf("\n");
    } else if (strcmp(command, "lschoco") == 0) {
        printf("\n");
        lsChoco();
        printf("\n");
    } else if (strcmp(command, "mkdir") == 0) {
        addChild(argument1, NULL, DIRECTORY, current->name);
    } else if (strcmp(command, "touch") == 0) {
        addChild(argument1, "", FILES, current->name);
    } else if (strcmp(command, "rm") == 0) {
        if (strcmp(argument1, "root") == 0) {
            printf("正在删除根目录...\n");
            playCoolAnimation(); // 播放动画
            deleteNode(root);
            root = createDirectory("root"); // 重新创建根目录
            current = root;
            printf("根目录已重置\n");
        } else {
            Node* node = findNode(current, argument1);
            if (node) {
                deleteNode(node);
                printf("已删除 '%s'\n", argument1);
            } else {
                printf("找不到 '%s'\n", argument1);
            }
        }
    } else if (strcmp(command, "cat") == 0) {
        Node* node = findNode(current, argument1);
        if (node && node->type == FILES) {
            printf("%s\n", node->content);
        } else {
            printf("无法读取文件 '%s'\n", argument1);
        }
    } else if (strcmp(command, "write") == 0) {
        Node* node = findNode(current, argument1);
        if (node && node->type == FILES) {
            strcpy(node->content, argument2);
            printf("已写入内容到 '%s'\n", argument1);
        } else {
            printf("无法写入文件 '%s'\n", argument1);
        }
    } else {
        printf("未知命令：%s\n", command);
    }
}

int main() {
    root = createDirectory("root");
    current = root;

    addChild("folder1", NULL, DIRECTORY, "root");
    addChild("file1.txt", "This is file1", FILES, "folder1");
    addChild("folder2", NULL, DIRECTORY, "root");

    while (1) {
        printf("%s > ", current->name);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        readCommand();
    }

    return 0;
}