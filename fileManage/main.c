#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_FILENAME 256
#define MAX_LENGTH_CONTENT 1024

struct Node;
typedef struct Node Node;
char input[1024];

Node* root = NULL;
Node* current = NULL;

Node* findNode (Node* parent, const char* name);

typedef enum
{
    DIRECTORY = 0,
    FILES = 1
} NodeType;

typedef struct Node
{
    char name [MAX_LENGTH_FILENAME];
    NodeType type;   
    struct Node *parent;
    struct Node *children;
    struct Node *sibling;
    char content [MAX_LENGTH_CONTENT];
} Node;

Node* createDirectory (char *inputName) // 创建文件夹或目录
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    strcpy (newNode -> name, inputName);
    newNode -> type = DIRECTORY;
    newNode -> parent = NULL;
    newNode -> children = NULL;
    newNode -> sibling = NULL;
    
    return newNode;
}

Node* createFile (char *inputName, char *inputContent) // 创建文件
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    strcpy (newNode -> name, inputName);
    newNode -> type = FILES;
    newNode -> parent = NULL;
    newNode -> children = NULL;
    newNode -> sibling = NULL;
    
    if (inputContent != NULL)
    {
        strcpy (newNode -> content, inputContent);
    }
    
    else
    {
        newNode->content[0] = '\0';
    }

    return newNode;
}

Node* addChild (char *inputName, char *inputContent, NodeType type, const char *nameParent) 
{
    Node* parent = findNode (root, nameParent); 
    if (parent == NULL) 
    {
        printf("找不到'%s'节点\n", nameParent);
        return NULL; 
    }

    Node* newNode = (type == FILES) ? createFile(inputName, inputContent) : createDirectory(inputName);
    newNode -> parent = parent;

    if (parent -> children == NULL) 
    {
        parent -> children = newNode;
    } 
    else 
    {
        Node* current = parent -> children;
        while (current -> sibling) 
        {
            current = current -> sibling;
        }
        current -> sibling = newNode;
    }

    return newNode;
}

Node* findNode (Node* parent, const char* name)
{
    if (parent == NULL) 
    {
        printf ("你马没啦！\n");
        return NULL; 
    }

    if (strcmp(parent->name, name) == 0) 
    {
        return parent; 
    }

    
    Node* child = parent->children;
    while (child) 
    {
        Node* result = findNode(child, name); 
        if (result != NULL) 
        {
            return result; 
        }
        child = child->sibling; 
    }

    return NULL; 
}

void catVanila (char *inputCat)
{
    Node* cat = NULL;
    if (cat = findNode (current, inputCat))
    {
        if ((strcmp (inputCat, cat -> name) == 0) && (cat -> type == FILES))
        {
            if (strlen (cat -> content) > 0)
            {
                printf ("\n%s文件的文本：\n%s\n", cat -> name, cat -> content);
            }
            
            else
            {
                printf ("'%s'文件无内容\n", inputCat);
            }
        }
        
        else
        {
            printf ("找不到'%s'文件\n", inputCat);
        }
    }
    
    else
    {
        printf ("找不到'%s'文件\n", inputCat);
    }

}

void writeVanila (char *inputWrite)
{
    Node* write = NULL;
    char text[MAX_LENGTH_CONTENT];

    if (write = findNode (current, inputWrite))
    {
        if ((strcmp (inputWrite, write -> name) == 0) && (write -> type == FILES))
        {
            printf ("请输入文本：\n");
            scanf ("%s", text);

            strcpy (write -> content, text);
        }
        
        else
        {
            printf ("找不到'%s'文件\n", inputWrite);
        }
    }

    else
    {
        printf ("找不到'%s'文件\n", inputWrite);
    }

}

void lsVanila (Node* currentNode, int depth) // 打印该目录下的结构
{
    for (int i = 0; i < depth; i++) 
    {
        printf ("|-- ");
    }
    
    printf ("%s\n", currentNode -> name);
    Node* child = currentNode -> children;
    
    while (child) 
    {
        lsVanila (child, depth + 1);
        child = child -> sibling;
    }
}

void lsChoco () // 打印树结构
{
    lsVanila (root, 0);
}

void cdVanila(char *inputCd) // 切换目录
{
     if (strcmp(inputCd, "..") == 0) 
    {
        if (current->parent != NULL) 
        {
            current = current->parent; 
            printf("当前目录：%s\n", current->name);
        } 
        else 
        {
            printf("已经在根目录，无法返回上一级\n");
        }
        return;
    }

    Node* child = current->children; 

    while (child) 
    {
        if (strcmp(child->name, inputCd) == 0 && child->type == DIRECTORY) 
        {
            current = child; 
            printf("当前目录：%s\n", current->name);
            return;
        }
        child = child->sibling;
    }

    printf("无法找到目标目录 '%s'\n", inputCd);
}

void readCommand () // 读取指令
{
    char command[MAX_LENGTH_FILENAME];
    char argument[MAX_LENGTH_FILENAME];

    sscanf(input, "%s %s", command, argument);

    if ((strcmp (command, "cd") == 0) && (strcmp (argument, "..") == 0))
    {
        cdVanila (argument);
    }
    
    else if (strcmp (command, "cd") == 0) 
    {
        cdVanila (argument); 
    } 
    
    else if (strcmp (command, "ls") == 0) 
    {
        printf ("\n");
        lsVanila (current, 0);
        printf ("\n");
    } 
    
    else if (strcmp (command, "lschoco") == 0) 
    {
        printf ("\n");
        lsChoco (); 
        printf ("\n");
    } 
    
    else if (strcmp (command, "mkdir") == 0)
    {
        addChild (argument, NULL, DIRECTORY, current -> name);
    } 
    
    else if (strcmp (command, "touch") == 0)
    {
        addChild (argument, NULL, FILES, current -> name);
    }
    
    else if (strcmp (command, "cat") == 0)
    {
        catVanila (argument);
    }
    
    else if (strcmp (command, "write") == 0)
    {
        writeVanila (argument);
    }
    
    else 
    {
        printf("未知命令：%s\n", command);
    }
}

int main () 
{
    root = createDirectory("root");
    current = root; 

    addChild("folder1", NULL, DIRECTORY, "root");
    addChild("gan", "i am kedo egg lover <3", FILES, "folder1");
    addChild("folder2", NULL, DIRECTORY, "root");

    while (1) 
    {
        printf("%s > ", current->name);
        fgets(input, sizeof(input), stdin); 
        input[strcspn(input, "\n")] = 0; 
        readCommand(); 
    }

    return 0;
}
