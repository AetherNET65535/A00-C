#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_CUSTOMERS 50
#define NUM_COUNTERS 3
#define MAX_QUEUE_SIZE 20

// 客户类型
typedef struct 
{
    int id;
    int is_vip;
    int service_time;  // 需要服务的时间（秒）
} Customer;

// 队列结构
typedef struct
 {
    Customer* customers[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// 全局变量
Queue* customer_queue;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t queue_not_full = PTHREAD_COND_INITIALIZER;
int bank_is_open = 1;

// 队列操作函数
Queue* create_queue() 
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

int is_queue_empty(Queue* q) 
{
    return q->size == 0;
}

int is_queue_full(Queue* q) 
{
    return q->size == MAX_QUEUE_SIZE;
}

// 入队（考虑VIP优先）
void enqueue(Queue* q, Customer* customer) 
{
    if (is_queue_full(q)) return;

    int pos;
    if (customer->is_vip) 
    {
        // VIP客户从队首开始找位置
        pos = q->front;
        for (int i = 0; i < q->size; i++) 
        {
            int idx = (q->front + i) % MAX_QUEUE_SIZE;
            if (!q->customers[idx]->is_vip) 
            {
                pos = idx;
                break;
            }
        }
        // 移动非VIP客户
        for (int i = q->size; i > (pos - q->front); i--) 
        {
            int idx = (q->front + i) % MAX_QUEUE_SIZE;
            int prev_idx = (q->front + i - 1) % MAX_QUEUE_SIZE;
            q->customers[idx] = q->customers[prev_idx];
        }
    } 
    else 
    {
        // 普通客户直接排队尾
        pos = (q->rear + 1) % MAX_QUEUE_SIZE;
    }
    
    q->customers[pos] = customer;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->size++;
}

// 出队
Customer* dequeue(Queue* q) 
{
    if (is_queue_empty(q)) return NULL;
    
    Customer* customer = q->customers[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return customer;
}

// 柜台线程函数
void* counter_thread(void* arg) 
{
    int counter_id = *(int*)arg;
    
    while (1) 
    {
        pthread_mutex_lock(&queue_mutex);
        
        // 等待队列非空
        while (is_queue_empty(customer_queue) && bank_is_open) 
        {
            pthread_cond_wait(&queue_not_empty, &queue_mutex);
        }
        
        // 银行关门且队列为空时，线程退出
        if (!bank_is_open && is_queue_empty(customer_queue)) 
        {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }
        
        // 处理客户
        Customer* customer = dequeue(customer_queue);
        pthread_cond_signal(&queue_not_full);
        pthread_mutex_unlock(&queue_mutex);
        
        if (customer) 
        {
            printf("柜台 %d 开始服务%s客户 %d, 预计服务时间: %d秒\n", 
                   counter_id, 
                   customer->is_vip ? "VIP" : "",
                   customer->id, 
                   customer->service_time);
            
            sleep(customer->service_time);  // 模拟服务时间
            
            printf("柜台 %d 完成服务客户 %d\n", counter_id, customer->id);
            free(customer);
        }
    }
    
    printf("柜台 %d 下班了\n", counter_id);
    return NULL;
}

// 生成客户线程函数
void* customer_generator(void* arg) 
{
    int customer_id = 0;
    
    while (bank_is_open) 
    {
        // 创建新客户
        Customer* customer = (Customer*)malloc(sizeof(Customer));
        customer->id = ++customer_id;
        customer->is_vip = rand() % 5 == 0;  // 20%概率是VIP
        customer->service_time = rand() % 5 + 1;  // 1-5秒服务时间
        
        pthread_mutex_lock(&queue_mutex);
        
        // 等待队列有空位
        while (is_queue_full(customer_queue) && bank_is_open) 
        {
            pthread_cond_wait(&queue_not_full, &queue_mutex);
        }
        
        // 银行关门时退出
        if (!bank_is_open) 
        {
            pthread_mutex_unlock(&queue_mutex);
            free(customer);
            break;
        }
        
        // 将客户加入队列
        enqueue(customer_queue, customer);
        printf("新%s客户 %d 进入队列, 需要服务时间: %d秒\n",
               customer->is_vip ? "VIP" : "",
               customer->id,
               customer->service_time);
        
        pthread_cond_signal(&queue_not_empty);
        pthread_mutex_unlock(&queue_mutex);
        
        sleep(rand() % 3 + 1);  // 1-3秒生成一个客户
    }
    
    printf("银行停止接待新客户\n");
    return NULL;
}

int main() 
{
    srand(time(NULL));
    
    // 初始化队列
    customer_queue = create_queue();
    
    // 创建柜台线程
    pthread_t counter_threads[NUM_COUNTERS];
    int counter_ids[NUM_COUNTERS];
    
    for (int i = 0; i < NUM_COUNTERS; i++) 
    {
        counter_ids[i] = i + 1;
        pthread_create(&counter_threads[i], NULL, counter_thread, &counter_ids[i]);
    }
    
    // 创建客户生成线程
    pthread_t generator_thread;
    pthread_create(&generator_thread, NULL, customer_generator, NULL);
    
    // 模拟银行营业时间（30秒）
    printf("银行开门营业！\n");
    sleep(30);
    
    // 关闭银行
    pthread_mutex_lock(&queue_mutex);
    bank_is_open = 0;
    pthread_cond_broadcast(&queue_not_empty);
    pthread_cond_broadcast(&queue_not_full);
    pthread_mutex_unlock(&queue_mutex);
    
    // 等待所有线程结束
    pthread_join(generator_thread, NULL);
    for (int i = 0; i < NUM_COUNTERS; i++) {
        pthread_join(counter_threads[i], NULL);
    }
    
    // 清理资源
    free(customer_queue);
    pthread_mutex_destroy(&queue_mutex);
    pthread_cond_destroy(&queue_not_empty);
    pthread_cond_destroy(&queue_not_full);
    
    printf("银行关门了！\n");
    return 0;
}