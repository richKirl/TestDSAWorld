#include "StaticObjects1.h"

void recursive_calculate(StaticObject1 *Obj,const C_STRUCT aiScene *sc, const C_STRUCT aiNode *nd)
{
	unsigned int i;
	unsigned int n = 0, t;
    // ,const C_STRUCT aiScene *sc, const C_STRUCT aiNode *nd;
	/* draw all meshes assigned to this node */
    
    // C_STRUCT aiNode *nd = Obj->scene->mRootNode;
	for (; n < nd->mNumMeshes; ++n) {
		const C_STRUCT aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const C_STRUCT aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;
            // printf("2 %d \n",);
            ;
			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}
			for(i = 0; i < face->mNumIndices; i++) {
                // printf("4 %d\n",i);
				int index = face->mIndices[i];//mesh->mNumVertices;
                
			}
            
            Obj->sumInds+=3;

		}

	}

	/* draw all children */
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_calculate(Obj,sc, nd->mChildren[n]);
	}

}

void recursive_read(StaticObject1 *Obj,const C_STRUCT aiScene *sc, const C_STRUCT aiNode *nd)
{
    // ,const C_STRUCT aiScene *sc, const C_STRUCT aiNode *nd
	unsigned int i;
	unsigned int n = 0, t;

	/* draw all meshes assigned to this node */
	for (; n < nd->mNumMeshes; ++n) {
		const C_STRUCT aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
        // printf("1 %d \n",mesh->mNumFaces);
        
		// apply_material(sc->mMaterials[mesh->mMaterialIndex]);
        C_STRUCT aiColor4D c;
        C_STRUCT aiMaterial* mat = sc->mMaterials[mesh->mMaterialIndex];
        aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&c);
        vec3 defColor;
        defColor=(vec3){c.r,c.g,c.b};

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const C_STRUCT aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;
            // printf("2 %d \n",mesh->mNumVertices);
			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

            vec3 tempV,CtempV,Ntemp;
			for(i = 0; i < face->mNumIndices; i++) {
                // printf("4 %d\n",i);
				int index = face->mIndices[i];//mesh->mNumVertices;
                
                tempV.x=(float)mesh->mVertices[index].x;
                tempV.y=(float)mesh->mVertices[index].y;
                tempV.z=(float)mesh->mVertices[index].z;
                if(mesh->mColors[0] != NULL){
                CtempV.x=(float)mesh->mColors[0][index].r;
                CtempV.y=(float)mesh->mColors[0][index].g;
                CtempV.z=(float)mesh->mColors[0][index].b;
                // printf("1\n");
                Obj->ColorObj[Obj->sumt]=CtempV;
                }
                else
                {
                    CtempV.x=defColor.x;
                    CtempV.y=defColor.y;
                    CtempV.z=defColor.z;
                    Obj->ColorObj[Obj->sumt]=CtempV;
                }
                if(mesh->mNormals != NULL){
                Ntemp.x=(float)mesh->mNormals[index].x;
                Ntemp.y=(float)mesh->mNormals[index].y;
                Ntemp.z=(float)mesh->mNormals[index].z;
                // printf("1\n");
                Obj->NormalsObj[Obj->sumt]=Ntemp;
                }
                Obj->VertObj[Obj->sumt]=tempV;
                
                Obj->sumt+=1;
			}
		}

	}

	/* draw all children */
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_read(Obj,sc, nd->mChildren[n]);
	}
}

void PrepareObject(StaticObject1 *Obj,const char *pModel,ShProgram1 *shaderMain)
{
    Obj->sumt=0;
    Obj->sumInds=0;
    Obj->d=0;
    // printf("1\n");
    Obj->shaderMain=shaderMain[0];
    // printf("2\n");
    createVBOBuff(&Obj->buffTemp);
    // printf("3\n");
    Obj->ModelPath=pModel;
    // C_STRUCT aiLogStream stream;
	// stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	// aiAttachLogStream(&stream);

	// /* ... same procedure, but this stream now writes the
	//    log messages to assimp_log.txt */
	// stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	// aiAttachLogStream(&stream);
    // printf("4\n");
    Obj->scene = aiImportFile(Obj->ModelPath,aiProcessPreset_TargetRealtime_MaxQuality);
    // printf("5\n");
    recursive_calculate(Obj,Obj->scene,Obj->scene->mRootNode);
    // printf("6\n");
    Obj->VertObj = malloc(sizeof(vec3)*Obj->sumInds);
    // printf("7\n");
    Obj->ColorObj = malloc(sizeof(vec3)*Obj->sumInds);
    Obj->NormalsObj = malloc(sizeof(vec3)*Obj->sumInds);
    // printf("8\n");
    recursive_read(Obj,Obj->scene,Obj->scene->mRootNode);
    // printf("9\n");
    loadData(&Obj->buffTemp, 9, Obj->sumInds, true, false, true, Obj->VertObj, Obj->NormalsObj, NULL, Obj->ColorObj);
    // printf("10\n");
    free(Obj->VertObj);
    free(Obj->ColorObj);
    free(Obj->NormalsObj);
    
    
}

void RenderObject(StaticObject1 *Obj,mat4 *view,mat4 *proj,int type)
{

        // Obj->model=RotateQT(&Obj->transform,Obj->model,Obj->d,(vec3){1,0,0});
        // model=RotateQT(model,Obj->d,(vec3){0,1,0});
        // model=RotateQT(model,Obj->d,(vec3){0,0,1});
        glBindVertexArray(Obj->buffTemp.VAO);
        useSh(&Obj->shaderMain);
        SetUniformFloat(0.0f,Obj->shaderMain.shaderProgram,"time");
        SetUniformInt(type,Obj->shaderMain.shaderProgram,"type");
        SetUniformMat4(proj,Obj->shaderMain.shaderProgram,"proj");
        SetUniformMat4(&view[0],Obj->shaderMain.shaderProgram,"view");
        SetUniformMat4(&Obj->model,Obj->shaderMain.shaderProgram,"model");
        mat3 t= Transposedm3(Inversem4((mat3){
            Obj->model.v[0], Obj->model.v[1], Obj->model.v[2],
            Obj->model.v[4], Obj->model.v[5], Obj->model.v[6],
            Obj->model.v[8], Obj->model.v[9], Obj->model.v[10]}));
        SetUniformMat3(&t,Obj->shaderMain.shaderProgram,"norm");
        
        glDrawArrays(GL_TRIANGLES, 0, Obj->sumInds);
        
        glBindVertexArray(0);
        // if (Obj->d == 359)
        //    Obj->d = 0;
        Obj->d = 1.01;
        // resetSh();
}

void CloseObject(StaticObject1 *Obj)
{
    aiReleaseImport(Obj->scene);
    deleteVBOBuff(&Obj->buffTemp);
    delSh(&Obj->shaderMain);
}

void SetPosRotScale(StaticObject1 *Obj, vec3 p, float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale)
{
    // printf("-4\n");
    SetPRS(&Obj->transform,p,rotateDegree,rotateX,rotateY,rotateZ,scale);
    Obj->model=GetModel(&Obj->transform);
    // printf("-5\n");
}

// model = AngleAxisfv3m4(model, Obj->d, (vec3){1.0f, 0.0f, 0.0f});
// model = AngleAxisfv3m4(model, Obj->d, (vec3){0.0f, 1.0f, 0.0f});
// model = AngleAxisfv3m4(model, Obj->d, (vec3){0.0f, 0.0f, 1.0f});
// mat4 Scale;
// Scale = Scalem4v3(identitym4(Scale),(vec3){2,2,2});
// model = Mulm4(model,Scale);