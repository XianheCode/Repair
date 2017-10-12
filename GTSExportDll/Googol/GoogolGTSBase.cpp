//#include "stdafx.h"
#include "GoogolGTSBase.h"

#include <iostream>
#include <windows.h>
#include <conio.h>

CGoogolGTSBase::CGoogolGTSBase()
{
}

CGoogolGTSBase::~CGoogolGTSBase()
{
	GT_Close();
}