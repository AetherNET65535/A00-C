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

// 内存条，第一个内存块，启动了没！？O神启动！！
static unsigned char memeowry_chip [MEMEOWRY_SIZE];
static memeowry_block_header* first_block = NULL;
static int is_started = 0;

void start_first_block ()
{
    first_block = (memeowry_block_header*) memeowry_chip
}

int main ()
{

}