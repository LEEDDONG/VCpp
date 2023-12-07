#include "yuhanCG.h"

 
void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    int faceLeft = 220;
    int faceTop = 100;
    int faceRight = 480;
    int faceBottom = 350;
    // 얼굴 영역을 그리기
    HBRUSH hFaceBrush = CreateSolidBrush(RGB(127, 200, 255)); // 흰색 얼굴
    SelectObject(hdc, hFaceBrush);
    Ellipse(hdc, faceLeft, faceTop, faceRight, faceBottom);
    DeleteObject(hFaceBrush);
    if (blink) {
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

    HBRUSH hLipBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입술 색상 
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

    int eyebrowWidth2 = radius / 12;
    int eyebrowHeight2 = radius / 12;

    // Left eyebrows above the eye
    int leftEyebrowStartX2 = centerX - eyebrowWidth2 * 8.5;
    int leftEyebrowStartY2 = centerY - eyebrowHeight2 * 4.2;
    int leftEyebrowEndX2 = leftEyebrowStartX2 + eyebrowWidth2 * 3;
    int leftEyebrowEndY2 = leftEyebrowStartY2;

    MoveToEx(hdc, leftEyebrowStartX2, leftEyebrowStartY2, NULL);
    LineTo(hdc, leftEyebrowEndX2, leftEyebrowEndY2);

    int eyebrowWidth3 = radius / 12;
    int eyebrowHeight3 = radius / 12;

    // Left eyebrows above the eye
    int leftEyebrowStartX3 = centerX - eyebrowWidth3 * 8.5;
    int leftEyebrowStartY3 = centerY - eyebrowHeight3 * 4.4;
    int leftEyebrowEndX3 = leftEyebrowStartX3 + eyebrowWidth3 * 3;
    int leftEyebrowEndY3 = leftEyebrowStartY3;

    MoveToEx(hdc, leftEyebrowStartX3, leftEyebrowStartY3, NULL);
    LineTo(hdc, leftEyebrowEndX3, leftEyebrowEndY3);


    // Right eyebrows above the eye
    int rightEyebrowStartX = centerX + eyebrowWidth * 6;
    int rightEyebrowStartY = centerY - eyebrowHeight * 4;
    int rightEyebrowEndX = rightEyebrowStartX + eyebrowWidth * 3;
    int rightEyebrowEndY = rightEyebrowStartY;

    MoveToEx(hdc, rightEyebrowStartX, rightEyebrowStartY, NULL);
    LineTo(hdc, rightEyebrowEndX, rightEyebrowEndY);
    // Right eyebrows above the eye
    int rightEyebrowStartX2 = centerX + eyebrowWidth2 * 6;
    int rightEyebrowStartY2 = centerY - eyebrowHeight2 * 4.2;
    int rightEyebrowEndX2 = rightEyebrowStartX2 + eyebrowWidth2 * 3;
    int rightEyebrowEndY2 = rightEyebrowStartY2;

    MoveToEx(hdc, rightEyebrowStartX2, rightEyebrowStartY2, NULL);
    LineTo(hdc, rightEyebrowEndX2, rightEyebrowEndY2);

    // Right eyebrows above the eye
    int rightEyebrowStartX3 = centerX + eyebrowWidth3 * 6;
    int rightEyebrowStartY3 = centerY - eyebrowHeight3 * 4.4;
    int rightEyebrowEndX3 = rightEyebrowStartX3 + eyebrowWidth3 * 3;
    int rightEyebrowEndY3 = rightEyebrowStartY3;

    MoveToEx(hdc, rightEyebrowStartX3, rightEyebrowStartY3, NULL);
    LineTo(hdc, rightEyebrowEndX3, rightEyebrowEndY3);


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

void DrawBox(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
  
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0,0));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, left,top,right,bottom);
}

void DrawCircle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
   

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0,0));
    SelectObject(hdc, hBrush);
    // Face
    Ellipse(hdc, left,top,right,bottom);

}
void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    // Set the color for drawing the cube
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));  // Blue color for lines
    SelectObject(hdc, hPen);

    // Calculate cube coordinates
    int frontLeftTopX = left;
    int frontLeftTopY = top;
    int frontRightTopX = right;
    int frontRightTopY = top;
    int frontLeftBottomX = left;
    int frontLeftBottomY = bottom;
    int frontRightBottomX = right;
    int frontRightBottomY = bottom;

    int backLeftTopX = left - 50;  // Adjust as needed
    int backLeftTopY = top - 50;   // Adjust as needed
    int backRightTopX = right - 50; // Adjust as needed
    int backRightTopY = top - 50;   // Adjust as needed
    int backLeftBottomX = left - 50; // Adjust as needed
    int backLeftBottomY = bottom - 50; // Adjust as needed
    int backRightBottomX = right - 50; // Adjust as needed
    int backRightBottomY = bottom - 50; // Adjust as needed

    // Draw the front face of the cube
    MoveToEx(hdc, frontLeftTopX, frontLeftTopY, NULL);
    LineTo(hdc, frontRightTopX, frontRightTopY);
    LineTo(hdc, frontRightBottomX, frontRightBottomY);
    LineTo(hdc, frontLeftBottomX, frontLeftBottomY);
    LineTo(hdc, frontLeftTopX, frontLeftTopY);

    // Draw the lines connecting the front and back faces
    MoveToEx(hdc, frontLeftTopX, frontLeftTopY, NULL);
    LineTo(hdc, backLeftTopX, backLeftTopY);

    MoveToEx(hdc, frontRightTopX, frontRightTopY, NULL);
    LineTo(hdc, backRightTopX, backRightTopY);

    MoveToEx(hdc, frontRightBottomX, frontRightBottomY, NULL);
    LineTo(hdc, backRightBottomX, backRightBottomY);

    MoveToEx(hdc, frontLeftBottomX, frontLeftBottomY, NULL);
    LineTo(hdc, backLeftBottomX, backLeftBottomY);

    // Draw the back face of the cube
    MoveToEx(hdc, backLeftTopX, backLeftTopY, NULL);
    LineTo(hdc, backRightTopX, backRightTopY);
    LineTo(hdc, backRightBottomX, backRightBottomY);
    LineTo(hdc, backLeftBottomX, backLeftBottomY);
    LineTo(hdc, backLeftTopX, backLeftTopY);

    // Delete the pen
    DeleteObject(hPen);
}