#include <windows.h>
#include <vector>
#include <tchar.h>
#include <math.h>

struct CustomShape {
    RECT rect;
    bool isDrawing;
    bool isRectangle;
    bool isCircle;
    bool isStar;
    bool isCube;
};

std::vector<CustomShape> shapes;

bool isDrawingRectangle = false;
bool isDrawingTriangle = false;
bool isDrawingCircle = false;
bool isDrawingStar = false;
bool isDrawingCube = false;
bool isErasing = false; // Added to indicate if erasing mode is active
POINT starPoints[5];
POINT initialClick; // Store the initial click position

bool isMovingShape = false;
int movingShapeIndex = -1;

void DrawShapes(HWND hWnd, HDC hdc) {
    for (size_t i = 0; i < shapes.size(); i++) {
        HBRUSH hBrush;
        HRGN hStarRegion = CreatePolygonRgn(starPoints, 5, WINDING);

        if (shapes[i].isRectangle) {
            hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Red rectangle
        }
        else if (shapes[i].isCircle) {
            hBrush = CreateSolidBrush(RGB(0, 255, 0)); // Green circle
        }
        else if (shapes[i].isStar) {
            hBrush = CreateSolidBrush(RGB(255, 255, 0)); // Yellow star
        }
        else if (shapes[i].isCube) {
            hBrush = CreateSolidBrush(RGB(255, 0, 255)); // Magenta cube
        }
        else {
            hBrush = CreateSolidBrush(RGB(0, 0, 255)); // Blue triangle
        }

        SelectObject(hdc, hBrush);

        if (shapes[i].isRectangle) {
            Rectangle(hdc, shapes[i].rect.left, shapes[i].rect.top, shapes[i].rect.right, shapes[i].rect.bottom);
        }
        else if (shapes[i].isCircle) {
            Ellipse(hdc, shapes[i].rect.left, shapes[i].rect.top, shapes[i].rect.right, shapes[i].rect.bottom);
        }
        else if (shapes[i].isStar) {
            
            int starWidth = shapes[i].rect.right - shapes[i].rect.left;
            int starHeight = shapes[i].rect.bottom - shapes[i].rect.top;
            int starSize = min(starWidth, starHeight); // 가로와 세로 중 작은 값을 선택

            for (int j = 0; j < 5; j++) {
                double angle = 3.1415926535897932384626433832795 * (j * 4.0 / 5.0);
                int x = shapes[i].rect.left + static_cast<int>(starSize * cos(angle));
                int y = shapes[i].rect.top + static_cast<int>(starSize * sin(angle));
                starPoints[j].x = x;
                starPoints[j].y = y;
            }


            // Create a region for the star
            HRGN hStarRegion = CreatePolygonRgn(starPoints, 5, WINDING);

            // Fill the star with the specified color
            FillRgn(hdc, hStarRegion, hBrush);

            // Delete the region
            DeleteObject(hStarRegion);
        }
        else if (shapes[i].isCube) {
            int centerX = (shapes[i].rect.left + shapes[i].rect.right) / 2;
            int centerY = (shapes[i].rect.top + shapes[i].rect.bottom) / 2;
            int halfSize = (shapes[i].rect.right - shapes[i].rect.left) / 2;

            // Create a solid pen for the front square
            HPEN hSolidPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            HPEN hDashedPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0)); // Create a dashed pen

            // Draw the front square with solid lines
            SelectObject(hdc, hSolidPen);

            int frontTopLeftX = centerX - halfSize;
            int frontTopLeftY = centerY - halfSize;
            int frontTopRightX = centerX + halfSize;
            int frontTopRightY = centerY - halfSize;
            int frontBottomLeftX = centerX - halfSize;
            int frontBottomLeftY = centerY + halfSize;
            int frontBottomRightX = centerX + halfSize;
            int frontBottomRightY = centerY + halfSize;
            Rectangle(hdc, frontTopLeftX, frontTopLeftY, frontBottomRightX, frontBottomRightY);

            // Draw the back square with dashed lines
            SelectObject(hdc, hDashedPen);

            int backTopLeftX = centerX - halfSize / 2;
            int backTopLeftY = centerY - halfSize / 2;
            int backTopRightX = centerX + halfSize / 2;
            int backTopRightY = centerY - halfSize / 2;
            int backBottomLeftX = centerX - halfSize / 2;
            int backBottomLeftY = centerY + halfSize / 2;
            int backBottomRightX = centerX + halfSize / 2;
            int backBottomRightY = centerY + halfSize / 2;
            Rectangle(hdc, backTopLeftX, backTopLeftY, backBottomRightX, backBottomRightY);

            // Draw the dashed lines for the back square
            MoveToEx(hdc, backTopLeftX, backTopLeftY, NULL);
            LineTo(hdc, backTopRightX, backTopRightY);
            LineTo(hdc, backBottomRightX, backBottomRightY);
            LineTo(hdc, backBottomLeftX, backBottomLeftY);
            LineTo(hdc, backTopLeftX, backTopLeftY);

            // Draw the dashed lines for the top square
            MoveToEx(hdc, frontTopLeftX, frontTopLeftY, NULL);
            LineTo(hdc, backTopLeftX, backTopLeftY);
            MoveToEx(hdc, frontTopRightX, frontTopRightY, NULL);
            LineTo(hdc, backTopRightX, backTopRightY);

            // Draw the dashed lines for the bottom square
            MoveToEx(hdc, frontBottomLeftX, frontBottomLeftY, NULL);
            LineTo(hdc, backBottomLeftX, backBottomLeftY);
            MoveToEx(hdc, frontBottomRightX, frontBottomRightY, NULL);
            LineTo(hdc, backBottomRightX, backBottomRightY);

            // Clean up, restore the original pens
            HRGN hStarRegion = CreatePolygonRgn(starPoints, 5, WINDING);

         
            SelectObject(hdc, hSolidPen);
           DeleteObject(hDashedPen);
           
        }
        else {
            POINT points[3];
            points[0].x = (shapes[i].rect.left + shapes[i].rect.right) / 2;
            points[0].y = shapes[i].rect.top;
            points[1].x = shapes[i].rect.left;
            points[1].y = shapes[i].rect.bottom;
            points[2].x = shapes[i].rect.right;
            points[2].y = shapes[i].rect.bottom;
            Polygon(hdc, points, 3);
        }

        DeleteObject(hBrush);
    }
}

void StartDrawing(int x, int y) {
    CustomShape newShape;
    newShape.isDrawing = true;
    initialClick.x = x; // Store the initial click X coordinate
    initialClick.y = y; // Store the initial click Y coordinate
    newShape.rect.left = x;
    newShape.rect.top = y;
    newShape.rect.right = x;
    newShape.rect.bottom = y;
    newShape.isRectangle = isDrawingRectangle;
    newShape.isCircle = isDrawingCircle;
    newShape.isStar = isDrawingStar;
    newShape.isCube = isDrawingCube;
    shapes.push_back(newShape);
}

void UpdateDrawing(int x, int y) {
    if (!shapes.empty() && shapes.back().isDrawing) {
        // Update the rectangle coordinates based on the initial click position
        shapes.back().rect.left = min(x, initialClick.x);
        shapes.back().rect.top = min(y, initialClick.y);
        shapes.back().rect.right = max(x, initialClick.x);
        shapes.back().rect.bottom = max(y, initialClick.y);
        InvalidateRect(NULL, NULL, TRUE);
    }
}

void StopDrawing() {
    if (!shapes.empty() && shapes.back().isDrawing) {
        shapes.back().isDrawing = false;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_LBUTTONDOWN:
        if (isErasing) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            bool deleted = false; // 삭제 여부를 나타내는 플래그
            // 그림을 클릭했을 때 해당 그림을 삭제합니다.
            for (int i = shapes.size() - 1; i >= 0; --i) {
                if (PtInRect(&shapes[i].rect, { mouseX, mouseY })) {
                    shapes.erase(shapes.begin() + i);
                    deleted = true; // 클릭한 도형을 삭제했음을 표시
                    InvalidateRect(hWnd, NULL, TRUE);
                    break; // 가장 위의 도형만 삭제합니다.
                }
            }
            if (!deleted) {
                // 만약 클릭한 위치에 도형이 없다면, 그림을 그리기 모드로 변경
                StartDrawing(mouseX, mouseY);
            }
        }
        else {
            StartDrawing(LOWORD(lParam), HIWORD(lParam));
        }
        break;
    case WM_LBUTTONUP:
        StopDrawing();
        if (isErasing) {
            isDrawingRectangle = false;
            isDrawingTriangle = false;
            isDrawingCircle = false;
            isDrawingStar = false;
            isDrawingCube = false;
        }
        break;
    case WM_RBUTTONDOWN:
        if (isErasing) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            bool deleted = false;

            for (int i = shapes.size() - 1; i >= 0; --i) {
                if (PtInRect(&shapes[i].rect, { mouseX, mouseY })) {
                    shapes.erase(shapes.begin() + i);
                    deleted = true;
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                }
            }

            if (!deleted) {
                StartDrawing(mouseX, mouseY);
            }
        }
        else {
            // 마우스 우클릭으로 도형 선택
            for (int i = shapes.size() - 1; i >= 0; --i) {
                if (PtInRect(&shapes[i].rect, { LOWORD(lParam), HIWORD(lParam) })) {
                    isMovingShape = true;
                    movingShapeIndex = i;
                    initialClick.x = LOWORD(lParam);
                    initialClick.y = HIWORD(lParam);
                    SetCapture(hWnd);
                    break;
                }
            }
        }
        break;

    case WM_RBUTTONUP:
        if (isMovingShape) {
            // 마우스 우클릭 떼면 도형 이동 모드 비활성화
            isMovingShape = false;
            ReleaseCapture();
        }
        break;

    case WM_MOUSEMOVE:
        if (!isErasing) {
            UpdateDrawing(LOWORD(lParam), HIWORD(lParam));
        }
        if (isMovingShape) {
            int offsetX = LOWORD(lParam) - initialClick.x;
            int offsetY = HIWORD(lParam) - initialClick.y;
            shapes[movingShapeIndex].rect.left += offsetX;
            shapes[movingShapeIndex].rect.right += offsetX;
            shapes[movingShapeIndex].rect.top += offsetY;
            shapes[movingShapeIndex].rect.bottom += offsetY;
            initialClick.x = LOWORD(lParam);
            initialClick.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawShapes(hWnd, hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: // "사각형" 버튼을 눌렀을 때
            isDrawingRectangle = true;
            isDrawingTriangle = false;
            isDrawingCircle = false;
            isDrawingStar = false;
            isDrawingCube = false;
            isErasing = false;
            break;
        case 2: // "삼각형" 버튼을 눌렀을 때
            isDrawingRectangle = false;
            isDrawingTriangle = true;
            isDrawingCircle = false;
            isDrawingStar = false;
            isDrawingCube = false;
            isErasing = false;
            break;
        case 3: // "원" 버튼을 눌렀을 때
            isDrawingRectangle = false;
            isDrawingTriangle = false;
            isDrawingCircle = true;
            isDrawingStar = false;
            isDrawingCube = false;
            isErasing = false;
            break;
        case 4: // "별" 버튼을 눌렀을 때
            isDrawingRectangle = false;
            isDrawingTriangle = false;
            isDrawingCircle = false;
            isDrawingStar = true;
            isDrawingCube = false;
            isErasing = false;
            break;
        case 5: // "직육면체" 버튼을 눌렀을 때
            isDrawingRectangle = false;
            isDrawingTriangle = false;
            isDrawingCircle = false;
            isDrawingStar = false;
            isDrawingCube = true;
            isErasing = false;
            break;
        case 6: // "지우개" 버튼을 눌렀을 때
            isDrawingRectangle = false;
            isDrawingTriangle = false;
            isDrawingCircle = false;
            isDrawingStar = false;
            isDrawingCube = false;
            isErasing = true;
            break;
        }
        break;
    case WM_CREATE: {
        CreateWindow(_T("BUTTON"), _T("사각형"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 40, hWnd, (HMENU)1, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("삼각형"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 20, 100, 40, hWnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("원"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 240, 20, 100, 40, hWnd, (HMENU)3, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("별"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 350, 20, 100, 40, hWnd, (HMENU)4, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("직육면체"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 460, 20, 100, 40, hWnd, (HMENU)5, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("지우개"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 570, 20, 100, 40, hWnd, (HMENU)6, NULL, NULL);
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
        L"ButtonWindowClass", L"Win32 Drawing Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
