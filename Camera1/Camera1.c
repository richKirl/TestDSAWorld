#include "Camera1.h"

void CameraInit(Camera1 *camera, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp, vec3 vp, float cameraSpeed)
{
    camera->cameraPos=cameraPos;
    camera->cameraFront=cameraFront;
    camera->cameraUp=cameraUp;
    camera->vp=vp;
    camera->cameraSpeed=cameraSpeed;
}

vec3 getNormalView(Camera1 *camera)
{
    return Normalizev3(Subv3(camera->vp,camera->cameraPos));
}
void rotateBy(Camera1 *camera,float deg)
{
    Quaternion q;
    q=QAngleAxisdV3(deg,(vec3){0,1,0});
    mat4 rot;
    rot=ToMatrixQQ1(q);
    vec3 tN = getNormalView(camera);
    vec4 rotViewVec = Mulmv4(rot, (vec4){tN.x, tN.y, tN.z, 0});

    camera->vp = Addv3(camera->cameraPos, (vec3){rotViewVec.x, rotViewVec.y, rotViewVec.z});
}

void rotateUD(Camera1 *camera,float deg)
{
    vec3 viewVector = getNormalView(camera);
    vec3 viewVectorNoY = Normalizev3((vec3){viewVector.x, 0.0f, viewVector.z});

    float currentAngleDegrees = Anglev3(viewVectorNoY,viewVector);
    if (viewVector.y < 0.0f) {
        currentAngleDegrees = -currentAngleDegrees;
    }

    float newAngleDegrees = currentAngleDegrees + deg;
    if (newAngleDegrees > -85.0f && newAngleDegrees < 85.0f)
    {
        vec3 rotationAxis = Crossv3(getNormalView(camera), camera->cameraUp);
        rotationAxis = Normalizev3(rotationAxis);

        Quaternion q;
        q = QAngleAxisdV3(deg, rotationAxis);
        mat4 rot;
        rot = ToMatrixQQ1(q);
        vec3 tN = getNormalView(camera);
        vec4 rotViewVec = Mulmv4(rot, (vec4){tN.x, tN.y, tN.z, 0});

        camera->vp = Addv3(camera->cameraPos, (vec3){rotViewVec.x, rotViewVec.y, rotViewVec.z});
    }
}
void moveBy(Camera1 *camera,float deg)
{
    vec3 vOffset = getNormalView(camera);
    vOffset = Mulv3c(vOffset, deg);
    camera->cameraPos = Addv3(camera->cameraPos, vOffset);
    camera->vp = Addv3(camera->vp, vOffset);
}