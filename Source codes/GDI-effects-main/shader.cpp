// shader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>

int main()
{
    //Get screen sizes
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    int size = x * y;
    DWORD* pixels = (DWORD*)VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    while (true) {
        //Prepare the pixels
        PRGBTRIPLE rgb;
        HDC hdc = GetDC(0);
        HDC mdc = CreateCompatibleDC(hdc);
        BITMAPINFO bmi = { 40, x, y, 1, 24 };
        HBITMAP bitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&rgb, 0, 0); 
        
        //Read the pixels
        SelectObject(mdc, bitmap);
        BitBlt(mdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

        //Write the pixels
        for (int i = 0; i < size; i++) {
            rgb[i].rgbtRed += GetRValue(i) * 10;
            rgb[i].rgbtGreen += GetGValue(i) * 10;
            rgb[i].rgbtBlue += GetBValue(i) * 10;
        }

        BitBlt(hdc, 0, 0, x, y, mdc, 0, 0, SRCCOPY);
        Sleep(10);

        //Delete objects so the program won't use more and more memory
        ReleaseDC(0, hdc);
        DeleteObject(bitmap);
        DeleteObject(rgb);
        DeleteDC(hdc);
        DeleteDC(mdc);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
