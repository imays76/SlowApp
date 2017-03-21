// SlowApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

volatile bool g_stopNow = false;

void SlowWork1();
void SlowWork2();
void SlowWork3();
void SlowSubwork1();
void SlowSubwork2();
void SlowSubwork3();

map<int, int> map1;
map<int, int> map2;
map<int, int> map3;

int g_num = 0;

void thread1()
{
	while (!g_stopNow)
	{
		SlowWork1();
	}
}

void thread2()
{
	while (!g_stopNow)
	{
		SlowWork2();
	}
}

void thread3()
{
	while (!g_stopNow)
	{
		SlowWork3();
	}
}

void SlowWork1()
{
	SlowWork2();
	SlowSubwork1();
}

void SlowWork2()
{
	SlowSubwork1();
	SlowSubwork3();
	SlowSubwork3();
}

void SlowWork3()
{
	SlowSubwork1();
	SlowSubwork3();
}

void WasteMemory(map<int,int>& map)
{
	map[g_num] = g_num;
	g_num++;
}

void SlowSubwork1()
{
	for (int i = 0; i < 1000; i++)
	{
		rand();
		WasteMemory(map1);
	}	
}

void SlowSubwork2()
{
	for (int i = 0; i < 2000; i++)
	{
		rand();
		WasteMemory(map2);
	}
}

void SlowSubwork3()
{
	for (int i = 0; i < 3000; i++)
	{
		rand();
		WasteMemory(map3);
	}
}


int main()
{
	thread t1([]() { thread1(); });
	thread t2([]() { thread2(); });
	thread t3([]() { thread3(); });

	cout << "Press Enter to exit.\n";

	string s;
	std::getline(cin, s);

	g_stopNow = true;

	t1.join();
	t2.join();
	t3.join();

    return 0;
}

