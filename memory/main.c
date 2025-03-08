#include <stdio.h>
#include <stddef.h>
#include <string.h>

// MEMEOWRY == MEMORY, BUT CUTER~ MEOW~
// 内存条（块）总容量 和 最小容量
#define MEMEOWRY_SIZE 1024 * 1 //1024 * x = xKB
#define MEMEOWRY_MIN_SIZE sizeof(memeowry_block_header)

// 内存块使用状态
typedef enum
{
    USED = 0,
    FREE = 1
} Block_Status;

typedef struct memeowry_block_header
{
    size_t size;
    Block_Status status;
    struct memeowry_block_header *prev;
    struct memeowry_block_header *next;
} memeowry_block_header;

// 内存条，第一个内存块，初始化识别码
static unsigned char memeowry_chip [MEMEOWRY_SIZE];
static memeowry_block_header* first_block = NULL;
static int is_initialized = 0;

void init_first_block ()
{
    // BIOS自检初始化了没，简称“给自己防呆”
    if (is_initialized)
    {
        return;
    }

    // 把内存条插上主板
    first_block = (memeowry_block_header*)memeowry_chip;
    
    // BIOS开始初始化内存
    first_block -> size = MEMEOWRY_SIZE - sizeof(memeowry_block_header);
    first_block -> status = FREE;
    first_block -> prev = NULL;
    first_block -> next = NULL;

    is_initialized = 1;
}

int main ()
{
    printf("%d\n", is_initialized);

    init_first_block();
    printf("%d\n", is_initialized);
}