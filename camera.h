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

float dot(const vec& a, const vec& b)
{
    return (a.x * b.x + a.y * b.y * a.z * b.z);
}

vec cameraPos = { 0.f, 0.f, 3.f };
vec cameraTarget = { 0.f, 0.f, 0.f };
vec cameraDirection = subAndnormalize(cameraTarget, cameraPos);
vec cameraUp = { 0.f, 1.f, 0.f };
vec cameraRight = normalizeVec(crossProduct(cameraUp, cameraDirection));
vec cameraFront = { 0.f, 0.f, -1.f };
//cameraPos + camreaFront

//W press
float cameraSpeed = 0.2f;

void cameraMatrix(float a[][4], const vec& eye, const vec& center, const vec& up)
{
    vec temp = { center.x - eye.x, center.y - eye.y, center.z - eye.z };
    vec f = (normalizeVec(temp));
    vec s = (normalizeVec(crossProduct(f, up)));
    vec u = (crossProduct(s, f));

    a[0][0] = s.x;
    a[1][0] = s.y;
    a[2][0] = s.z;
    a[0][1] = u.x;
    a[1][1] = u.y;
    a[2][1] = u.z;
    a[0][2] = -f.x;
    a[1][2] = -f.y;
    a[2][2] = -f.z;
    a[3][0] = -dot(s, eye);
    a[3][1] = -dot(u, eye);
    a[3][2] = dot(f, eye);
    a[3][3] = 1;

}
