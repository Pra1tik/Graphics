#pragma once
#pragma once
#include <cmath>

struct vec
{
    float x, y, z;
};

vec normalizeVec(vec v)
{
    float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vec r = { v.x / magnitude, v.y / magnitude, v.z / magnitude };
    return r;
}

vec subAndnormalize(vec v1, vec v2)
{
    vec v = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
    float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vec r = { v.x / magnitude, v.y / magnitude, v.z / magnitude };
    return r;
}

vec crossProduct(vec a, vec b)
{
    vec r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = -(a.x * b.z - a.z * b.x);
    r.z = a.x * b.y - b.x * a.y;
    return r;
}

vec addVec(vec a, vec b)
{
    vec res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return res;
}

vec subVec(vec a, vec b)
{
    vec res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return res;
}

vec scalarMulVec(float k, vec a)
{
    vec res;
    res.x = k * a.x;
    res.y = k * a.y;
    res.z = k * a.z;
    return res;
}

vec cameraPos = { 0.f, 0.f, 3.f };
vec cameraTarget = { 0.f, 0.f, 0.f };
vec cameraDirection = subAndnormalize(cameraTarget, cameraPos);
vec cameraUp = { 0.f, 1.f, 0.f };
vec cameraRight = normalizeVec(crossProduct(cameraUp, cameraDirection));
vec cameraFront = { 0.f, 0.f, -1.f };
//cameraPos + camreaFront

//W press
float cameraSpeed = 0.5f;

void cameraMatrix(float a[][4])
{
    a[0][0] = cameraRight.x;
    a[0][1] = cameraRight.y;
    a[0][2] = cameraRight.z;

    a[1][0] = cameraUp.x;
    a[1][1] = cameraUp.y;
    a[1][2] = cameraUp.z;

    a[2][0] = cameraDirection.x;
    a[2][1] = cameraDirection.y;
    a[2][2] = cameraDirection.z;

    a[3][3] = 1;
}
