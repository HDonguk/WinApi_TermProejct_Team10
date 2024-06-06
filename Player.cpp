#include "Player.h"

Player::Player(float x, float y, float speed) : x(x), y(y), speed(speed), currentFrame(0), frameTimeAccumulator(0.0f), moveLeft(false), moveRight(false), moveUp(false), moveDown(false), isMoving(false), boundWidth(0), boundHeight(0) {
    LoadImages();
}

Player::~Player() {
}

void Player::Update(float frameTime) {
    frameTimeAccumulator += frameTime;
    if (frameTimeAccumulator >= 0.1f) {
        if (isMoving) {
            currentFrame = (currentFrame + 1) % 4; // Run �ִϸ��̼��� 4 �������̹Ƿ�
        }
        else {
            currentFrame = (currentFrame + 1) % 5; // Idle �ִϸ��̼��� 5 �������̹Ƿ�
        }
        frameTimeAccumulator = 0.0f;
    }

    isMoving = false;
    if (moveLeft) { Move(-speed, 0); isMoving = true; }
    if (moveRight) { Move(speed, 0); isMoving = true; }
    if (moveUp) { Move(0, -speed); isMoving = true; }
    if (moveDown) { Move(0, speed); isMoving = true; }
}

void Player::Move(float dx, float dy) {
    x += dx;
    y += dy;

    // �÷��̾��� ũ��
    float playerWidth = 32.0f;
    float playerHeight = 32.0f;

    // ��踦 ����� �ʵ��� ��ġ ����
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > boundWidth - playerWidth) x = boundWidth - playerWidth * 2;
    if (y > boundHeight - playerHeight) y = boundHeight - playerHeight * 2;
}

void Player::SetBounds(float width, float height) {
    boundWidth = width;
    boundHeight = height;
}

float Player::GetX() const {
    return x;
}

float Player::GetY() const {
    return y;
}

void Player::LoadImages() {
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

void Player::DrawBoundingBox(HDC hdc, float offsetX, float offsetY) const {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    // �÷��̾��� ũ��
    float playerWidth = 32.0f;
    float playerHeight = 32.0f;

    // Top line
    MoveToEx(hdc, static_cast<int>(x - offsetX), static_cast<int>(y - offsetY), NULL);
    LineTo(hdc, static_cast<int>(x - offsetX + playerWidth), static_cast<int>(y - offsetY));

    // Right line
    LineTo(hdc, static_cast<int>(x - offsetX + playerWidth), static_cast<int>(y - offsetY + playerHeight));

    // Bottom line
    LineTo(hdc, static_cast<int>(x - offsetX), static_cast<int>(y - offsetY + playerHeight));

    // Left line
    LineTo(hdc, static_cast<int>(x - offsetX), static_cast<int>(y - offsetY));

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}