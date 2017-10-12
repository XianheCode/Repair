#pragma once
#include <Windows.h> 

class Mutex
{
public:
	Mutex()                      { InitializeCriticalSection(&section); }
	~Mutex()                     { DeleteCriticalSection(&section); }
	void  Enter()                { EnterCriticalSection(&section); }
	void  Leave()                { LeaveCriticalSection(&section); }

	struct Lock;
protected:
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);

	CRITICAL_SECTION section;
};

struct Mutex::Lock {
	Mutex& s;
	Lock(Mutex& s) : s(s) { s.Enter(); }
	~Lock()               { s.Leave(); }
};

