#include "stdafx.h"
#include "GameFramework.h"

GameFramework::GameFramework() : m_hdcBackBuffer(nullptr), m_hBitmap(nullptr), m_hOldBitmap(nullptr), player(nullptr), camera(nullptr), showClickImage(false), clickImageTimer(0.0f) {
    Clear();

    // ��� �̹��� �ε�
    mapImage.Load(L"./resources/background/background.png");

    // ��� �̹��� ũ�� ��������
    int mapWidth = mapImage.GetWidth();
    int mapHeight = mapImage.GetHeight();

    // �÷��̾ ����� ���߾ӿ� ��ġ
    player = new Player(mapWidth / 2.0f, mapHeight / 2.0f, 0.2f, 5.0f); // ������ �Ķ���Ͱ�, �ִϸ��̼� �ӵ�.
    player->SetBounds(mapWidth, mapHeight); // �÷��̾� ��� ����

    // ī�޶� �ʱ�ȭ
    camera = new Camera(800, 600);
    camera->SetBounds(mapWidth, mapHeight); // ī�޶� ��� ����

    // Ŀ�� �̹��� �ε�
    cursorImage.Load(L"./resources/ui/icon_TakeAim.png");
    clickImage.Load(L"./resources/ui/T_CursorSprite.png");
}

GameFramework::~GameFramework() {
    CleanupDoubleBuffering();
    delete camera;
    delete player; // �÷��̾� ����
}

void GameFramework::Update(const float frameTime) {
    player->Update(frameTime); // �÷��̾� ������Ʈ
    camera->Update(player->GetX(), player->GetY()); // �÷��̾� ��ġ�� ī�޶� ������Ʈ

    if (showClickImage) {
        clickImageTimer -= frameTime;
        if (clickImageTimer <= 0.0f) {
            showClickImage = false;
        }
    }
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
    player->Draw(m_hdcBackBuffer, offsetX, offsetY);

    // �÷��̾��� �ٿ�� �ڽ� �׸���
    player->DrawBoundingBox(m_hdcBackBuffer, offsetX, offsetY);

    // ���콺 Ŀ�� �̹��� �׸���
    int cursorWidth = cursorImage.GetWidth();
    int cursorHeight = cursorImage.GetHeight();
    int clickWidth = clickImage.GetWidth();
    int clickHeight = clickImage.GetHeight();

    if (showClickImage) {
        clickImage.Draw(m_hdcBackBuffer, cursorPos.x - clickWidth / 2, cursorPos.y - clickHeight / 2);
    }
    else {
        cursorImage.Draw(m_hdcBackBuffer, cursorPos.x - cursorWidth / 2, cursorPos.y - cursorHeight / 2);
    }

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
        case 'A':
        case 'a':
            player->moveLeft = true;
            player->SetDirectionLeft(true); // �������� �̵� �� ���� ����
            break;
        case 'D':
        case 'd':
            player->moveRight = true;
            player->SetDirectionLeft(false); // ���������� �̵� �� ���� ����
            break;
        case 'W':
        case 'w':
            player->moveUp = true;
            break;
        case 'S':
        case 's':
            player->moveDown = true;
            break;
        }
        break;

    case WM_KEYUP:
        switch (wParam) {
        case 'A':
        case 'a':
            player->moveLeft = false;
            break;
        case 'D':
        case 'd':
            player->moveRight = false;
            break;
        case 'W':
        case 'w':
            player->moveUp = false;
            break;
        case 'S':
        case 's':
            player->moveDown = false;
            break;
        }
        break;
    }
}

void GameFramework::OnMouseProcessing(UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage) {
    case WM_MOUSEMOVE:
        cursorPos.x = LOWORD(lParam);
        cursorPos.y = HIWORD(lParam);
        break;

    case WM_LBUTTONDOWN:
        showClickImage = true;
        clickImageTimer = 0.2f; // Ŭ�� �̹��� ǥ�� �ð�
        cursorPos.x = LOWORD(lParam);
        cursorPos.y = HIWORD(lParam);
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