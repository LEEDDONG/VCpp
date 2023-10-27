#include <windows.h>
#define BOX_BUTTON_ID 1
#define CIRCLE_BUTTON_ID 2
bool isBoxVisible = false;
bool isCirclesible = false;
bool isDragging = false;
bool isMoving = false;
bool isSpacebar = false;
POINT startDrag;
POINT startMove;
POINT circleCenter;
RECT currentRect = { 0, 0, 0, 0 };
RECT drawArea = { 16, 80, 764, 424 };

void DrawBox(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBoxVisible) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 300, 50, 500, 200);
        DeleteObject(hBrush);
    }
    if (isCirclesible) {
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, hBrush);

        // 중심 좌표를 계산
        int centerX = (currentRect.left + currentRect.right) / 2;
        int centerY = (currentRect.top + currentRect.bottom) / 2;

        // 반지름을 계산
        int radius = min((currentRect.right - currentRect.left) / 2, (currentRect.bottom - currentRect.top) / 2);

        // 중심 좌표를 벗어나지 않도록 조정
        centerX = max(drawArea.left + radius, min(centerX, drawArea.right - radius));
        centerY = max(drawArea.top + radius, min(centerY, drawArea.bottom - radius));

        // 수정된 중심과 반지름을 사용하여 원 그리기
        Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

        DeleteObject(hBrush);
    }
}

// 이 함수는 주어진 사각형을 흰색 영역 안으로 제한합니다.
RECT ConstrainRect(const RECT& rect, const RECT& constraint) {
    RECT constrainedRect = rect;
    if (constrainedRect.left < constraint.left) {
        int offsetX = constraint.left - constrainedRect.left;
        OffsetRect(&constrainedRect, offsetX, 0);
    }
    if (constrainedRect.top < constraint.top) {
        int offsetY = constraint.top - constrainedRect.top;
        OffsetRect(&constrainedRect, 0, offsetY);
    }
    if (constrainedRect.right > constraint.right) {
        int offsetX = constraint.right - constrainedRect.right;
        OffsetRect(&constrainedRect, offsetX, 0);
    }
    if (constrainedRect.bottom > constraint.bottom) {
        int offsetY = constraint.bottom - constrainedRect.bottom;
        OffsetRect(&constrainedRect, 0, offsetY);
    }
    return constrainedRect;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    RECT Box = { 8, 8, 772, 432 };

    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == BOX_BUTTON_ID) {
            isBoxVisible = true;
            isCirclesible = false; // Box 버튼을 누를 때 원을 비활성화
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == CIRCLE_BUTTON_ID) {
            isCirclesible = true;
            isBoxVisible = false; // Circle 버튼을 누를 때 상자를 비활성화
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONDOWN:
        if (isBoxVisible || isCirclesible) {
            startDrag.x = LOWORD(lParam);
            startDrag.y = HIWORD(lParam);
            isDragging = true;
            isMoving = false;
        }
        break;
    case WM_RBUTTONDOWN:
        isMoving = false;
        if (isBoxVisible || isCirclesible) {
            POINT clickPoint;
            clickPoint.x = LOWORD(lParam);
            clickPoint.y = HIWORD(lParam);

            // 클릭한 좌표가 그림 내부에 있는지 확인
            if (PtInRect(&currentRect, clickPoint)) {
                startMove.x = clickPoint.x;
                startMove.y = clickPoint.y;
                isMoving = true;
                isDragging = false;
            }
        }
        break;
    case WM_MOUSEMOVE:
        if (isDragging && (isBoxVisible || isCirclesible)) {
            HDC hdc = GetDC(hWnd);

            // 이전에 그린 사각형 또는 원을 지웁니다.
            HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &drawArea, hBackgroundBrush);
            DeleteObject(hBackgroundBrush);

            POINT currentDrag;
            currentDrag.x = LOWORD(lParam);
            currentDrag.y = HIWORD(lParam);

            if (isBoxVisible) {
                // 현재 사각형을 그립니다. 단, 흰색 영역을 벗어나지 못하도록 좌표를 조정합니다.
                currentRect.left = max(drawArea.left, min(startDrag.x, currentDrag.x));
                currentRect.top = max(drawArea.top, min(startDrag.y, currentDrag.y));
                currentRect.right = min(drawArea.right, max(startDrag.x, currentDrag.x));
                currentRect.bottom = min(drawArea.bottom, max(startDrag.y, currentDrag.y));
            }
            else if (isCirclesible) {
                // 원의 중심 좌표와 반지름 계산
                int centerX = (startDrag.x + currentDrag.x) / 2;
                int centerY = (startDrag.y + currentDrag.y) / 2;
                int radius = abs(currentDrag.x - startDrag.x) / 2;
                currentRect.left = max(drawArea.left, min(startDrag.x, currentDrag.x));
                currentRect.top = max(drawArea.top, min(startDrag.y, currentDrag.y));
                currentRect.right = min(drawArea.right, max(startDrag.x, currentDrag.x));
                currentRect.bottom = min(drawArea.bottom, max(startDrag.y, currentDrag.y));
            }

            if (isBoxVisible) {
                HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hBrush);
                Rectangle(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
                DeleteObject(hBrush);
            }
            else if (isCirclesible) {
                HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
                SelectObject(hdc, hBrush);
                Ellipse(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
                DeleteObject(hBrush);
            }

            ReleaseDC(hWnd, hdc);
        }
        if (isMoving && (isBoxVisible || isCirclesible)) {
            HDC hdc = GetDC(hWnd);

            // 이전에 그린 사각형 또는 원을 지웁니다.
            HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &currentRect, hBackgroundBrush);
            DeleteObject(hBackgroundBrush);

            POINT currentMove;
            currentMove.x = LOWORD(lParam);
            currentMove.y = HIWORD(lParam);

            // 사각형 또는 원을 이동시키기 전에 제한된 위치를 계산합니다.
            RECT newRect = currentRect;
            newRect.left += currentMove.x - startMove.x;
            newRect.right += currentMove.x - startMove.x;
            newRect.top += currentMove.y - startMove.y;
            newRect.bottom += currentMove.y - startMove.y;
            newRect = ConstrainRect(newRect, drawArea);

            // 이동된 사각형 또는 원을 그립니다.
            if (isBoxVisible) {
                HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hBrush);
                Rectangle(hdc, newRect.left, newRect.top, newRect.right, newRect.bottom);
                DeleteObject(hBrush);
            }
            else if (isCirclesible) {
                HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
                SelectObject(hdc, hBrush);
                Ellipse(hdc, newRect.left, newRect.top, newRect.right, newRect.bottom);
                DeleteObject(hBrush);
            }

            currentRect = newRect;
            startMove = currentMove;

            ReleaseDC(hWnd, hdc);
        }
        break;

    case WM_LBUTTONUP:
        isDragging = false;
        break;
    case WM_RBUTTONUP:
        isMoving = false;
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));
        FillRect(hdc, &ps.rcPaint, hBackgroundBrush);
        DeleteObject(hBackgroundBrush);
        FrameRect(hdc, &Box, hBrush);
        FrameRect(hdc, &drawArea, hBrush);
        FillRect(hdc, &drawArea, CreateSolidBrush(RGB(255, 255, 255)));
        DeleteObject(hBrush);

        // 저장된 currentRect를 이용하여 마지막에 그린 사각형 또는 원을 복원합니다.
        if (isBoxVisible) {
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
            DeleteObject(hBrush);
        }
        else if (isCirclesible) {
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
            DeleteObject(hBrush);
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
    HWND hButton1, hButton2;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }


    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        100, 100, 800, 480, NULL, NULL, hInstance, NULL);
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        16, 16, 130, 64, hWnd, (HMENU)BOX_BUTTON_ID, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        162, 16, 130, 64, hWnd, (HMENU)CIRCLE_BUTTON_ID, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        308, 16, 130, 64, hWnd, (HMENU)CIRCLE_BUTTON_ID, hInstance, NULL);
    hButton2 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        454, 16, 130, 64, hWnd, (HMENU)CIRCLE_BUTTON_ID, hInstance, NULL);
    hButton2 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        620, 16, 130, 64, hWnd, (HMENU)CIRCLE_BUTTON_ID, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}