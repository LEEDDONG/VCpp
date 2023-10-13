#define UNICODE
#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isKeyPressed = 0;
int isCrashed = 0; // 충돌 상태를 나타내는 변수

RECT rect_user = { 5, 5, 10, 10 }; // 파란색 사각형
RECT rect_target = { 50, 50, 150, 150 }; // 핑크색 사각형

// 두 개의 RECT 구조체가 겹치는지 확인하는 함수
BOOL RectanglesOverlap(RECT rect1, RECT rect2)
{
    return (rect1.left < rect2.right&& rect1.right > rect2.left &&
        rect1.top < rect2.bottom&& rect1.bottom > rect2.top);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
    HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));
    const wchar_t* text = L"Crash!!!";

    switch (uMsg)
    {
    case WM_KEYDOWN:
        isKeyPressed = 1;
        if (wParam == VK_RIGHT)
        {
            rect_user.left += 1;
            rect_user.right += 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (wParam == VK_LEFT)
        {
            rect_user.left -= 1;
            rect_user.right -= 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (wParam == VK_UP)
        {
            rect_user.top -= 1;
            rect_user.bottom -= 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (wParam == VK_DOWN)
        {
            rect_user.top += 1;
            rect_user.bottom += 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        isKeyPressed = 0;
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (RectanglesOverlap(rect_user, rect_target))
        {
            // 두 개의 사각형이 겹치면 "Crush!!!" 텍스트를 화면 왼쪽 상단에 표시
            TextOut(hdc, 0, 0, text, lstrlen(text));
        }

        // 도형 그리기 코드 (FillRect 함수 등)
        if (isKeyPressed)
        {
            FillRect(hdc, &rect_target, hBrush_target);
            FillRect(hdc, &rect_user, hBrush_user);
        }
        else
        {
            FillRect(hdc, &rect_target, hBrush_target);
            FillRect(hdc, &rect_user, hBrush_eraser);
        }

        EndPaint(hwnd, &ps);
    }
    break;


    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    DeleteObject(hBrush_user);
    DeleteObject(hBrush_target);
    DeleteObject(hBrush_eraser);
    ReleaseDC(hwnd, hdc);

    return S_OK;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));

    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WindowProc;

    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("컴소 Application"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return (int)msg.wParam;
}
