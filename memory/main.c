#include <stdio.h>
#include <stddef.h>
#include <string.h>

// 内存条（块）总容量 和 最小容量
#define MEMORY_SIZE 1024 * 1 // 1024 * x = xKiB
#define BLOCK_MIN_SIZE sizeof(memory_block_header) + 4 // 下一块内存块最低大小

// 内存块使用状态
typedef enum
{
    USED = 0,
    FREE = 1
} Block_Status;

typedef struct memory_block_header
{
    size_t size;
    Block_Status status;
    struct memory_block_header *prev;
    struct memory_block_header *next;
} memory_block_header;

// 内存条，第一个内存块，初始化识别码
static unsigned char memory_chip [MEMORY_SIZE];
static memory_block_header* first_block = NULL;
static int is_initialized = 0;

void init_first_block ()
{
    // BIOS自检初始化了没，简称“给自己防呆”
    if (is_initialized)
    {
        return;
    }

    // 把内存条插上主板
    first_block = (memory_block_header*)memory_chip;
    
    // BIOS开始初始化内存
    first_block -> size = MEMORY_SIZE - sizeof(memory_block_header);
    first_block -> status = FREE;
    first_block -> prev = NULL;
    first_block -> next = NULL;

    is_initialized = 1;
}

void* my_malloc (size_t size)
{
    memory_block_header* current;
    memory_block_header* new_block;

    // 又一个防呆，这是让忘记初始化的人用的
    if (!is_initialized)
    {
        init_first_block();
    }

    // 对齐4字节
    size = (size + 3) & (~3);
    printf("即将创建容量为%d的内存块...\n", size);

    // 防止无用块的创建
    if (size == 0)
    {
        printf("不能创建容量为0的内存块！！\n");
        return 0;
    }

    current = first_block;

    while(current)
    {
        printf ("正在寻找合适的内存块...\n");

        // 寻找合适的内存块
        if (current -> status == FREE && current -> size >= size)
        {
            printf ("找到合适的内存块\n");

            // 如果内存够用了，看看能不能分一下
            if (current -> size >= size + BLOCK_MIN_SIZE)
            {   
                printf ("可分块，正在创建新块...\n");

                // 计算新块的地址
                new_block = (memory_block_header*)((unsigned char*)current + sizeof(memory_block_header) + size);
                
                // 设置新块属性
                new_block -> size = current -> size - sizeof(memory_block_header) - size;
                new_block -> status = FREE;
                new_block -> prev = current;
                new_block -> next = current -> next;

                printf ("新块设置完成\n");

                // 设置当前块属性
                current -> size = size;
                current -> next = new_block;

                // 如果之后还有一个内存块，连一连～
                if (new_block -> next)
                {
                    new_block -> next -> prev = new_block;
                }

            }
            current -> status = USED;
            printf ("用户块设置完成：\n数据容量：%zu\n", current -> size);
        }
        // 返回数据部门指针（跳过头部）
        return (void*)((unsigned char*)current + sizeof(memory_block_header));
    }
    current = current -> next;
}

void my_free (void* ptr)
{
    memory_block_header* now_block;
    memory_block_header* after_block;

    // 检测野指针
    if (ptr == NULL)
    {
        printf ("FREE函数检测到野指针\n");
        return;
    }

    // 夺回头部控制权
    now_block = (memory_block_header*)((unsigned char*)ptr - sizeof(memory_block_header));
    printf ("已夺回头部控制权\n");

    // 检测用户有没有发错地址，又一个防呆呀～
    if ((unsigned char*)now_block < memory_chip || (unsigned char*)now_block >= memory_chip + MEMORY_SIZE)
    {
        printf ("发错地址啦！\n");
        return;
    }

    // 先FREE一下，不然等下旁边没有FREE就完蛋蛋了
    now_block -> status = FREE;

    // 向前合并
    after_block = now_block;

    while (after_block -> next != NULL)
    {
        after_block = after_block -> next;

        if (after_block -> status = FREE)
        {
            now_block -> size += after_block -> size + sizeof(memory_block_header);
            now_block -> next = after_block -> next;
            printf ("合并成功！\n");
        }
        else
        {
            break;
        }
    }

    // 向后合并
    after_block = now_block;

    while (after_block -> prev != NULL)
    {
        after_block = after_block -> prev;

        if (after_block -> status = FREE)
        {
            now_block -> size += after_block -> size + sizeof(memory_block_header);
            now_block -> prev = after_block -> prev;
        }
        else
        {
            break;
        }
    }
    printf("done\n");
}

int main ()
{
    init_first_block();
    void* p = my_malloc(200);
    my_free(p);

}