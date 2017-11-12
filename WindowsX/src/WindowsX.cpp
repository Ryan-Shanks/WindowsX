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

void drawNotch(int x, int y){

}

int main() {
	EnumWindows(callBackProc, 0);
	Sleep(1000);
	char title[1000];
	cout << "n windows: " << windows.size() << endl;
	for (unsigned i = 0; i < windows.size(); i++){
		GetWindowText(windows[i], title, 1000);
		DWORD dwStyle = (DWORD)GetWindowLong(windows[i], GWL_STYLE);
		RECT r;
		if (IsWindowVisible(windows[i]) && strcmp("", title) != 0){
			HWND parent = GetParent(windows[i]);
			GetWindowRect(windows[i], &r);
			if (r.bottom - r.top > 100 && r.right - r.left > 200){
				cout << title << " parent: " << parent << " dwStyle: " << dwStyle << "(" << r.left << ", "
						<< r.top << ", " << r.right << ", " << r.bottom << ")" << endl;
			}
		}
	}
}


