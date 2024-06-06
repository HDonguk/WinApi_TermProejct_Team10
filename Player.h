#pragma once
#include <atlimage.h> // CImage ����� ���� ���

class Player {
public:
    Player(float x, float y, float speed);
    ~Player();

    void Update(float frameTime);
    void Move(float dx, float dy);

    float GetX() const;
    float GetY() const;

    void SetBounds(float width, float height); // ��踦 �����ϴ� �޼��� �߰�
    void DrawBoundingBox(HDC hdc, float offsetX, float offsetY) const;

    float x, y;
    float speed;
    int currentFrame;
    float frameTimeAccumulator;
    bool moveLeft, moveRight, moveUp, moveDown;
    bool isMoving;

    float boundWidth, boundHeight; // ��踦 ���� ����

    // �÷��̾� �̹��� �ε� �޼����
    void LoadImages();
    // �÷��̾� ���¿� ���� �̹��� �迭
    CImage idleImages[5];
    CImage runImages[4];
};
