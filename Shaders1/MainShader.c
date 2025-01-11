#include "MainShader.h"


void testOpenFile(MainShader *mShader,char *p,const char **FileMain,int *countL1)
{
    FILE *file1 = fopen(&p[0], "r");
    char line1[256];
    int countL=countL1[0];
    // countL++;
    if (file1 != NULL)
    {
        while (fgets(line1, sizeof(line1), file1)){

            if (strncmp(line1,"include ",8)!=0)
            {
                // fputs(line1, nameFile);
                FileMain[countL]=malloc(sizeof(const char)*256);
                strcpy(FileMain[countL], line1);
                countL++;
                // fputs("\n", nameFile);
            }
            if (strncmp(line1,"include ",8)==0)
            {
                // printf("%s", &line1[8]);
            }
        }
    }
    countL1[0]=countL;
    fclose(file1);
}

void openMainFiles(MainShader *mShader,const char **pathUtility,const char *sInclude,const char *pathMainVert,const char **FileMain)
{
    FILE* file = fopen(pathMainVert, "r");
    // FILE* wfile = fopen(nameFile,"w");

    char line[256];
    char line1[256];
    char p[30];
    int countL=0;
    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {


            if (strncmp(line,sInclude,8)==0)
            {
                // printf("%d\n", strlen(&line[8]));
                int nt=strlen(&line[8])-2;
                // char *p1 = (char*)malloc(nt*sizeof(char));
                int h=0;
                int w=0;
                strcpy(p,&line[8]);
                for (int i = 0; i < 4; i++)
                {
                    if (strncmp(pathUtility[i], p,nt)==0)
                    {
                        
                        testOpenFile(mShader,pathUtility[i],FileMain,&countL);
                    }
                }
            }
            if (strncmp(line,sInclude,8)!=0)
            {
                // FileMain=malloc(sizeof(char)*strlen(line));
                FileMain[countL]=malloc(sizeof( char)*256);
                strcpy(FileMain[countL], line);
                countL++;
                // fputs(line, wfile);
                // strcpy()
                // fputs("\n", wfile);
            }
        }

        // Close the file stream once all lines have been
        // read.
        fclose(file);
        // fclose(wfile);
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
    }
}
void calculateOpenFile(MainShader *mShader,char *p,long *sz,long *nlines)
{
    FILE *file1 = fopen(&p[0], "r");
    fseek(file1, 0L, SEEK_END);
    sz += ftell(file1);
    fseek(file1, 0L, SEEK_SET);
    char line1[256];
    // nlines[0]+=1;
    if (file1 != NULL)
    {
        while (fgets(line1, sizeof(line1), file1))
        {
            // printf("%s", line1);
            if (strncmp(line1,"include ",8)!=0)
            {
                nlines[0]+=1;
            }
            if (strncmp(line1,"include ",8)==0)
            {
                printf("%s", &line1[8]);
            }
            
        }
    }
    fclose(file1);
}

void CalculateMainFiles(MainShader *mShader,const char **pathUtility,const char *sInclude,const char *pathMainVert,long *sz,long *nlines)
{
    FILE* file = fopen(pathMainVert, "r");
    // FILE* file1;
    // Buffer to store each line of the file.
    char line[256];
    char line1[256];
    char p[30];
    long lin=0;
    long lin1=0;
    // char *tmainFileVert=NULL;
    fseek(file, 0L, SEEK_END);
    sz[0] = ftell(file);
    fseek(file, 0L, SEEK_SET);
    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        // getline()
        while (fgets(line, sizeof(line), file)) {
            // Print each line to the standard output.

            if (strncmp(line,sInclude,8)==0)
            {
                // printf("%d\n", strlen(&line[8]));
                int nt=strlen(&line[8])-2;
                // char *p1 = (char*)malloc(nt*sizeof(char));
                int h=0;
                int w=0;
                strcpy(p,&line[8]);
                // printf("rrrrr %d\n",strlen(p));
                for (int i = 0; i < 4; i++)
                {
                    if (strncmp(pathUtility[i], p,nt)==0)
                    {
                        calculateOpenFile(mShader,pathUtility[i],sz,&lin1);
                        
                    }
                }
            }
            if (strncmp(line,sInclude,8)!=0)
            {
                lin++;
            }
            
        }
        // Close the file stream once all lines have been
        // read.
        nlines[0]=lin+lin1;
        fclose(file);
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
    }
}

void FileWrite(MainShader *mShader,const char* p,const char** fileW,long sz)
{
    FILE* file = fopen(p, "w");

    // fwrite(fileW, sizeof(fileW[0]), sz, file);
    for (size_t i = 0; i < sz; i++)
    {
        fputs(fileW[i], file);
    }
    
    
    // fwrite("\0", sizeof(char), 2, file);
    fclose(file);
}
void PrintLines(MainShader *mShader,const char** linesW,long sz)
{
    for(int l=0;l<sz;l++)
    {
        printf("%s",linesW[l]);
        printf("%d\n",l);
    }
}
void FreeMemoryForShader(MainShader *mShader,const char **FileVertexShaderMain,long nlinesV)
{
    for (int l = 0; l < nlinesV; l++)
    {
        free(FileVertexShaderMain[l]);
        // printf("%d\n",nlinesV);
    }
    free(FileVertexShaderMain);
}

void initMainShader(MainShader *mShader)
{
    mShader->Vsz=0;
    mShader->Fsz=0;
    mShader->nlinesV=0;
    mShader->nlinesF=0;

}
