#include <windows.h>
#include <comdef.h>
#include <stdio.h>
#include <Wbemidl.h>
#include <commctrl.h>

#include "resource.h"

#pragma comment(lib, "wbemuuid.lib")

HWND hListBox;
HWND hTerminateButton;
int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
void GetProcessesWMI(HWND hWnd);


HINSTANCE hInst;
LPCTSTR szWindowClass = L"ProcessExplorer";
LPCTSTR szTitle = L"Process Explorer";
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;

	int windowWidth = screenWidth * 25 / 100;
	int windowHeight = screenHeight * 50 / 100;

	hWnd = CreateWindow(szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	RECT rect;
	GetWindowRect(hWnd, &rect);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_CREATE:
	{
		hTerminateButton = CreateWindow(
			L"BUTTON", 
			L"End process",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			0, 
			0, 
			100, 
			30, 
			hWnd, 
			(HMENU)ID_MENU_END,
			hInst, 
			NULL);

		HWND hWndListView = CreateWindow(
			WC_LISTVIEW,
			NULL,
			WS_CHILD | LVS_REPORT | WS_VISIBLE | LVS_EDITLABELS,
			0, 0, 500, 400,
			hWnd,
			(HMENU)ID_MENU_LIST,
			hInst,
			NULL);

		// Додаємо колонки
		LVCOLUMN lvColumn;
		lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		lvColumn.cx = 150;

		lvColumn.pszText = (LPWSTR)L"Name";
		ListView_InsertColumn(hWndListView, 0, &lvColumn);

		lvColumn.pszText = (LPWSTR)L"PID";
		ListView_InsertColumn(hWndListView, 1, &lvColumn);

		lvColumn.pszText = (LPWSTR)L"CPU";
		ListView_InsertColumn(hWndListView, 2, &lvColumn);

		lvColumn.pszText = (LPWSTR)L"Memory";
		ListView_InsertColumn(hWndListView, 3, &lvColumn);
	}
	break;

	case WM_SIZE:
	{
		int newWidth = LOWORD(lParam);
		int newHeight = HIWORD(lParam);
		int buttonWidth = 100;
		int buttonHeight = 30;
		SetWindowPos(hTerminateButton, NULL, newWidth - buttonWidth - 10, newHeight - buttonHeight - 10, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}
	break;

	case WM_COMMAND: 
	{
		switch (LOWORD(wParam)) {
			case ID_FILE_RUNNEWTASK:
			{
	
	
	
			}
			break;

			case ID_FILE_EXIT:
			{
				PostQuitMessage(0);
			}
			break;
			
			case ID_VIEW_REFRESHNOW:
			{
				// Refresh the list of processes
			}
			break;
			
			case ID_PROCESS_KILLPROCESS40005:
			{
				// Kill the selected process
			}
			break;
		}

	}
	break;

	// Фіксуємо розміри вікна!!!!!!!!!!!!!!!
	case WM_GETMINMAXINFO:
	{
		// Отримуємо розміри екрану
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		int minWidth = screenWidth * 25 / 100;
		int minHeight = screenHeight * 50 / 100;

		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = minWidth;
		minMaxInfo->ptMinTrackSize.y = minHeight;
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//#include <windows.h>
//#include <comdef.h>
//#include <stdio.h>
//#include <Wbemidl.h>
//#pragma comment(lib, "wbemuuid.lib")
//
//HINSTANCE hInst;
//LPCTSTR szWindowClass = L"ProcessExplorer";
//LPCTSTR szTitle = L"Process Explorer";
//ATOM MyRegisterClass(HINSTANCE hInstance);
//BOOL InitInstance(HINSTANCE, int);
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//// Ідентифікатори для кнопок і компонентів
//#define IDC_BUTTON_REFRESH 102
//#define IDC_LISTBOX_PROCESSES 103
//
//HWND hListBox;
//
//// Прототип функції для отримання процесів через WMI
//void GetProcessesWMI(HWND hWnd);
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
//	int nCmdShow)
//{
//	MSG msg;
//	MyRegisterClass(hInstance);
//
//	if (!InitInstance(hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	return msg.wParam;
//}
//
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = (WNDPROC)WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
//	wcex.lpszMenuName = NULL;
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
//
//	return RegisterClassEx(&wcex);
//}
//
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//	HWND hWnd;
//	hInst = hInstance;
//	hWnd = CreateWindow(szWindowClass,
//		szTitle,
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		500, 400,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//
//	if (!hWnd)
//	{
//		return FALSE;
//	}
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	// Створюємо кнопку Refresh
//	CreateWindow(L"BUTTON", L"Refresh",
//		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//		20, 20, 100, 30, hWnd, (HMENU)IDC_BUTTON_REFRESH, hInst, NULL);
//
//	// Створюємо ListBox для відображення процесів
//	hListBox = CreateWindow(L"LISTBOX", NULL,
//		WS_CHILD | WS_VISIBLE | LBS_STANDARD,
//		20, 60, 450, 300, hWnd, (HMENU)IDC_LISTBOX_PROCESSES, hInst, NULL);
//
//	return TRUE;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		switch (wmId)
//		{
//		case IDC_BUTTON_REFRESH:
//			SendMessage(hListBox, LB_RESETCONTENT, 0, 0); // Очистити ListBox перед оновленням
//			GetProcessesWMI(hWnd);  // Отримання процесів за допомогою WMI
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//	}
//	break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
//void GetProcessesWMI(HWND hWnd)
//{
//    HRESULT hres;
//
//    // 1. Ініціалізація COM.
//    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
//    if (FAILED(hres))
//    {
//        MessageBox(hWnd, L"Failed to initialize COM library.", L"Error", MB_OK | MB_ICONERROR);
//        return;
//    }
//
//    // 2. Ініціалізація security.
//    hres = CoInitializeSecurity(
//        NULL,
//        -1,                          // Дозволити всім організаціям
//        NULL,                        // Дозволити всі авторизації
//        NULL,                        // Зарезервовано
//        RPC_C_AUTHN_LEVEL_DEFAULT,    // Автентифікація за замовчуванням
//        RPC_C_IMP_LEVEL_IMPERSONATE,  // Рівень виконання
//        NULL,                        // Зарезервовано
//        EOAC_NONE,                   // Параметри context
//        NULL                         // Зарезервовано
//    );
//
//    if (FAILED(hres))
//    {
//        MessageBox(hWnd, L"Failed to initialize security.", L"Error", MB_OK | MB_ICONERROR);
//        CoUninitialize();
//        return;
//    }
//
//    // 3. Отримання доступу до локального простору імен "root\\cimv2".
//    IWbemLocator* pLoc = NULL;
//    hres = CoCreateInstance(
//        CLSID_WbemLocator, 0,
//        CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
//
//    if (FAILED(hres))
//    {
//        MessageBox(hWnd, L"Failed to create IWbemLocator object.", L"Error", MB_OK | MB_ICONERROR);
//        CoUninitialize();
//        return;
//    }
//
//    IWbemServices* pSvc = NULL;
//    hres = pLoc->ConnectServer(
//        _bstr_t(L"ROOT\\CIMV2"), // Простір імен WMI
//        NULL,                    // Ім'я користувача
//        NULL,                    // Пароль
//        0,                       // Мова
//        NULL,                    // Безпека
//        0,                       // Контекст
//        0,                       // Контекст
//        &pSvc                    // Інтерфейс IWbemServices
//    );
//
//    if (FAILED(hres))
//    {
//        MessageBox(hWnd, L"Could not connect to WMI server.", L"Error", MB_OK | MB_ICONERROR);
//        pLoc->Release();
//        CoUninitialize();
//        return;
//    }
//
//    // 4. Налаштування рівня захисту для проксі.
//    hres = CoSetProxyBlanket(
//        pSvc,                        // Інтерфейс IWbemServices
//        RPC_C_AUTHN_WINNT,           // Автентифікація
//        RPC_C_AUTHZ_NONE,            // Авторизація
//        NULL,                        // Домен
//        RPC_C_AUTHN_LEVEL_CALL,      // Рівень автентифікації
//        RPC_C_IMP_LEVEL_IMPERSONATE, // Рівень виконання
//        NULL,                        // Проксі
//        EOAC_NONE                    // Параметри
//    );
//
//    if (FAILED(hres))
//    {
//        MessageBox(hWnd, L"Could not set proxy blanket.", L"Error", MB_OK | MB_ICONERROR);
//        pSvc->Release();
//        pLoc->Release();
//        CoUninitialize();
//        return;
//    }
//
//    // 5. Виконання WMI-запиту для отримання процесів.
//    IEnumWbemClassObject* pEnumerator = NULL;
//    hres = pSvc->ExecQuery(
//        bstr_t("WQL"),
//        bstr_t("SELECT Name, ProcessId FROM Win32_Process"),
//        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//        NULL,
//        &pEnumerator);
//
//    if (FAILED(hres))
//    {
//        MessageBox(hWnd, L"WMI query failed.", L"Error", MB_OK | MB_ICONERROR);
//        pSvc->Release();
//        pLoc->Release();
//        CoUninitialize();
//        return;
//    }
//
//    // 6. Обробка результатів запиту.
//    IWbemClassObject* pclsObj = NULL;
//    ULONG uReturn = 0;
//    wchar_t buffer[256];
//
//    while (pEnumerator)
//    {
//        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
//
//        if (0 == uReturn)
//        {
//            break;
//        }
//
//        VARIANT vtProp;
//
//        // Отримання імені процеса
//        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
//        swprintf_s(buffer, 256, L"Process: %s", vtProp.bstrVal);
//        VariantClear(&vtProp);
//
//        // Отримання PID процеса
//        hr = pclsObj->Get(L"ProcessId", 0, &vtProp, 0, 0);
//        swprintf_s(buffer + wcslen(buffer), 256 - wcslen(buffer), L" | PID: %u", vtProp.uintVal);
//        VariantClear(&vtProp);
//
//        // Додавання до ListBox
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
//
//        pclsObj->Release();
//    }
//
//    // 7. Очищення
//    pSvc->Release();
//    pLoc->Release();
//    pEnumerator->Release();
//    CoUninitialize();
//}
