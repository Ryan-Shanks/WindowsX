//============================================================================
// Name        : WindowsX.cpp
// Author      : Ryan Shanks
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
vector<HWND> windows;

BOOL CALLBACK callBackProc(HWND hwnd, LPARAM lp){
	windows.push_back(hwnd);
	return true;
}

int main() {
	EnumWindows(callBackProc, 0);
	Sleep(1000);
	char title[1000];
	cout << "n windows: " << windows.size() << endl;
	for (unsigned i = 0; i < windows.size(); i++){
		GetWindowText(windows[i], title, 1000);
		DWORD dwStyle = (DWORD)GetWindowLong(windows[i], GWL_STYLE);
		DWORD dwExStyle = (DWORD)GetWindowLong(windows[i], GWL_EXSTYLE);
		if (IsWindowVisible(windows[i]) && strcmp("", title) != 0){
			HWND parent = GetParent(windows[i]);
			cout << title << " parent: " << parent << endl;
		}
	}
}


