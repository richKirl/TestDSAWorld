#ifndef __CAMERA1_T__
#define __CAMERA1_T__
#include <stdbool.h>
#include "../Math1/WTMath.h"
// float lastX =  1200.0f / 2.0;
// float lastY =  900.0 / 2.0;
// float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
// float pitch =  0.0f;
struct Camera1_t
{
    float lastX;
    float lastY;
    vec3 cameraPos;
    vec3 cameraFront;
    vec3 cameraUp;
    vec3 vp;
    float cameraSpeed;
    vec2 mousePos;
};

typedef struct Camera1_t Camera1;

void CameraInit(Camera1 *camera,vec3 cameraPos,vec3 cameraFront,vec3 cameraUp,vec3 vp,float cameraSpeed);
vec3 getNormalView(Camera1 *camera);
void rotateBy(Camera1 *camera,float deg);
void rotateUD(Camera1 *camera,float deg);
void moveBy(Camera1 *camera,float deg);
#endif