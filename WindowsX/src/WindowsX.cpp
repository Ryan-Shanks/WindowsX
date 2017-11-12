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
vector<string> windowTitles;
Gdiplus::Image *image;
ULONG_PTR gdiplusToken;
Gdiplus::Graphics *grpx;
int count = 0;
int numDrawn = 0;

BOOL CALLBACK callBackProc(HWND hwnd, LPARAM lp) {
	windows.push_back(hwnd);
	return true;
}

void drawNotch(HWND hwnd) {
	RECT r;
	GetWindowRect (hwnd, &r);
	if (r.top < 0){
		r.bottom -= r.top;
		r.top = 0;
	}
	if (r.right - r.left > 200 && r.bottom - r.top > 100){
		Gdiplus::Rect rect((r.right + r.left)/2 - 100, r.top, 200, 28);
		POINT tl, tr;
		tl.x = rect.X;
		tl.y = rect.Y;
		tr.x = rect.X + rect.Width;
		tr.y = rect.Y;
		if (WindowFromPoint(tl) == hwnd && WindowFromPoint(tr) == hwnd){
			grpx->DrawImage(image, rect);
			numDrawn ++;
		}
	}
	// if we have not drawn any we will draw one on the desktop so user can experiece the courage
	if (hwnd == HWND_DESKTOP){
		int width = GetSystemMetrics(SM_CXSCREEN);
		Gdiplus::Rect rect(width/2 - 100, 0, 200, 28);
		grpx->DrawImage(image, rect);
	}
}

void drawNotches(){
	numDrawn = 0;
	if (count >= 100){
		RedrawWindow(HWND_DESKTOP, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
		count = 0;
	}
	for (unsigned i =0; i < windows.size();i++){
		if (windowTitles[i].compare("") != 0){
			drawNotch(windows[i]);
		}
	}
	if (numDrawn == 0){
		drawNotch(HWND_DESKTOP);
	}
	count ++;
}

void init(){
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	grpx = new Gdiplus::Graphics(GetDC(HWND_DESKTOP));
	image = new Gdiplus::Image(L"notch.png");
}

void updateWindows(){
	windowTitles.clear();
	windows.clear();
	EnumWindows(callBackProc, 0);
	for(unsigned i = 0; i < windows.size(); i++){
		if (IsWindowVisible(windows[i])){
			char title[1000];
			GetWindowText(windows[i], title, 1000);
			windowTitles.push_back(title);
		} else{
			windowTitles.push_back("");
		}
	}
}

int main() {
	FreeConsole();
	init();
	while(true){
		updateWindows();
		drawNotches();
		Sleep(10);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
}

