#include "../Ryan/yuhanCG.h"
#define BOX_BUTTON_ID 1
#define CIRCLE_BUTTON_ID 2
#define BONOBONO_BUTTON_ID 3
#define RYAN_BUTTON_ID 4
#define CUBE_BUTTON_ID 5
bool isBoxVisible = false;
bool isCirclesible = false;
bool isDragging = false;
bool isMoving = false;
bool isspacebar = false;
bool isbono = false;
bool isryan = false;
bool isCubeVisible = false;
int blink = 0;


POINT startDrag;
POINT startMove;
POINT circleCenter;
RECT currentRect = { 0, 0, 0, 0 };
RECT drawArea = { 16, 96, 764, 424 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    RECT Box = { 8, 8, 772, 432 };

    switch (message) {
    case WM_COMMAND:
        // Reset all drawing flags
        isBoxVisible = false;
        isCirclesible = false;
        isbono = false;
        isryan = false;
        isCubeVisible = false;

        // Set the appropriate drawing flag based on the clicked button
        if (LOWORD(wParam) == BOX_BUTTON_ID) {
            isBoxVisible = true;
        }
        else if (LOWORD(wParam) == CIRCLE_BUTTON_ID) {
            isCirclesible = true;
        }
        else if (LOWORD(wParam) == BONOBONO_BUTTON_ID) {
            isbono = true;
        }
        else if (LOWORD(wParam) == RYAN_BUTTON_ID) {
            isryan = true;
        }
        else if (LOWORD(wParam) == CUBE_BUTTON_ID) {
            isCubeVisible = true;
        }

        // Invalidate the window to trigger a redraw
        InvalidateRect(hWnd, NULL, TRUE);
        SetFocus(hWnd);
        break;

    case WM_LBUTTONDOWN:
        if (isryan || isBoxVisible || isCirclesible||isCubeVisible) {
            startDrag.x = LOWORD(lParam);
            startDrag.y = HIWORD(lParam);
            isDragging = true;
            isMoving = false;
        }
        break;
    case WM_RBUTTONDOWN:
        if (isryan ) {
            startDrag.x = LOWORD(lParam);
            startDrag.y = HIWORD(lParam);
            isDragging = true;
            isMoving = false;
        }
     
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
        

        
        if (isDragging) {

            HDC hdc = GetDC(hWnd);

            // Update the startMove point based on the drag movement
            startMove.x = LOWORD(lParam);
            startMove.y = HIWORD(lParam);

            // Check if the cursor is within the drawArea
            if (PtInRect(&drawArea, startMove)) {
                // Calculate the new rectangle based on the drag movement
                int newRectLeft = startDrag.x;
                int newRectTop = startDrag.y;
                int newRectRight = startDrag.x;
                int newRectBottom = startDrag.y;

                // Redraw the window only if the cursor is within drawArea
                InvalidateRect(hWnd, &drawArea, TRUE);
                UpdateWindow(hWnd);
                if (isryan) {

                    DrawRyan(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
                }
                if (isCirclesible)
                {
                    DrawCircle(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
                }
                if (isBoxVisible)
                {
                    DrawBox(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);

                }
                if (isCubeVisible) {
                    DrawCube(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
                }
            }
            else {
                // The cursor is outside drawArea, stop drawing
                isDragging = false;
                isMoving = false;
            }

            ReleaseDC(hWnd, hdc);
        }  break;


    case WM_LBUTTONUP:
        if (isryan||isBoxVisible||isCirclesible||isCubeVisible) {
            POINT clickPoint;
            clickPoint.x = LOWORD(lParam);
            clickPoint.y = HIWORD(lParam);


            isDragging = false;
            isMoving = false;

        }
        break;

    case WM_RBUTTONUP:
        if (isryan||isCirclesible||isBoxVisible) {
          
           isDragging = false;
            isMoving = false;

        }
        break;
    case WM_KEYDOWN: // 스페이스바를 눌렀을 때
        if (wParam == VK_SPACE) {
           // isspacebar = true;
            blink = 1;
            if (isbono) {
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }



        break;
    case WM_SETCURSOR:
    {
        // 현재 마우스 커서 위치를 얻습니다.
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);

        // 커서 위치가 drawArea 영역 내에 있는지 확인합니다.
        if (PtInRect(&drawArea, cursorPos)) {
            // drawArea 영역 내에 있다면 십자가 모양의 커서로 설정합니다.
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        }
        else {
            // drawArea 영역 밖에 있다면 원래 커서로 설정합니다.
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }

        return TRUE; // 커서를 변경했음을 알립니다.
    }
    break;

    case WM_KEYUP:
       // isspacebar = false;
        blink = 0;
        if (isbono) {
            InvalidateRect(hWnd, NULL, TRUE);
        }
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
        // Calculate the new rectangle based on the drag movement
        int newRectLeft = startDrag.x;
        int newRectTop = startDrag.y;
        int newRectRight = startDrag.x + (startMove.x - startDrag.x);
        int newRectBottom = startDrag.y + (startMove.y - startDrag.y);

        if (isbono) {
            // 스페이스바를 눌렀을 때 윙크하는 부분
            DrawBonobono(hWnd, hdc, blink);
        }
        if (isryan) {
          

            DrawRyan(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
        } if (isCirclesible) {
           

            DrawCircle(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
        }
        if (isBoxVisible) {
           

            DrawBox(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
        }
        if (isCubeVisible) {
            DrawCube(hWnd, hdc, newRectLeft, newRectTop, newRectRight, newRectBottom);
        }
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


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

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
        16, 24, 134, 64, hWnd, (HMENU)BOX_BUTTON_ID, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        169.5, 24, 134, 64, hWnd, (HMENU)CIRCLE_BUTTON_ID, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        323, 24, 134, 64, hWnd, (HMENU)BONOBONO_BUTTON_ID, hInstance, NULL);
    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        476.5, 24, 134, 64, hWnd, (HMENU)RYAN_BUTTON_ID, hInstance, NULL);
    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        630,24, 134, 64, hWnd, (HMENU)CUBE_BUTTON_ID, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}