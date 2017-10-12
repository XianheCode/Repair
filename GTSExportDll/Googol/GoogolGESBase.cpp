//#include "stdafx.h"
#include "GoogolGESBase.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

CGoogolGESBase::CGoogolGESBase()
{
}

CGoogolGESBase::~CGoogolGESBase()
{
	GT_Close();
}