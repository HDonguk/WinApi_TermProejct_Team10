#pragma once

#include <atlimage.h> // CImage 사용을 위한 헤더

class GameFramework
{
public:
    GameFramework();
    virtual ~GameFramework();

    void Create(HWND hWnd);
    void Draw(HDC hdc);
    void Update(const float frameTime);
    void OnKeyBoardProcessing(UINT iMessage, WPARAM wParam, LPARAM lParam);
    void Clear();
    void Reset();

private:
    HWND m_hWnd;

    // 더블 버퍼링을 위한 멤버 변수
    HDC m_hdcBackBuffer;
    HBITMAP m_hBitmap;
    HBITMAP m_hOldBitmap;

    // 배경 이미지
    CImage mapImage;

    // 주인공 이미지 배열
    CImage idleImages[10];
    CImage runImages[8];
    int currentFrame;
    float frameTimeAccumulator;

    float playerX, playerY; // 주인공의 위치
    float playerSpeed; // 주인공의 이동 속도

    bool moveLeft, moveRight, moveUp, moveDown; // 이동 상태
    bool isMoving; // 주인공이 움직이고 있는지 여부

    void LoadImages();
    void MovePlayer(float dx, float dy); // 주인공 이동 함수
    void InitializeDoubleBuffering(HDC hdc);
    void CleanupDoubleBuffering();
};
