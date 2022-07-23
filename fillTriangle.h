#include <algorithm>

float zbuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

bool edgeFunc(const vec& p, const vec& t)
{
    return ((p.x * t.y - p.y * t.x) >= 0);
}

float edgeFunc(const vec& a, const vec& b, const vec& c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}


int num = 0;
int color[] = { 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 0,
                0, 255, 255 };

int orientation(vec p1, vec p2, vec p3)
{
    int val = (p2.y - p1.y) * (p3.x - p2.x)
        - (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0)
        return 0; // collinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}



int tcounter = 0;
void rasterize(vec up0, vec up1, vec up2)
{
    float start = SDL_GetTicks();
    up0.y = SCREEN_HEIGHT - up0.y;
    up1.y = SCREEN_HEIGHT - up1.y;
    up2.y = SCREEN_HEIGHT - up2.y;

    int order = orientation(up0, up1, up2);
    vec p0 = up0, p1 = up1, p2 = up2;
    if (order == 2)
    {
       
        p0 = up2; p1 = up1; p2 = up0;
    }

    float area = abs(edgeFunc(p0, p1, p2));

    //std::cout << "area = " << area << std::endl;

    //SDL_RenderClear(gRenderer);
    //num = num % 18;
    //SDL_SetRenderDrawColor(gRenderer, color[num], color[num + 1], color[num + 2], 0xFF);

    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0xFF);

    int xrange[2], yrange[2];
    xrange[0] = std::min({ p0.x, p1.x, p2.x });
    xrange[1] = std::max({ p0.x, p1.x, p2.x });
    yrange[0] = std::min({ p0.y, p1.y, p2.y });
    yrange[1] = std::max({ p0.y, p1.y, p2.y });

    xrange[1] += (8 - (xrange[1] - xrange[0]) % 8);

    //Check for boundary
    xrange[0] = xrange[0] < 0 ? 0 : xrange[0];
    xrange[1] = xrange[1] >= SCREEN_WIDTH ? SCREEN_WIDTH - 8 : xrange[1];
    yrange[0] = yrange[0] < 0 ? 0 : yrange[0];
    yrange[1] = yrange[1] >= SCREEN_HEIGHT ? SCREEN_HEIGHT : yrange[1];


    // SDL_Rect fillRect = {xrange[0], yrange[0], xrange[1]-xrange[0], yrange[1]-yrange[0]};
    // SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);

    //SDL_SetRenderDrawColor(gRenderer, 0xFF, 0, 0, 0xFF);

    vec V01, V12, V20;
    V01 = { p1.x - p0.x, p1.y - p0.y };
    V12 = { p2.x - p1.x, p2.y - p1.y };
    V20 = { p0.x - p2.x, p0.y - p2.y };


    int counter = 0;
    bool print = true;

    for (int i = yrange[0]; i <= yrange[1]; i++)
    {
        //float start = SDL_GetTicks();

        for (int j = xrange[0]; j <= xrange[1]; j += 1)
        {


            vec V0P, V1P, V2P;
            V0P = { j - p0.x, i - p0.y };
            V1P = { j - p1.x, i - p1.y };
            V2P = { j - p2.x, i - p2.y };

            bool inside = true;
            inside &= edgeFunc(V0P, V01);
            inside &= edgeFunc(V1P, V12);
            inside &= edgeFunc(V2P, V20);

            // //std::cout << inside << std::endl;
            if (inside == true)
            {
                vec p = { j, i };
                float w0 = edgeFunc(p1, p2, p);
                float w1 = edgeFunc(p2, p0, p);
                float w2 = edgeFunc(p0, p1, p);

                w0 /= (float)area;
                w1 /= (float)area;
                w2 /= (float)area;

                float invZ = (w0) / p0.z + (w1) / p1.z + (w2) / p2.z;
                invZ = (1 / invZ);
                if (zbuffer[i][j] > invZ)
                {
                    zbuffer[i][j] = invZ;
                    SDL_RenderDrawPoint(gRenderer, j, i);

                }
            }
        }

        print = false;
        //float end = SDL_GetTicks();

        //std::cout << end - start << std::endl;

    }

    num++;
    tcounter++;
    //SDL_RenderPresent(gRenderer);
    //std::cout << "Counter = " << counter << std::endl;

    float end = SDL_GetTicks();

    // std::cout << "Rasterize time = " << end - start << std::endl;
}
