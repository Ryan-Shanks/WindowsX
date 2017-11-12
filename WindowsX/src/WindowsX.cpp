//============================================================================
// Name        : WindowsX.cpp
// Author      : Ryan Shanks
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>
using namespace std;
vector<HWND> windows;
vector<HWND> notches;

BOOL CALLBACK callBackProc(HWND hwnd, LPARAM lp) {
	windows.push_back(hwnd);
	return true;
}

void drawNotch(HWND hwnd) {
	RECT r;
	GetWindowRect (hwnd, &r);
	Gdiplus::Rect rect((r.right + r.left)/2 - 87, r.top, 175, 25);
	Gdiplus::Graphics grpx(GetDC(HWND_DESKTOP));
	Gdiplus::Image* image = new Gdiplus::Image(L"notch.png");
	grpx.DrawImage(image, rect);
}



int main() {
	EnumWindows(callBackProc, 0);
	// start GDI
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	char title[1000];
	cout << "n windows: " << windows.size() << endl;
	for (unsigned i = 0; i < windows.size(); i++) {
		GetWindowText(windows[i], title, 1000);
		DWORD dwStyle = (DWORD) GetWindowLong(windows[i], GWL_STYLE);
		RECT r;
		if (IsWindowVisible(windows[i]) && strcmp("", title) != 0) {
			HWND parent = GetParent(windows[i]);
			GetWindowRect(windows[i], &r);
			if (r.bottom - r.top > 100 && r.right - r.left > 200) {
				cout << title << " parent: " << parent << " dwStyle: " << dwStyle << "(" << r.left << ", " << r.top
						<< ", " << r.right << ", " << r.bottom << ")" << endl;
				drawNotch(windows[i]);
			}
		}
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

