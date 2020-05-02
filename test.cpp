#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

//模拟火车站购票,双线程
HANDLE hMutex = NULL; //全局mutex变量	
DWORD WINAPI pthreadId1;
DWORD WINAPI pthreadId2;

//定义票数;
static int tickets = 100;

//线程回调函数;
DWORD WINAPI FUN(LPVOID lp)
{
	while (1)
	{
		WaitForSingleObject(hMutex,INFINITE);
		if (tickets <= 0)
		{
			break;
		}
		else
		{
			cout << "线程1：tickets self:" << tickets-- << "\n";
			Sleep(100);
		}
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI fun(LPVOID lp)
{
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets <= 0)
		{
			break;
		}
		else
		{
			cout << "线程2：tickets self:" << tickets-- << "\n";
			Sleep(100);
		}
		ReleaseMutex(hMutex);
	}

	return 0;
}


int main()
{
	HANDLE pthread1 = CreateThread(NULL, 0, FUN, NULL, 0, &pthreadId1);
	HANDLE pthread2 = CreateThread(NULL,0,fun,NULL,0,&pthreadId2);
	CloseHandle(pthread1); //关闭线程句柄，释放资源
	CloseHandle(pthread2);

	cout << pthreadId1 << endl;
	cout << pthreadId2 << endl;

	/*while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		cout << "tickets self:" << tickets - (tickets--) << endl;
		Sleep(1000);
		ReleaseMutex(hMutex);
	}*/
		
	system("pause");
	return 0;
}