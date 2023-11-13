#include "yuhanCG.h"

 
void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    int faceLeft = 220;
    int faceTop = 100;
    int faceRight = 480;
    int faceBottom = 350;
    // �� ������ �׸���
    HBRUSH hFaceBrush = CreateSolidBrush(RGB(127, 200, 255)); // ��� ��
    SelectObject(hdc, hFaceBrush);
    Ellipse(hdc, faceLeft, faceTop, faceRight, faceBottom);
    DeleteObject(hFaceBrush);
    if (blink) {
        // ��������
        int wstartX = 250;
        int wstartY = 200;
        int wendX = 230;
        int wendY = 190;

        MoveToEx(hdc, wstartX, wstartY, NULL); // ������ �̵�
        LineTo(hdc, wendX, wendY); // �밢�� 

        int wrstartX = 250;
        int wrstartY = 200;
        int wrendX = 230;
        int wrendY = 235;

        MoveToEx(hdc, wrstartX, wrstartY, NULL); // ������ �̵�
        LineTo(hdc, wendX, wrendY); // �밢�� �׸���

        // ��������
        int wkrstartX = 450;
        int wkrstartY = 200;
        int wkrendX = 470;
        int wkrendY = 190;

        MoveToEx(hdc, wkrstartX, wkrstartY, NULL); // ������ �̵�
        LineTo(hdc, wkrendX, wkrendY); // �밢�� 

        int wklstartX = 450;
        int wklstartY = 200;
        int wklendX = 470;
        int wklendY = 235;

        MoveToEx(hdc, wklstartX, wklstartY, NULL); // ������ �̵�
        LineTo(hdc, wklendX, wklendY); // �밢�� �׸���

    }
    else {


        // �� �׸���
        int eyeWidth = 6;   // �� ���� ������
        int eyeHeight = 12; // �� ���� ������
        int leftEyeX = 250;
        int rightEyeX = 450;
        int eyeY = 200;

        HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // �� ���� (������)
        SelectObject(hdc, hEyeBrush);
        Ellipse(hdc, leftEyeX - eyeWidth, eyeY - eyeHeight, leftEyeX + eyeWidth, eyeY + eyeHeight);
        Ellipse(hdc, rightEyeX - eyeWidth, eyeY - eyeHeight, rightEyeX + eyeWidth, eyeY + eyeHeight);
        DeleteObject(hEyeBrush);

        // ����� �׸���
        int wEyeWidth = 3;    // ��� �� ���� ������
        int wEyeHeight = 4;   // ��� �� ���� ������
        int leftWEyeX = 250;
        int rightWEyeX = 450;
        int weyeY = 195;

        HBRUSH hwEyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // �� ���� (���)
        SelectObject(hdc, hwEyeBrush);
        Ellipse(hdc, leftWEyeX - wEyeWidth, weyeY - wEyeHeight, leftWEyeX + wEyeWidth, weyeY + wEyeHeight);
        Ellipse(hdc, rightWEyeX - wEyeWidth, weyeY - wEyeHeight, rightWEyeX + wEyeWidth, weyeY + wEyeHeight);
        DeleteObject(hwEyeBrush);
    }
    // �Լ� �׸���
    int lipLeft = 335;
    int lipRight = 365;
    int lipTop = 250;
    int lipBottom = 300;

    HBRUSH hLipBrush = CreateSolidBrush(RGB(255, 150, 255)); // �Լ� ���� 
    SelectObject(hdc, hLipBrush);
    Ellipse(hdc, lipLeft, lipTop, lipRight, lipBottom);
    DeleteObject(hLipBrush);
    // ��1
    int noseLeft = 300;
    int noseRight = 350;
    int noseTop = 220;
    int noseBottom = 270;

    HBRUSH hnose1Brush = CreateSolidBrush(RGB(255, 255, 255)); // (��1)
    SelectObject(hdc, hnose1Brush);
    Ellipse(hdc, noseLeft, noseTop, noseRight, noseBottom);
    DeleteObject(hnose1Brush);
    // ��2
    int rnoseLeft = 350;
    int rnoseRight = 400;
    int rnoseTop = 220;
    int rnoseBottom = 270;

    HBRUSH hnose2Brush = CreateSolidBrush(RGB(255, 255, 255)); //��2
    SelectObject(hdc, hnose2Brush);
    Ellipse(hdc, rnoseLeft, rnoseTop, rnoseRight, rnoseBottom);
    DeleteObject(hnose2Brush);
    // ��3
    int cnoseLeft = 335;
    int cnoseRight = 365;
    int cnoseTop = 210;
    int cnoseBottom = 240;

    HBRUSH hnose3Brush = CreateSolidBrush(RGB(0, 0, 0)); //��2
    SelectObject(hdc, hnose3Brush);
    Ellipse(hdc, cnoseLeft, cnoseTop, cnoseRight, cnoseBottom);
    DeleteObject(hnose3Brush);
    // ����1
    int startX = 290;
    int startY = 280;
    int endX = 310;
    int endY = 250;

    MoveToEx(hdc, startX, startY, NULL); // ������ �̵�
    LineTo(hdc, endX, endY); // �밢�� �׸���
     // ����2
    int start2X = 275;
    int start2Y = 230;
    int end2X = 310;
    int end2Y = 235;

    MoveToEx(hdc, start2X, start2Y, NULL); // ������ �̵�
    LineTo(hdc, end2X, end2Y); // �밢�� �׸���
     // ����3
    int start3X = 410;
    int start3Y = 275;
    int end3X = 390;
    int end3Y = 250;

    MoveToEx(hdc, start3X, start3Y, NULL); // ������ �̵�
    LineTo(hdc, end3X, end3Y); // �밢�� �׸���
     // ����4
    int start4X = 415;
    int start4Y = 220;
    int end4X = 385;
    int end4Y = 230;

    MoveToEx(hdc, start4X, start4Y, NULL); // ������ �̵�
    LineTo(hdc, end4X, end4Y); // �밢�� �׸���
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    // Calculate the center and radius using the provided parameters
    int centerX = (left + right) / 2;
    int centerY = (top + bottom) / 2;
    int radius = min((right - left) / 2, (bottom - top) / 2);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hBrush);

    int earRadius = radius / 3;

    // Left ear
    int leftearX = centerX - earRadius * 2;
    int leftearY = centerY - earRadius * 2;
    HBRUSH hLeftearBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hLeftearBrush);
    Ellipse(hdc, leftearX - earRadius, leftearY - earRadius, leftearX + earRadius, leftearY + earRadius);
    DeleteObject(hLeftearBrush);

    // Right ear
    int rightearX = centerX - earRadius * -2;
    int rightearY = centerY - earRadius * 2;
    HBRUSH hRIGHTearBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hRIGHTearBrush);
    Ellipse(hdc, rightearX - earRadius, rightearY - earRadius, rightearX + earRadius, rightearY + earRadius);
    DeleteObject(hRIGHTearBrush);

    // Face
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

    // Eyes
    int eyeRadius = radius / 12;

    // Left eye
    int leftEyeX = centerX - eyeRadius * 7;
    int leftEyeY = centerY - eyeRadius;
    HBRUSH hLeftEyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // Black color for left eye
    SelectObject(hdc, hLeftEyeBrush);
    Ellipse(hdc, leftEyeX - eyeRadius, leftEyeY - eyeRadius, leftEyeX + eyeRadius, leftEyeY + eyeRadius);
    DeleteObject(hLeftEyeBrush);

    // Right eye
    int rightEyeX = centerX + eyeRadius * 7;
    int rightEyeY = centerY - eyeRadius;
    HBRUSH hRightEyeBrush = CreateSolidBrush(RGB(0, 0, 0)); // Black color for right eye
    SelectObject(hdc, hRightEyeBrush);
    Ellipse(hdc, rightEyeX - eyeRadius, rightEyeY - eyeRadius, rightEyeX + eyeRadius, rightEyeY + eyeRadius);
    DeleteObject(hRightEyeBrush);

    // Eyebrows
    int eyebrowWidth = radius / 12;
    int eyebrowHeight = radius / 12;

    // Left eyebrows above the eye
    int leftEyebrowStartX = centerX - eyebrowWidth * 8.5;
    int leftEyebrowStartY = centerY - eyebrowHeight * 4;
    int leftEyebrowEndX = leftEyebrowStartX + eyebrowWidth * 3;
    int leftEyebrowEndY = leftEyebrowStartY;

    MoveToEx(hdc, leftEyebrowStartX, leftEyebrowStartY, NULL);
    LineTo(hdc, leftEyebrowEndX, leftEyebrowEndY);

    // Right eyebrows above the eye
    int rightEyebrowStartX = centerX + eyebrowWidth * 6;
    int rightEyebrowStartY = centerY - eyebrowHeight * 4;
    int rightEyebrowEndX = rightEyebrowStartX + eyebrowWidth * 3;
    int rightEyebrowEndY = rightEyebrowStartY;

    MoveToEx(hdc, rightEyebrowStartX, rightEyebrowStartY, NULL);
    LineTo(hdc, rightEyebrowEndX, rightEyebrowEndY);

    // Nose
    int RadiusNose = radius / 6;

    // Left nose
    int leftNoseX = centerX - RadiusNose;
    int leftNoseY = centerY - RadiusNose * (-1);
    HBRUSH hLeftNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hLeftNoseBrush);
    Ellipse(hdc, leftNoseX - RadiusNose, leftNoseY - RadiusNose, leftNoseX + RadiusNose, leftNoseY + RadiusNose);
    DeleteObject(hLeftNoseBrush);

    // Right nose
    int rightNoseX = centerX - RadiusNose * -1;
    int rightNoseY = centerY - RadiusNose * (-1);
    HBRUSH hRightNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hRightNoseBrush);
    Ellipse(hdc, rightNoseX - RadiusNose, rightNoseY - RadiusNose, rightNoseX + RadiusNose, rightNoseY + RadiusNose);
    DeleteObject(hRightNoseBrush);
}
