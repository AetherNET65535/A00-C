#include <stdio.h>
#include <stdlib.h>

#define POOL_SIZE 1024  // 定义内存池大小

// 定义内存块结构
typedef struct Block {
    size_t size;  // 当前内存块的大小
    struct Block *next;  // 指向下一个内存块
    int free;  // 标记内存块是否空闲
} Block;

static char memory_pool[POOL_SIZE];  // 定义内存池
static Block *free_list = NULL;  // 空闲块链表

// 初始化内存池
void init_pool() {
    free_list = (Block *)memory_pool;  // 初始化第一个块
    free_list->size = POOL_SIZE - sizeof(Block);  // 设置块大小
    free_list->next = NULL;  // 没有下一个块
    free_list->free = 1;  // 设置为空闲状态
    printf("Memory pool initialized with size %d bytes.\n", POOL_SIZE);
}

// 自定义内存分配函数
void *my_malloc(size_t size) {
    Block *current = free_list;

    // 遍历空闲链表寻找合适的块
    while (current) {
        if (current->free && current->size >= size) {  // 找到合适的块
            current->free = 0;  // 标记为已分配
            if (current->size > size + sizeof(Block)) {  // 如果块太大，分割
                Block *new_block = (Block *)((char *)current + size + sizeof(Block));
                new_block->size = current->size - size - sizeof(Block);
                new_block->free = 1;
                new_block->next = current->next;
                current->next = new_block;
                current->size = size;
            }
            printf("Allocated %zu bytes.\n", size);
            return (char *)current + sizeof(Block);  // 返回内存块的实际内存地址
        }
        current = current->next;
    }
    printf("Failed to allocate %zu bytes.\n", size);
    return NULL;  // 没有合适的块时返回NULL
}

// 自定义内存释放函数
void my_free(void *ptr) {
    if (!ptr) return;

    Block *block = (Block *)((char *)ptr - sizeof(Block));  // 找到块头部
    block->free = 1;  // 标记为空闲
    printf("Freed %zu bytes.\n", block->size);

    // 合并相邻的空闲块
    Block *current = free_list;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

int main() {
    init_pool();  // 初始化内存池

    // 测试内存分配和释放
    void *ptr1 = my_malloc(100);  // 分配100字节
    void *ptr2 = my_malloc(200);  // 分配200字节

    my_free(ptr1);  // 释放第一个内存块
    my_free(ptr2);  // 释放第二个内存块

    return 0;
}
