#include <stdint.h>
#include <vector>

#define PI 3.1415

struct vec3
{
    int a, b, c;
};

struct Face
{
    std::vector<float> vertexIndices;
    std::vector<float> texCoordIndices;
    std::vector<float> normalIndices;

};

struct Mesh
{
    std::vector<float> mVertices;
    std::vector<float> mTexCoords;
    std::vector<float> mNormals;

    Face mFaces;
};

void translateMesh(Mesh* mesh, float x, float y, float z = -40)
{
    //std::cout << "After translation\n";
    float l = 60.f, b = 60.f, h = 20.f;
    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        mesh->mVertices[i] = mesh->mVertices[i] * l + x;
        mesh->mVertices[i + 1] = mesh->mVertices[i + 1] * b + y;
        mesh->mVertices[i + 2] = mesh->mVertices[i + 2] * h + z;

        //std::cout << mesh->mVertices[i] << " " << mesh->mVertices[i+1] << " " << mesh->mVertices[i+2] << "\n";     

    }
}

void cameraTranslation(Mesh* mesh, float x, float y, float z)
{
    //std::cout << "CameraPos translation\n";

    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        mesh->mVertices[i] += x;
        mesh->mVertices[i + 1] += y;
        mesh->mVertices[i + 2] += z;

        //std::cout << mesh->mVertices[i] << " " << mesh->mVertices[i+1] << " " << mesh->mVertices[i+2] << "\n";     

    }
}
void normalizeMesh(Mesh* mesh)
{
    //std::cout << "Normalization\n";
    float near = 0.1, far = 200.f;

    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        mesh->mVertices[i] /= (float)SCREEN_WIDTH;
        mesh->mVertices[i + 1] /= (float)SCREEN_HEIGHT;
        mesh->mVertices[i + 2] /= far;

        //std::cout << mesh->mVertices[i] << " " << mesh->mVertices[i+1] << " " << mesh->mVertices[i+2] << "\n";     

    }
}

void viewTransformMesh(Mesh* mesh, float cameraMat[][N])
{
    //std::cout << "View transformation\n";
    //translateMesh(mesh, -cameraPos.x, -cameraPos.y, -cameraPos.z);
    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        float point[] = { mesh->mVertices[i], mesh->mVertices[i + 1], mesh->mVertices[i + 2], 1.f };
        float temp[N];

        for (int r = 0; r < N; r++)
        {
            float sum = 0;
            for (int c = 0; c < N; c++)
            {
                sum += cameraMat[r][c] * point[c];
            }
            temp[r] = sum;
        }

        mesh->mVertices[i] = temp[0];
        mesh->mVertices[i + 1] = temp[1];
        mesh->mVertices[i + 2] = temp[2];

        //std::cout << temp[0] << " " << temp[1] << " " << temp[2] << "\n";     

    }


}

void rotateMeshY(Mesh* mesh, float angle)
{
    float radian = (PI / 180.f) * angle;
    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        float x, z;
        x = cos(radian) * mesh->mVertices[i] +
            sin(radian) * mesh->mVertices[i + 2];
        z = -sin(radian) * mesh->mVertices[i] +
            cos(radian) * mesh->mVertices[i + 2];
        mesh->mVertices[i] = x;
        mesh->mVertices[i + 2] = z;
    }
}

void rotateMeshZ(Mesh* mesh, float angle)
{
    float radian = (PI / 180.f) * angle;
    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        float x, y;
        x = cos(radian) * mesh->mVertices[i] -
            sin(radian) * mesh->mVertices[i + 1];
        y = sin(radian) * mesh->mVertices[i] +
            cos(radian) * mesh->mVertices[i + 1];
        mesh->mVertices[i] = x;
        mesh->mVertices[i + 1] = y;
    }
}

void rotateMeshX(Mesh* mesh, float angle)
{
    float radian = (PI / 180.f) * angle;
    for (uint32_t i = 0; i < mesh->mVertices.size(); i += 3)
    {
        float y, z;
        y = cos(radian) * mesh->mVertices[i + 1] +
            sin(radian) * mesh->mVertices[i + 2];
        z = -sin(radian) * mesh->mVertices[i + 1] +
            cos(radian) * mesh->mVertices[i + 2];
        mesh->mVertices[i + 1] = y;
        mesh->mVertices[i + 2] = z;
    }
}
