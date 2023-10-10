#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT lastMousePs = { 0 };
const wchar_t* text = L"crash!!!";

int isMouseLButtonPressed = 0; // 왼쪽 마우스 버튼이 눌렸는지 여부를 나타내는 플래그
int isMouseRButtonPressed = 0; // 오른쪽 마우스 버튼이 눌렸는지 여부를 나타내는 플래그
bool isMouseInRg = 0; // 마우스가 도형 범위 내에 있는지 여부를 나타내는 플래그

// 마우스가 도형 범위 내에 있는지 확인
bool IsMouseInsideShape(POINT mousePs, POINT diagramStart, POINT diagramEnd)
{
    // 도형의 시작점과 끝점을 기준으로 마우스 위치를 확인하여 마우스가 도형 내부에 있는지 판단합니다.
    if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
        return (mousePs.x <= diagramStart.x && mousePs.x >= diagramEnd.x &&
            mousePs.y >= diagramStart.y && mousePs.y <= diagramEnd.y);
    }
    else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
        return (mousePs.x >= diagramStart.x && mousePs.x <= diagramEnd.x &&
            mousePs.y <= diagramStart.y && mousePs.y >= diagramEnd.y);
    }


    else if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
        return (mousePs.x >= diagramStart.x && mousePs.x <= diagramEnd.x &&
            mousePs.y >= diagramStart.y && mousePs.y <= diagramEnd.y);
    }
   
    else {
        return (mousePs.x <= diagramStart.x && mousePs.x >= diagramEnd.x &&
            mousePs.y <= diagramStart.y && mousePs.y >= diagramEnd.y);
    }
}

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        // 창 크기 변경 못하게 막음
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* info = (MINMAXINFO*)lParam;
        info->ptMinTrackSize.x = 800; // 최소 가로 크기를 800으로 설정
        info->ptMinTrackSize.y = 600; // 최소 세로 크기를 600으로 설정
        info->ptMaxTrackSize.x = 800; // 최대 가로 크기를 800으로 설정
        info->ptMaxTrackSize.y = 600; // 최대 세로 크기를 600으로 설정
    }
    break;

  

    // 마우스 이동 중
    case WM_MOUSEMOVE:
    {
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (isMouseRButtonPressed && isMouseInRg) {
            int deltaX = LOWORD(lParam) - lastMousePs.x;
            int deltaY = HIWORD(lParam) - lastMousePs.y;

            // 그림의 위치를 이동
            startPoint.x += deltaX;
            startPoint.y += deltaY;
            endPoint.x += deltaX;
            endPoint.y += deltaY;

            // 마우스 위치 업데이트
            lastMousePs.x = LOWORD(lParam);
            lastMousePs.y = HIWORD(lParam);

            // WM_PAINT 메시지를 유발하여 그림을 다시 그립니다.
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    

    case WM_LBUTTONDOWN://왼쪽 클릭할 경우
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 1; // 왼쪽 마우스 버튼 눌림 플래그 설정
    }
    break;

    case WM_LBUTTONUP://왼쪽 클릭을 땔 경우
    {
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 0; // 왼쪽 마우스 버튼 눌림 플래그 해제

        // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
    case WM_RBUTTONDOWN://오른쪽 클릭할 경우
    {
        isMouseRButtonPressed = 1; // 오른쪽 마우스 버튼 눌림 플래그 설정

        lastMousePs.x = LOWORD(lParam);
        lastMousePs.y = HIWORD(lParam);

        // 마우스 위치가 도형 범위 내에 있는지 확인
        if (IsMouseInsideShape(lastMousePs, startPoint, endPoint))
        {

            isMouseInRg = 1; // 마우스가 도형 범위 내에 있음을 설정
        }
        else
        {

            isMouseInRg = 0; // 마우스가 도형 범위 내에 없음을 설정

        }
    }
    break;
    case WM_RBUTTONUP://오른쪽 클릭을 땔 경우
    {
        isMouseRButtonPressed = 0; // 오른쪽 마우스 버튼 눌림 플래그 해제
    }
    break;

    case WM_PAINT:
    {
        HDC hdc = GetDC(hwnd);
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0)); // 노란색 브러시 생성

        if (isMouseLButtonPressed || (isMouseRButtonPressed && isMouseInRg))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // 창을 흰색으로 채움

            MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
            rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
            FillRect(hdc, &rect, hBrush); // 도형을 그림
        }

        DeleteObject(hBrush);
        ReleaseDC(hwnd, hdc);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0); // 종료 메시지를 보냄
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return S_OK;
}

#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
    /* 윈도우 클래스 선언. */
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));   // 모두 0으로 초기화.

    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    // 윈도우 클래스 등록.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);   // 예외
    }

    // 윈도우 생성
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007042 이동현"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        800, 600,
        NULL, NULL,
        hInstance,
        NULL
    );

    // 오류 검사.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW); // 창 띄우고
    UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.

    // 메시지 처리 루프.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // 메시지 처리.
        if (GetMessage(&msg, hwnd, 0, 0))
        {
            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);
        }
    }

    // 종료 메시지 보내기
    return (int)msg.wParam;
}
