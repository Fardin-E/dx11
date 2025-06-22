#pragma once

#include "WinHeader.h"
#include "CustomException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <sstream>
#include <optional>

class Window
{
public:
	class Exception : public CustomException
	{
	public:
		Exception(int line, const char *file, HRESULT hr) noexcept;
		const char *what() const noexcept override;
		virtual const char *GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const WCHAR *GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass &) = delete;
		WindowClass &operator=(const WindowClass &) = delete;
		static constexpr const WCHAR *wndClassName = L"Direct 3D Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const WCHAR *name);
	~Window();
	Window(const Window &) = delete;
	Window &operator=(const Window &) = delete;
	void SetTitle(const std::wstring &title);
	static std::optional<int> ProcessMessages();
	Keyboard kbd;
	Mouse mouse;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT ms, WPARAM wParam, LPARAM lParam) noexcept;
	int width;
	int height;
	HWND hWnd;
};

// helper macro
#define CSWND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define CSWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())