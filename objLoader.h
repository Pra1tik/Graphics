#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
// #include <iostream>


void loadFromFile(const char* fileName, Mesh* mesh)
{

    // Mesh mesh;

    FILE* fp = fopen(fileName, "r");
    size_t len = 255;
    char* line = (char*)malloc(sizeof(char) * len);
    if (fp == NULL) {
        printf("can't open");
        return;
    }

    while (fgets(line, len, fp) != NULL) {

        char* token;

        token = strtok(line, " ");


        if (strcmp(token, "v") == 0)
        {
            token = strtok(NULL, " ");

            while (token != NULL)
            {
                //printf( "%s\n", token );
                mesh->mVertices.push_back(atof(token));
                token = strtok(NULL, " ");
            }
        }
        else if (strcmp(token, "vt") == 0)
        {
            token = strtok(NULL, " ");

            while (token != NULL)
            {
                mesh->mTexCoords.push_back(atof(token));
                token = strtok(NULL, " ");
            }
        }
        else if (strcmp(token, "vn") == 0)
        {
            token = strtok(NULL, " ");

            while (token != NULL)
            {
                mesh->mNormals.push_back(atof(token));
                token = strtok(NULL, " ");
            }
        }
        else if (strcmp(token, "f") == 0)
        {
            vec3 v, t, n;

            token = strtok(NULL, " /");
            v.a = atoi(token);
            token = strtok(NULL, " /");
            t.a = atoi(token);
            token = strtok(NULL, " /");
            n.a = atoi(token);

            token = strtok(NULL, " /");
            v.b = atoi(token);
            token = strtok(NULL, " /");
            t.b = atoi(token);
            token = strtok(NULL, " /");
            n.b = atoi(token);

            token = strtok(NULL, " /");
            v.c = atoi(token);
            token = strtok(NULL, " /");
            t.c = atoi(token);
            token = strtok(NULL, " /");
            n.c = atoi(token);

            mesh->mFaces.vertexIndices.push_back(v.a);
            mesh->mFaces.vertexIndices.push_back(v.b);
            mesh->mFaces.vertexIndices.push_back(v.c);

            mesh->mFaces.texCoordIndices.push_back(t.a);
            mesh->mFaces.texCoordIndices.push_back(t.b);
            mesh->mFaces.texCoordIndices.push_back(t.c);

            mesh->mFaces.normalIndices.push_back(n.a);
            mesh->mFaces.normalIndices.push_back(n.b);
            mesh->mFaces.normalIndices.push_back(n.c);


        }
    }

    free(line);
    fclose(fp);
}

