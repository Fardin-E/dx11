#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	try
	{
		Window wnd(800, 300, L"window");

		MSG msg;
		BOOL gResult;
		while ((gResult) = GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_MENU))
			{
				MessageBoxA(nullptr, "Something Happened!", "Space Key was pressed", MB_OK | MB_ICONEXCLAMATION);
			}
		}

		if (gResult == 1)
		{
			return -1;
		}

		return static_cast<int>(msg.wParam);
	}
	catch (const CustomException &e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception &e)
	{
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available", "Unknown Exception thrown", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
	
}