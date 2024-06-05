#include "stdafx.h"
#include "GameFramework.h"

GameFramework::GameFramework() : currentFrame(0), frameTimeAccumulator(0.0f), playerX(100.0f), playerY(100.0f), playerSpeed(0.2f), m_hdcBackBuffer(nullptr), m_hBitmap(nullptr), m_hOldBitmap(nullptr), moveLeft(false), moveRight(false), moveUp(false), moveDown(false), isMoving(false)
{
    Clear();
    LoadImages();
    camera = new Camera(800, 600); // ī�޶� �ʱ�ȭ
}

GameFramework::~GameFramework()
{
    CleanupDoubleBuffering();
    delete camera; // ī�޶� ����
}

void GameFramework::Reset()
{
}

void GameFramework::Clear()
{
}

void GameFramework::Create(HWND hWnd)
{
    m_hWnd = hWnd;
}

void GameFramework::LoadImages()
{
    // ��� �̹��� �ε�
    mapImage.Load(L"./resources/background/background.png");

    // Idle �̹��� �ε�
    idleImages[0].Load(L"./resources/player/Idle_0.png");
    idleImages[1].Load(L"./resources/player/Idle_1.png");
    idleImages[2].Load(L"./resources/player/Idle_2.png");
    idleImages[3].Load(L"./resources/player/Idle_3.png");
    idleImages[4].Load(L"./resources/player/Idle_4.png");

    // Run �̹��� �ε�
    runImages[0].Load(L"./resources/player/Run_0.png");
    runImages[1].Load(L"./resources/player/Run_1.png");
    runImages[2].Load(L"./resources/player/Run_2.png");
    runImages[3].Load(L"./resources/player/Run_3.png");
}

void GameFramework::InitializeDoubleBuffering(HDC hdc)
{
    RECT clientRect;
    GetClientRect(m_hWnd, &clientRect);

    m_hdcBackBuffer = CreateCompatibleDC(hdc);
    m_hBitmap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
    m_hOldBitmap = (HBITMAP)SelectObject(m_hdcBackBuffer, m_hBitmap);
}

void GameFramework::CleanupDoubleBuffering()
{
    if (m_hdcBackBuffer)
    {
        SelectObject(m_hdcBackBuffer, m_hOldBitmap);
        DeleteObject(m_hBitmap);
        DeleteDC(m_hdcBackBuffer);
        m_hdcBackBuffer = nullptr;
    }
}

void GameFramework::Draw(HDC hdc)
{
    if (!m_hdcBackBuffer)
    {
        InitializeDoubleBuffering(hdc);
    }

    RECT clientRect;
    GetClientRect(m_hWnd, &clientRect);

    // �� ���۸� Ŭ����
    FillRect(m_hdcBackBuffer, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

    // ī�޶� �������� ������
    float offsetX = camera->GetOffsetX();
    float offsetY = camera->GetOffsetY();

    // ����� �� ���ۿ� �׸���
    mapImage.Draw(m_hdcBackBuffer, -static_cast<int>(offsetX), -static_cast<int>(offsetY));

    // ���ΰ��� ���� �������� �� ���ۿ� �׸���
    if (isMoving)
    {
        runImages[currentFrame].Draw(m_hdcBackBuffer, static_cast<int>(playerX - offsetX), static_cast<int>(playerY - offsetY));
    }
    else
    {
        idleImages[currentFrame].Draw(m_hdcBackBuffer, static_cast<int>(playerX - offsetX), static_cast<int>(playerY - offsetY));
    }

    // �� ������ ������ ȭ�鿡 ���
    BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, m_hdcBackBuffer, 0, 0, SRCCOPY);
}

void GameFramework::Update(const float frameTime)
{
    frameTimeAccumulator += frameTime;
    if (frameTimeAccumulator >= 0.1f) // 0.1�ʸ��� ������ ��ȯ
    {
        if (isMoving)
        {
            currentFrame = (currentFrame + 1) % 4; // Run �ִϸ��̼��� 4 �������̹Ƿ�
        }
        else
        {
            currentFrame = (currentFrame + 1) % 5; // Idle �ִϸ��̼��� 6 �������̹Ƿ�
        }
        frameTimeAccumulator = 0.0f;
    }

    // �̵� ���¿� ���� ���ΰ� ��ġ ������Ʈ
    isMoving = false;
    if (moveLeft) { MovePlayer(-playerSpeed, 0); isMoving = true; }
    if (moveRight) { MovePlayer(playerSpeed, 0); isMoving = true; }
    if (moveUp) { MovePlayer(0, -playerSpeed); isMoving = true; }
    if (moveDown) { MovePlayer(0, playerSpeed); isMoving = true; }

    // ī�޶� ������Ʈ
    camera->Update(playerX, playerY);
}

void GameFramework::OnKeyBoardProcessing(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_KEYDOWN:
        if (wParam == 'Q')
        {
            SendMessage(m_hWnd, WM_DESTROY, 0, 0);
            return;
        }
        // ����Ű �Է� ó��
        switch (wParam)
        {
        case VK_LEFT:
            moveLeft = true;
            break;
        case VK_RIGHT:
            moveRight = true;
            break;
        case VK_UP:
            moveUp = true;
            break;
        case VK_DOWN:
            moveDown = true;
            break;
        }
        break;

    case WM_KEYUP:
        // ����Ű �Է� ���� ó��
        switch (wParam)
        {
        case VK_LEFT:
            moveLeft = false;
            break;
        case VK_RIGHT:
            moveRight = false;
            break;
        case VK_UP:
            moveUp = false;
            break;
        case VK_DOWN:
            moveDown = false;
            break;
        }
        break;
    }
}

void GameFramework::MovePlayer(float dx, float dy)
{
    playerX += dx;
    playerY += dy;
}
