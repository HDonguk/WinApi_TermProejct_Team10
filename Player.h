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

    // �÷��̾� �̹��� �ε� �޼����
    void LoadImages();
    void Draw(HDC hdc, float offsetX, float offsetY);

    // ������ �����ϱ� ���� �޼���
    void SetDirectionLeft(bool isLeft);
    bool IsDirectionLeft() const;

    float x, y;
    float speed;
    int currentFrame;
    float frameTimeAccumulator;
    bool moveLeft, moveRight, moveUp, moveDown;
    bool isMoving;
    bool directionLeft; // ���� �÷��� �߰�

    float boundWidth, boundHeight; // ��踦 ���� ����

    // �÷��̾� ���¿� ���� �̹��� �迭
    CImage idleImages[5];
    CImage runImages[4];
    CImage r_idleImages[5];
    CImage r_runImages[4];
};
