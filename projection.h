#include <stdint.h>
#include <vector>

struct argList
{
    Mesh* m;
    float(*projMat)[4];
    int index;
};

#define epsilon 0.1

void projectMesh(Mesh* mesh, const float projMat[][N])
{
    SDL_SetRenderTarget(gRenderer, gTexture);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    int start = 0, end = mesh->mVertices.size();
   

    //start = 0; end = mesh->mVertices.size();
    bool set = true;
    int counter = 0;
    //std::cout << "mesh size = " << mesh->mVertices.size() << std::endl;

    for (uint32_t i = 0; i < mesh->mFaces.vertexIndices.size(); i += 3)
    {
        uint32_t f1 = mesh->mFaces.vertexIndices[i] - 1;
        uint32_t f2 = mesh->mFaces.vertexIndices[i + 1] - 1;
        uint32_t f3 = mesh->mFaces.vertexIndices[i + 2] - 1;


        float points[][4] = { {mesh->mVertices[f1*3], mesh->mVertices[f1*3 + 1], mesh->mVertices[f1*3 + 2], 1.f},
                            {mesh->mVertices[f2*3], mesh->mVertices[f2*3 + 1], mesh->mVertices[f2*3 + 2], 1.f},
                            {mesh->mVertices[f3*3], mesh->mVertices[f3*3 + 1], mesh->mVertices[f3*3 + 2], 1.f} };


        float projPoints[3][4];

        for (int r = 0; r < 3; r++)
        {
            for (int i = 0; i < 4; i++)
            {
                float res = 0.f;
                for (int k = 0; k < 4; k++)
                {
                    res += projMat[i][k] * points[r][k];
                }
                projPoints[r][i] = res;
            }
        }

        //Clipping       
        // w = 0 clip

        //Check if whole traingle is behind or infront of camera
        float d1 = projPoints[0][3];
        float d2 = projPoints[1][3];
        float d3 = projPoints[2][3];

        if (d1 <= epsilon && d2 <= epsilon && d3 <= epsilon)
        {
            //std::cout << "Triangle Fully removed\n";
            continue;
        }

        //if(d1 > epsilon && d2 > epsilon && d3 > epsilon)
        {

            for (int j = 0; j < 3; j++)
            {
                //w divide
                projPoints[j][0] /= projPoints[j][3];
                projPoints[j][1] /= projPoints[j][3];
                projPoints[j][2] /= projPoints[j][3];

                //To [0, 1] 
                projPoints[j][0] = (projPoints[j][0] + 1.f) / 2.f;
                projPoints[j][1] = (projPoints[j][1] + 1.f) / 2.f;

                //To screen coordinates
                projPoints[j][0] *= SCREEN_WIDTH;
                projPoints[j][1] *= SCREEN_HEIGHT;

            }

            //Rasterize
            vec p0 = { projPoints[0][0], projPoints[0][1], projPoints[0][2] };
            vec p1 = { projPoints[1][0], projPoints[1][1], projPoints[1][2] };
            vec p2 = { projPoints[2][0], projPoints[2][1], projPoints[2][2] };
            
            //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
            //SDL_RenderDrawLine(gRenderer, p0.x, p0.y, p1.x, p1.y);
            //SDL_RenderDrawLine(gRenderer, p2.x, p2.y, p1.x, p1.y);
            //SDL_RenderDrawLine(gRenderer, p0.x, p0.y, p2.x, p2.y);
            //SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
             
            //std::cout << p0.x << " " << p0.y << " ";
            //std::cout << p1.x << " " << p1.y << " ";
            //std::cout << p2.x << " " << p2.y << "\n";
            rasterize(p0, p1, p2);
            //break;
        }

       
    }


    SDL_SetRenderTarget(gRenderer, NULL);
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    //std::cout << "NO of triangles = " << tcounter << "\n";

    //return 0;
}

void proj(float projMat[][4])
{
    float l, r, n = 0.1, f = 100.f;
    float aspectRatio, FOV, t, b;
    float angle = 90.f;

    FOV = angle;
    aspectRatio = SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    t = tanf(FOV / 2.f) * n;
    b = -t;
    r = t * aspectRatio;
    l = -r;

    //float projMat[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            projMat[i][j] = 0;
        }
    }


    projMat[0][0] = (2 * n) / (r - l);
    projMat[0][2] = (r + l) / (r - l);
    projMat[1][1] = (2 * n) / (t - b);
    projMat[1][2] = (t + b) / (t - b);
    projMat[2][2] = -(f + n) / (f - n);
    projMat[2][3] = -(2 * f * n) / (f - n);
    projMat[3][2] = -1.f;

    //projMat[0][0] = 1/ (aspectRatio*t);
    //projMat[1][1] = 1/t;
    //projMat[2][2] = (f) / (f - n);
    //projMat[2][3] = 1;
    //projMat[3][2] = f*n/(f-n);

    // for(int i = 0; i < 4; i++)
    // {
    //     for(int j = 0; j < 4; j++)
    //     {
    //         std::cout << projMat[i][j] << " ";
    //     }

    //     std::cout << std::endl;
    // }

}