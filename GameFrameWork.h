#pragma once

#include <windows.h>
#include <atlimage.h> // CImage 사용을 위한 헤더
#include "Player.h"
#include "Camera.h"
#include "Gun.h"
#include "Enemy.h"
#include <vector>

class GameFramework {
public:
    GameFramework();
    ~GameFramework();

    void Create(HWND hWnd);
    void Update(float frameTime);
    void Draw(HDC hdc);
    void OnKeyBoardProcessing(UINT iMessage, WPARAM wParam, LPARAM lParam);
    void OnMouseProcessing(UINT iMessage, WPARAM wParam, LPARAM lParam);
    void CreateEnemies(); // 적 객체 생성 메서드 추가
    void Clear();

private:
    void InitializeDoubleBuffering(HDC hdc);
    void CleanupDoubleBuffering();
    void SpawnEnemy(); // 주기적으로 적을 생성하는 메서드 추가

    HWND m_hWnd;
    HDC m_hdcBackBuffer;
    HBITMAP m_hBitmap;
    HBITMAP m_hOldBitmap;

    CImage mapImage;
    Player* player;
    Camera* camera;
    Gun gun; // Regular object

    CImage cursorImage;
    CImage clickImage;
    bool showClickImage;
    float clickImageTimer;
    POINT cursorPos;

    std::vector<Enemy*> enemies; // 적 객체 벡터 추가

    float enemySpawnTimer; // 적 생성 타이머
    const float enemySpawnInterval = 1.0f; // 적 생성 간격 (초)
};
