#version 460 core 

layout(location = 0) in vec3 vertexPosition; 
layout(location = 1) in vec3 vCol; 
layout(location = 2) in vec3 vNorm; 

smooth out vec3 ioVColor; 
smooth out vec3 ioVertexTexNormal; 
smooth out vec4 ioEyeSpacePosition; 
smooth out float visibility; 
smooth out vec4 posRelativeToCam; 
uniform mat4 model; 
uniform mat4 proj; 
uniform mat4 view; 
uniform mat3 norm; 
uniform float time; 
uniform vec4 vposRelativeToCam; 

include asset/shaders/tnoise.glsl

vec3 lPos = vec3(0.0,3.0,0.0); 
float density = 0.00035; 
float gradient = 1.5; 

void main() 
{ 
   mat4 mvpMatrix = proj * view * model; 
   vec4 wPos; 

     if(time==0.0){ 
        wPos = model * vec4(vertexPosition,1.0); 
        posRelativeToCam = view * wPos; 
     	gl_Position = mvpMatrix*vec4(vertexPosition, 1.0); 
     } 
     if(time>0){ 
        float noise = pnoise(vec3(vertexPosition) + time,vec3(35)); 
        float displacement = noise / 10.0; 
        vec3 newPos = vec3(vertexPosition); 
        float j=2*3.1415/20.0; 
        float wave = 0.01*(33*sin(j*(vertexPosition.x-5*time))+(33*cos(j*(vertexPosition.z-5*time)))) ; 
        newPos.y = wave; 
        newPos.y += vertexPosition.y + vNorm.y *displacement; 
        wPos = model * vec4(newPos,1.0); 
        posRelativeToCam = view * wPos; 
        vec4 dt=vec4(newPos, 1.0); 
     	gl_Position = mvpMatrix*dt; 
     } 
     	ioVColor = vCol;
      ioVertexTexNormal = norm * vNorm;
   ioEyeSpacePosition = mvpMatrix * vec4(vertexPosition, 1.0);
   float distance = length(posRelativeToCam.xyz);
   visibility = exp(- pow((distance * density), gradient));
   visibility = clamp(visibility, 0.0, 1.0); 
} 
