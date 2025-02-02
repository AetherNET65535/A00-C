#include <stdio.h>

#define MAX_SIZE 5 // 队列的最大容量

typedef struct 
{
    int data[MAX_SIZE]; // 队列的存储空间
    int front;           // 队列头指针
    int rear;            // 队列尾指针
} Queue;


void initQueue(Queue *q) 
{
    q->front = -1;
    q->rear = -1;
}

int enqueue(Queue *q, int value) 
{
    if (q->rear == MAX_SIZE - 1) 
    {
        printf("Queue is full!\n");
        return -1; // 队列已满
    }
    if (q->front == -1) 
    {
        q->front = 0; // 如果是第一次入队，设置front为0
    }
    q->rear++;
    q->data[q->rear] = value;
    return 0; // 入队成功
}

int dequeue(Queue *q) 
{
    if (q->front == -1) 
    {
        printf("Queue is empty!\n");
        return -1; // 队列为空
    }
    int dequeued_value = q->data[q->front];
    // 如果队列只有一个元素，出队后清空队列
    if (q->front == q->rear) 
    {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return dequeued_value; // 返回出队的值
}

void displayQueue(Queue *q) 
{
    if (q->front == -1) 
    {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) 
    {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() 
{
    Queue q;
    initQueue(&q);

    // 模拟任务加入队列
    enqueue(&q, 10); // 任务10进入队列
    enqueue(&q, 20); // 任务20进入队列
    enqueue(&q, 30); // 任务30进入队列
    displayQueue(&q); // 显示队列状态

    // 模拟处理任务（FIFO）
    printf("Processing task: %d\n", dequeue(&q)); // 处理任务10
    printf("Processing task: %d\n", dequeue(&q)); // 处理任务20
    displayQueue(&q); // 显示剩余队列状态

    return 0;
}
