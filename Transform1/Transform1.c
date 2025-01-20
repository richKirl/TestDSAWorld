#include "Transform1.h"

void SetPRS(Transform1 *transform,vec3 p,float rotateDegree, vec3 rotateX, vec3 rotateY, vec3 rotateZ, vec3 scale)
{
    // printf("-9");
    // printf("-9");
    transform->model=identitym4(transform->model);
    transform->Rotate=identitym4(transform->Rotate);
    // transform->RotateX=identitym4(transform->RotateX);
    // transform->RotateY=identitym4(transform->RotateY);
    // transform->RotateZ=identitym4(transform->RotateZ);
    transform->Scale=identitym4(transform->Scale);
    transform->Translate=identitym4(transform->Translate);

    transform->Translate = Translationm4v3(transform->Translate,p);
    Quaternion q;
    // q.v[3]=1;
    // q=Qidentity();
    q=QAngleAxisdV3(rotateDegree,(vec3){rotateX.x,rotateY.y,rotateZ.z});
    // if(scale.x!=0&&scale.y!=0&&scale.z!=0)
        transform->Scale= Scalem4v3(transform->Scale,scale);
    
    transform->Rotate = ToMatrixQQ1(q);
    transform->model= Mulm4(transform->model,transform->Translate);
    transform->model= Mulm4(transform->model,transform->Rotate);//,transform->Scale
    transform->model= Mulm4(transform->model,transform->Scale);
}

mat4 GetModel(Transform1 *transform)
{
    return transform->model;
}

mat4 RotateQT(Transform1 *transform,mat4 m,float angle, vec3 ax)
{
    Quaternion q;
    q=QAngleAxisdV3(angle,ax);
    mat4 rot;
    rot=ToMatrixQQ1(q);
    transform->model=Mulm4(m,rot);
    return transform->model;
}
