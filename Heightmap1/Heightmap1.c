#include "Heightmap1.h"
#include <time.h>

void initH(Heightmap1 *heightmap, int rows, int columns, int numHills, int hillRadiusMin, int hillRadiusMax, float hillMinHeight, float hillMaxHeight)
{
    createVBOBuff(&heightmap->buffTemp);
    printf("1\n");
    heightmap->rows = rows;
    heightmap->columns = columns;
    heightmap->heighData = malloc(sizeof(float *) * rows);
    for (int i = 0; i < rows; i++)
    {
        heightmap->heighData[i] = malloc(sizeof(float) * columns);
    }
    printf("1\n");
    // srand(time(NULL));
    double sdd = time(NULL);
    // int centerR = IntegerNoise (rows-1);
    // int centerC = IntegerNoise (columns-1);
    // int radius = getNoise(hillRadiusMin,hillRadiusMax,sdd);
    // int height = getNoise(hillMinHeight,hillMaxHeight,sdd);
    // printf("1\n");
    // for (int g = 0; g < numHills; g++)
    // {
    //     /* code */
    //     double hillCenterRow = rand()%(rows-1);
    // 	double hillCenterCol = rand()%(columns-1);
    // 	double hillRadius = getNoise(hillRadiusMin,hillRadiusMax,sdd);
    // 	double hillHeight = getNoise(hillMinHeight,hillMaxHeight,sdd);

    //     for (int i = hillCenterRow - hillRadius; i < hillCenterRow + hillRadius; i++)
    //     {
    //         for (int j = hillCenterCol - hillRadius; j < hillCenterCol + hillRadius; j++)
    //         {
    //             if (i < 0 || i >= rows || j < 0 || j >= columns)
    //             {
    //                 continue;
    //             }
    //             double r2 = hillRadius * hillRadius;
    //             double x21 = hillCenterCol - j;
    //             double y21 = hillCenterRow - i;
    //             double height = (r2 - x21 * x21 - y21 * y21);
    //             if (height < 0.0f)
    //             {
    //                 continue;
    //             }
    //             double factor = (float)height / r2;
    //             heightmap->heighData[i][j] += hillHeight * (factor);

    //             // if(heightmap->heighData[i][j] > NAN){ heightmap->heighData[i][j] = 1.0f;}
    //             // if(heightmap->heighData[i][j] < -NAN){ heightmap->heighData[i][j] = -1.0f;}
    //             // printf("heightmap->heighData[i][j] %f\n",heightmap->heighData[i][j]);
    //         }
    //     }
    // }
    // printf("1\n");
    vec3 **h1dataV = malloc(sizeof(vec3 *) * rows);
    for (int i = 0; i < rows; i++)
    {
        h1dataV[i] = malloc(sizeof(vec3) * columns);
    }
    heightmap->VertObj = malloc(sizeof(vec3) * rows * columns);
    heightmap->ColorObj = malloc(sizeof(vec3) * rows * columns);
    heightmap->NormalsObj = malloc(sizeof(vec3) * rows * columns);
    heightmap->Inds = malloc(sizeof(unsigned int) * 3 * rows * columns);
    int VCount = 0;
    double tq = 0;
    double rrrrrr;

    printf("1\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            float factorRow = (float)i / (rows - 1);
            float factorColumn = (float)j / (columns - 1);
            float vertexHeight = heightmap->heighData[i][j];
            rrrrrr = getImterpolatedNoise((double)j / 10.0f, (double)i / 10.0f, sdd);
            h1dataV[i][j] = (vec3){-0.5f + factorColumn, rrrrrr, -0.5f + factorRow};
            heightmap->ColorObj[VCount] = (vec3){0.1, 0.3, 0.1};
            VCount += 1;
        }
        memcpy(&heightmap->VertObj[i * columns], &h1dataV[i][0], columns * sizeof(vec3));
    }
    vec3 **normalsV = malloc(sizeof(vec3 *) * rows);
    for (int i = 0; i < rows; i++)
    {
        normalsV[i] = malloc(sizeof(vec3) * columns);
    }
    vec3 **tempnormalsV[2];
    for (int i = 0; i < 2; i++)
    {
        tempnormalsV[i] = malloc(sizeof(vec3 *) * rows - 1);
        for (int j = 0; j < rows - 1; j++)
        {
            tempnormalsV[i][j] = malloc(sizeof(vec3) * columns - 1);
        }
    }
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < columns - 1; j++)
        {
            vec3 v1 = h1dataV[i][j];
            vec3 v2 = h1dataV[i][j + 1];
            vec3 v3 = h1dataV[i + 1][j + 1];
            vec3 v4 = h1dataV[i + 1][j];

            // const auto triangleNormalA = glm::cross(vertexB - vertexA, vertexA - vertexD);
            vec3 triangleNormalA = Crossv3(Subv3(v2, v1), Subv3(v1, v4));
            vec3 triangleNormalB = Crossv3(Subv3(v4, v3), Subv3(v3, v2));

            tempnormalsV[0][i][j] = Normalizev3(triangleNormalA);
            tempnormalsV[1][i][j] = Normalizev3(triangleNormalB);
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            // Now we wanna calculate final normal for [i][j] vertex. We will have a look at all triangles this vertex is part of, and then we will make average vector
            // of all adjacent triangles' normals

            int isFirstRow = i == 0;
            int isFirstColumn = j == 0;
            int isLastRow = i == rows - 1;
            int isLastColumn = j == columns - 1;

            vec3 finalVertexNormal = (vec3){0.0f, 0.0f, 0.0f};

            // Look for triangle to the upper-left
            if (!isFirstRow && !isFirstColumn)
            {
                finalVertexNormal = Addv3(finalVertexNormal, tempnormalsV[0][i - 1][j - 1]);
            }

            // Look for triangles to the upper-right
            if (!isFirstRow && !isLastColumn)
            {
                for (int k = 0; k < 2; k++)
                {
                    finalVertexNormal = Addv3(finalVertexNormal, tempnormalsV[k][i - 1][j]);
                }
            }

            // Look for triangle to the bottom-right
            if (!isLastRow && !isLastColumn)
            {
                finalVertexNormal = Addv3(finalVertexNormal, tempnormalsV[0][i][j]);
            }

            // Look for triangles to the bottom-right
            if (!isLastRow && !isFirstColumn)
            {
                for (int k = 0; k < 2; k++)
                {
                    finalVertexNormal = Addv3(finalVertexNormal, tempnormalsV[k][i][j - 1]);
                }
            }

            // Store final normal of j-th vertex in i-th row
            normalsV[i][j] = Normalizev3(finalVertexNormal);
        }
        memcpy(&heightmap->NormalsObj[i * columns], &normalsV[i][0], columns * sizeof(vec3));
    }
    // tempnormalsV[0][1023][1023];
    VCount = 0;
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (int k = 0; k < 2; k++)
            {

                int row = i + k;
                int index = row * columns + j;
                heightmap->Inds[VCount] = index;
                // printf("index %d\n",index);
                VCount += 1;
            }
        }
        heightmap->Inds[VCount] = rows * columns;
        VCount += 1;
    }
    printf("1\n");
    heightmap->sumt = (rows - 1) * (columns) * 2 + (rows - 1);

    heightmap->sumInds = rows * columns;
    printf("1\n");
    loadData(&heightmap->buffTemp, 9, heightmap->sumInds, true, false, true, heightmap->VertObj, heightmap->NormalsObj, NULL, heightmap->ColorObj, true, heightmap->Inds, heightmap->sumt);
    printf("1\n");
    free(heightmap->VertObj);
    free(heightmap->ColorObj);
    free(heightmap->NormalsObj);
    free(heightmap->Inds);
}

void setShader(Heightmap1 *heightmap, ShProgram1 *shader)
{
    heightmap->shaderMain = shader[0];
}

void RenderHeightMap(Heightmap1 *heightmap, mat4 *view, mat4 *proj, int type)
{
    glBindVertexArray(heightmap->buffTemp.VAO);
    useSh(&heightmap->shaderMain);
    SetUniformFloat(0.0f, heightmap->shaderMain.shaderProgram, "time");
    SetUniformInt(type, heightmap->shaderMain.shaderProgram, "type");
    SetUniformMat4(proj, heightmap->shaderMain.shaderProgram, "proj");
    SetUniformMat4(&view[0], heightmap->shaderMain.shaderProgram, "view");
    SetUniformMat4(&heightmap->model, heightmap->shaderMain.shaderProgram, "model");
    mat3 t = Transposedm3(Inversem4((mat3){
        heightmap->model.v[0], heightmap->model.v[1], heightmap->model.v[2],
        heightmap->model.v[4], heightmap->model.v[5], heightmap->model.v[6],
        heightmap->model.v[8], heightmap->model.v[9], heightmap->model.v[10]}));
    SetUniformMat3(&t, heightmap->shaderMain.shaderProgram, "norm");

    // glDrawArrays(GL_TRIANGLES, 0, heightmap->sumInds);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(heightmap->sumInds);

    glDrawElements(GL_TRIANGLE_STRIP, heightmap->sumt, GL_UNSIGNED_INT, 0);
    glDisable(GL_PRIMITIVE_RESTART);
    // glBindVertexArray(0);
}

void SetPosRotScaleH(Heightmap1 *heightmap, vec3 p, float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale)
{
    SetPRS(&heightmap->transform, p, rotateDegree, rotateX, rotateY, rotateZ, scale);
    heightmap->model = GetModel(&heightmap->transform);
}

void closeH(Heightmap1 *heightmap)
{
    // heightmap->rows=rows;
    // heightmap->columns=columns;
    for (int l = 0; l < heightmap->columns; l++)
    {
        free((float *)heightmap->heighData[l]);
        // printf("%d\n",nlinesV);
    }
    free((float **)heightmap->heighData);
    deleteVBOBuff(&heightmap->buffTemp);
    delSh(&heightmap->shaderMain);
}
