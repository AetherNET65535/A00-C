#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <windows.h>
#include <stdio.h>

DWORD WINAPI myThreadFunction(LPVOID lpParam) {
    int* pInt = (int*)lpParam;
    printf("线程 %d 正在运行\n", *pInt);
    return 0;
}

int main() {
    HANDLE thread1, thread2;
    int arg1 = 1, arg2 = 2;

    // 创建线程
    thread1 = CreateThread(NULL, 0, myThreadFunction, &arg1, 0, NULL);
    thread2 = CreateThread(NULL, 0, myThreadFunction, &arg2, 0, NULL);

    // 等待线程完成
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // 关闭线程句柄
    CloseHandle(thread1);
    CloseHandle(thread2);

    printf("主线程结束\n");
    return 0;
}



