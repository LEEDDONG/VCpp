#include <windows.h>
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
POINT startDrag;
POINT startMove;
POINT circleCenter;
RECT currentRect = { 0, 0, 0, 0 };
RECT drawArea = { 16, 96, 764, 424 };

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

void DrawBonobonoFace(HDC hdc) {
    int faceLeft = 220;
    int faceTop = 100;
    int faceRight = 480;
    int faceBottom = 350;
    // 얼굴 영역을 그리기
    HBRUSH hFaceBrush = CreateSolidBrush(RGB(127, 200, 255)); // 흰색 얼굴
    SelectObject(hdc, hFaceBrush);
    Ellipse(hdc, faceLeft, faceTop, faceRight, faceBottom);
    DeleteObject(hFaceBrush);
    if (isspacebar) {
        // 왼쪽찡긋
        int wstartX = 250;
        int wstartY = 200;
        int wendX = 230;
        int wendY = 190;

        MoveToEx(hdc, wstartX, wstartY, NULL); // 시작점 이동
        LineTo(hdc, wendX, wendY); // 대각선 

        int wrstartX = 250;
        int wrstartY = 200;
        int wrendX = 230;
        int wrendY = 235;

        MoveToEx(hdc, wrstartX, wrstartY, NULL); // 시작점 이동
        LineTo(hdc, wendX, wrendY); // 대각선 그리기

        // 왼쪽찡긋
        int wkrstartX = 450;
        int wkrstartY = 200;
        int wkrendX = 470;
        int wkrendY = 190;

        MoveToEx(hdc, wkrstartX, wkrstartY, NULL); // 시작점 이동
        LineTo(hdc, wkrendX, wkrendY); // 대각선 

        int wklstartX = 450;
        int wklstartY = 200;
        int wklendX = 470;
        int wklendY = 235;

        MoveToEx(hdc, wklstartX, wklstartY, NULL); // 시작점 이동
        LineTo(hdc, wklendX, wklendY); // 대각선 그리기

    }
    else {


        // 눈 그리기
        int eyeWidth = 6;   // 눈 가로 반지름
        int eyeHeight = 12; // 눈 세로 반지름
        int leftEyeX = 250;
        int rightEyeX = 450;
        int eyeY = 200;

        HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // 눈 색상 (검정색)
        SelectObject(hdc, hEyeBrush);
        Ellipse(hdc, leftEyeX - eyeWidth, eyeY - eyeHeight, leftEyeX + eyeWidth, eyeY + eyeHeight);
        Ellipse(hdc, rightEyeX - eyeWidth, eyeY - eyeHeight, rightEyeX + eyeWidth, eyeY + eyeHeight);
        DeleteObject(hEyeBrush);

        // 눈흰색 그리기
        int wEyeWidth = 3;    // 흰색 눈 가로 반지름
        int wEyeHeight = 4;   // 흰색 눈 세로 반지름
        int leftWEyeX = 250;
        int rightWEyeX = 450;
        int weyeY = 195;

        HBRUSH hwEyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // 눈 색상 (흰색)
        SelectObject(hdc, hwEyeBrush);
        Ellipse(hdc, leftWEyeX - wEyeWidth, weyeY - wEyeHeight, leftWEyeX + wEyeWidth, weyeY + wEyeHeight);
        Ellipse(hdc, rightWEyeX - wEyeWidth, weyeY - wEyeHeight, rightWEyeX + wEyeWidth, weyeY + wEyeHeight);
        DeleteObject(hwEyeBrush);
    }
    // 입술 그리기
    int lipLeft = 335;
    int lipRight = 365;
    int lipTop = 250;
    int lipBottom = 300;

    HBRUSH hLipBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입술 색상 (빨간색)
    SelectObject(hdc, hLipBrush);
    Ellipse(hdc, lipLeft, lipTop, lipRight, lipBottom);
    DeleteObject(hLipBrush);
    // 코1
    int noseLeft = 300;
    int noseRight = 350;
    int noseTop = 220;
    int noseBottom = 270;

    HBRUSH hnose1Brush = CreateSolidBrush(RGB(255, 255, 255)); // (코1)
    SelectObject(hdc, hnose1Brush);
    Ellipse(hdc, noseLeft, noseTop, noseRight, noseBottom);
    DeleteObject(hnose1Brush);
    // 코2
    int rnoseLeft = 350;
    int rnoseRight = 400;
    int rnoseTop = 220;
    int rnoseBottom = 270;

    HBRUSH hnose2Brush = CreateSolidBrush(RGB(255, 255, 255)); //코2
    SelectObject(hdc, hnose2Brush);
    Ellipse(hdc, rnoseLeft, rnoseTop, rnoseRight, rnoseBottom);
    DeleteObject(hnose2Brush);
    // 코3
    int cnoseLeft = 335;
    int cnoseRight = 365;
    int cnoseTop = 210;
    int cnoseBottom = 240;

    HBRUSH hnose3Brush = CreateSolidBrush(RGB(0, 0, 0)); //코2
    SelectObject(hdc, hnose3Brush);
    Ellipse(hdc, cnoseLeft, cnoseTop, cnoseRight, cnoseBottom);
    DeleteObject(hnose3Brush);
    // 수염1
    int startX = 290;
    int startY = 280;
    int endX = 310;
    int endY = 250;

    MoveToEx(hdc, startX, startY, NULL); // 시작점 이동
    LineTo(hdc, endX, endY); // 대각선 그리기
     // 수염2
    int start2X = 275;
    int start2Y = 230;
    int end2X = 310;
    int end2Y = 235;

    MoveToEx(hdc, start2X, start2Y, NULL); // 시작점 이동
    LineTo(hdc, end2X, end2Y); // 대각선 그리기
     // 수염3
    int start3X = 410;
    int start3Y = 275;
    int end3X = 390;
    int end3Y = 250;

    MoveToEx(hdc, start3X, start3Y, NULL); // 시작점 이동
    LineTo(hdc, end3X, end3Y); // 대각선 그리기
     // 수염4
    int start4X = 415;
    int start4Y = 220;
    int end4X = 385;
    int end4Y = 230;

    MoveToEx(hdc, start4X, start4Y, NULL); // 시작점 이동
    LineTo(hdc, end4X, end4Y); // 대각선 그리기

}
void DrawRyanFace(HDC hdc) {
    // Ryan 얼굴을 그리는 코드를 작성하세요.
    // Bonobono 얼굴 그리는 코드와 유사하지만 Ryan의 얼굴에 맞게 조정되어야 합니다.
        //왼쪽 귀
    int learLeft = 220;
    int learTop = 100;
    int learRight = 300;
    int learBottom = 170;



    HBRUSH learBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, learBrush);
    Ellipse(hdc, learLeft, learTop, learRight, learBottom);
    DeleteObject(learBrush);

    //오른쪽 귀
    int rearLeft = 400;
    int rearTop = 100;
    int rearRight = 480;
    int rearBottom = 170;

    // 얼굴 영역을 그리기
    HBRUSH rearBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, rearBrush);
    Ellipse(hdc, rearLeft, rearTop, rearRight, rearBottom);
    DeleteObject(rearBrush);

    int faceLeft = 220;
    int faceTop = 100;
    int faceRight = 480;
    int faceBottom = 350;

    // 얼굴 영역을 그리기
    HBRUSH hFaceBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hFaceBrush);
    Ellipse(hdc, faceLeft, faceTop, faceRight, faceBottom);
    DeleteObject(hFaceBrush);




    //  왼쪽 눈
    // 눈흰색 그리기
    int wEyeWidth = 8;    // 흰색 눈 가로 반지름
    int wEyeHeight = 8;   // 흰색 눈 세로 반지름
    int leftWEyeX = 300;
    int rightWEyeX = 400;
    int weyeY = 195;

    HBRUSH hwEyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // 눈 색상 (흰색)
    SelectObject(hdc, hwEyeBrush);
    Ellipse(hdc, leftWEyeX - wEyeWidth, weyeY - wEyeHeight, leftWEyeX + wEyeWidth, weyeY + wEyeHeight);
    Ellipse(hdc, rightWEyeX - wEyeWidth, weyeY - wEyeHeight, rightWEyeX + wEyeWidth, weyeY + wEyeHeight);
    DeleteObject(hwEyeBrush);

    //// 라이언 왼코

    //   int lnosewidth = 12;    // 흰색 눈 가로 반지름
    //   int rnoseheight = 12;   // 흰색 눈 세로 반지름
    //   int leftweyex = 330;
    //   int rightweyex = 460;
    //   int weyey = 230;

    //   hbrush hweyebrush = createsolidbrush(rgb(255, 255, 255)); // 눈 색상 (흰색)
    //   selectobject(hdc, hweyebrush);
    //   ellipse(hdc, leftweyex - weyewidth, weyey - weyeheight, leftweyex + weyewidth, weyey + weyeheight);
    //   ellipse(hdc, rightweyex - weyewidth, weyey - weyeheight, rightweyex + weyewidth, weyey + weyeheight);
    //   deleteobject(hweyebrush);







}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    RECT Box = { 8, 8, 772, 432 };

    switch (message) {
    case WM_COMMAND:
        isBoxVisible = false;
        isCirclesible = false;
        isbono = false;
        if (LOWORD(wParam) == BOX_BUTTON_ID) {
            isBoxVisible = true;
        }
        if (LOWORD(wParam) == CIRCLE_BUTTON_ID) {
            isCirclesible = true;
        }
        if (LOWORD(wParam) == BONOBONO_BUTTON_ID) {
            isbono = true;
            isryan = false;
        }

        if (LOWORD(wParam) == RYAN_BUTTON_ID) {
            isbono = false;
            isryan = true;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        SetFocus(hWnd);
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
        if (isMoving && isCirclesible) {
            HDC hdc = GetDC(hWnd);

            POINT currentMove;
            currentMove.x = LOWORD(lParam);
            currentMove.y = HIWORD(lParam);

            // 현재 중심 좌표와 반지름 계산
            int centerX = (currentRect.left + currentRect.right) / 2;
            int centerY = (currentRect.top + currentRect.bottom) / 2;
            int radius = (currentRect.right - currentRect.left) / 2;

            // 드래그 이동 벡터 계산
            int deltaX = currentMove.x - startMove.x;
            int deltaY = currentMove.y - startMove.y;

            // 드래그 방향에 따라 확대 또는 축소
            if (deltaX > 0) {
                // 오른쪽으로 드래그한 경우 확대
                radius += deltaX;
            }
            if (deltaX < 0) {
                // 왼쪽으로 드래그한 경우 축소
                radius -= abs(deltaX);
                radius -= abs(deltaX);
            }

            // 반지름이 음수가 되지 않도록 처리
            radius = max(radius, 100);

            // 중심 좌표 계산
            centerX = currentMove.x;

            // 수정된 중심과 반지름을 사용하여 원 그리기
            int newLeft = centerX - radius;
            int newTop = centerY - radius;
            int newRight = centerX + radius;
            int newBottom = centerY + radius;

            // 중심 좌표를 벗어나지 않도록 조정
            newLeft = max(drawArea.left, newLeft);
            newTop = max(drawArea.top, newTop);
            newRight = min(drawArea.right, newRight);
            newBottom = min(drawArea.bottom, newBottom);

            // 이전에 그린 사각형을 지웁니다.
            HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &currentRect, hBackgroundBrush);
            DeleteObject(hBackgroundBrush);

            currentRect.left = newLeft;
            currentRect.top = newTop;
            currentRect.right = newRight;
            currentRect.bottom = newBottom;


            // 수정된 원 그리기
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
            DeleteObject(hBrush);

            ReleaseDC(hWnd, hdc);
        }
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
            if (isCirclesible) {
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
            if (isCirclesible) {
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
    case WM_KEYDOWN: // 스페이스바를 눌렀을 때
        if (wParam == VK_SPACE) {
            isspacebar = true;
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
        isspacebar = false;
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

        if (isBoxVisible) {
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
            DeleteObject(hBrush);
        }
        if (isCirclesible) {
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, currentRect.left, currentRect.top, currentRect.right, currentRect.bottom);
            DeleteObject(hBrush);
        }
        if (isbono) {
            // 스페이스바를 눌렀을 때 윙크하는 부분
            DrawBonobonoFace(hdc);
        }
        if (isryan) {
            DrawRyanFace(hdc);
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
        16, 16, 130, 64, hWnd, (HMENU)BOX_BUTTON_ID, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        162, 16, 130, 64, hWnd, (HMENU)CIRCLE_BUTTON_ID, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        308, 16, 130, 64, hWnd, (HMENU)BONOBONO_BUTTON_ID, hInstance, NULL);
    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        454, 16, 130, 64, hWnd, (HMENU)RYAN_BUTTON_ID, hInstance, NULL);
    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        620, 16, 130, 64, hWnd, (HMENU)CUBE_BUTTON_ID, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}