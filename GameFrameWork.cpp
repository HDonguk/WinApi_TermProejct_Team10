#include "stdafx.h"
#include "GameFramework.h"

GameFramework::GameFramework() : m_hdcBackBuffer(nullptr), m_hBitmap(nullptr), m_hOldBitmap(nullptr), player(nullptr), camera(nullptr) {
    Clear();

    // ��� �̹��� �ε�
    mapImage.Load(L"./resources/background/background.png");

    // ��� �̹��� ũ�� ��������
    int mapWidth = mapImage.GetWidth();
    int mapHeight = mapImage.GetHeight();

    // �÷��̾ ����� ���߾ӿ� ��ġ
    player = new Player(mapWidth / 2.0f, mapHeight / 2.0f, 0.2f);
    player->SetBounds(mapWidth, mapHeight); // �÷��̾� ��� ����

    // ī�޶� �ʱ�ȭ
    camera = new Camera(800, 600);
    camera->SetBounds(mapWidth, mapHeight); // ī�޶� ��� ����
}

GameFramework::~GameFramework() {
    CleanupDoubleBuffering();
    delete camera;
    delete player; // �÷��̾� ����
}

void GameFramework::Update(const float frameTime) {
    player->Update(frameTime); // �÷��̾� ������Ʈ
    camera->Update(player->GetX(), player->GetY()); // �÷��̾� ��ġ�� ī�޶� ������Ʈ
}

void GameFramework::Draw(HDC hdc) {
    if (!m_hdcBackBuffer) {
        InitializeDoubleBuffering(hdc);
    }

    RECT clientRect;
    GetClientRect(m_hWnd, &clientRect);

    FillRect(m_hdcBackBuffer, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

    float offsetX = camera->GetOffsetX();
    float offsetY = camera->GetOffsetY();

    mapImage.Draw(m_hdcBackBuffer, -static_cast<int>(offsetX), -static_cast<int>(offsetY));

    // ���ΰ��� ���� �������� �� ���ۿ� �׸���
    if (player->isMoving) {
        if (player->runImages[player->currentFrame].IsNull() == FALSE) {
            player->runImages[player->currentFrame].Draw(m_hdcBackBuffer, static_cast<int>(player->GetX() - offsetX), static_cast<int>(player->GetY() - offsetY));
        }
    }
    else {
        if (player->idleImages[player->currentFrame].IsNull() == FALSE) {
            player->idleImages[player->currentFrame].Draw(m_hdcBackBuffer, static_cast<int>(player->GetX() - offsetX), static_cast<int>(player->GetY() - offsetY));
        }
    }

    // �÷��̾��� �ٿ�� �ڽ� �׸���
    player->DrawBoundingBox(m_hdcBackBuffer, offsetX, offsetY);

    BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, m_hdcBackBuffer, 0, 0, SRCCOPY);
}


void GameFramework::OnKeyBoardProcessing(UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage) {
    case WM_KEYDOWN:
        if (wParam == 'Q') {
            SendMessage(m_hWnd, WM_DESTROY, 0, 0);
            return;
        }
        switch (wParam) {
        case VK_LEFT:
            player->moveLeft = true;
            break;
        case VK_RIGHT:
            player->moveRight = true;
            break;
        case VK_UP:
            player->moveUp = true;
            break;
        case VK_DOWN:
            player->moveDown = true;
            break;
        }
        break;

    case WM_KEYUP:
        switch (wParam) {
        case VK_LEFT:
            player->moveLeft = false;
            break;
        case VK_RIGHT:
            player->moveRight = false;
            break;
        case VK_UP:
            player->moveUp = false;
            break;
        case VK_DOWN:
            player->moveDown = false;
            break;
        }
        break;
    }
}

void GameFramework::InitializeDoubleBuffering(HDC hdc) {
    RECT clientRect;
    GetClientRect(m_hWnd, &clientRect);

    m_hdcBackBuffer = CreateCompatibleDC(hdc);
    m_hBitmap = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
    m_hOldBitmap = (HBITMAP)SelectObject(m_hdcBackBuffer, m_hBitmap);
}

void GameFramework::CleanupDoubleBuffering() {
    if (m_hdcBackBuffer) {
        SelectObject(m_hdcBackBuffer, m_hOldBitmap);
        DeleteObject(m_hBitmap);
        DeleteDC(m_hdcBackBuffer);
        m_hdcBackBuffer = nullptr;
    }
}

void GameFramework::Clear() {
    // Clear �޼��� ����
}

void GameFramework::Create(HWND hWnd) {
    m_hWnd = hWnd;
}
