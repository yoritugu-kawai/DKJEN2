#pragma once
#include"../DKJEN/DKJEN/Math/Math.h"
class ABB {
public:
    // AABBの中心座標
    Vector3 center;
    // AABBのサイズ（幅、高さ、奥行き）
    Vector3 size;

    // コンストラクタ
    //ABB(const Vector3& center = {}, const Vector3& size = {}) : center(center), size(size) {}

    // AABB同士の衝突判定
    static bool CheckCollision(const ABB& obj1, const ABB& obj2);
};