#ifndef __SHADERS1_T__
#define __SHADERS1_T__

// const char *shader01vert = {
//     "#version 460 core\n"

//     "layout(location = 0) in vec3 vertexPosition;\n"

//     "void main()\n"
//     "{\n"
//     "	gl_Position = vec4(vertexPosition, 1.0);\n"
//     "}\n"};
// const char *shader01frag = {
//     "#version 460 core\n"

//     "layout(location = 0) out vec4 outputColor;\n"

//     "void main()\n"
//     "{\n"
//     "	outputColor = vec4(1.0, 0.0, 1.0, 0.7);\n"
//     "}\n"};

// const char *shader02vert = {
//     "#version 460 core\n"
//     "layout(location = 0) in vec3 vertexPosition;\n"
//     "layout(location = 1) in vec3 vCol;\n"
//     "smooth out vec3 ioVColor;\n"
//     "void main()\n"
//     "{\n"
//     "	gl_Position = vec4(vertexPosition, 1.0);\n"
//     "	ioVColor = vCol;\n"
//     "}\n"};
// const char *shader02frag = {
//     "#version 460 core\n"

//     "layout(location = 0) out vec4 outputColor;\n"
//     "smooth in vec3 ioVColor;\n"

//     "void main()\n"
//     "{\n"
//     "	outputColor = vec4(ioVColor, 1.0);\n"
//     "}\n"};

// const char *shader03vert = {
//     "#version 460 core\n"
//     "layout(location = 0) in vec3 vertexPosition;\n"
//     "layout(location = 1) in vec3 vCol;\n"

//     "smooth out vec3 ioVColor;\n"
//     "uniform mat4 model;\n"
//     "uniform mat4 proj;\n"
//     "uniform mat4 view;\n"
//     "void main()\n"
//     "{\n"
//     "   mat4 mvpMatrix = proj * view * model;\n"
//     "	gl_Position = mvpMatrix*vec4(vertexPosition, 1.0);\n"
//     "	ioVColor = vCol;\n"
//     "}\n"};
// const char *shader03frag = {
//     "#version 460 core\n"

//     "layout(location = 0) out vec4 outputColor;\n"
//     "smooth in vec3 ioVColor;\n"

//     "void main()\n"
//     "{\n"
//     "	outputColor = vec4(ioVColor, 1.0);\n"
//     "}\n"};

// const char *shader04vert = 
// {
//     "#version 460 core\n"

//     "layout(location = 0) in vec3 vertexPosition;\n"
//     "layout(location = 1) in vec3 vCol;\n"
//     "layout(location = 2) in vec3 vNorm;\n"

//     "smooth out vec3 ioVColor;\n"
//     "smooth out vec3 ioVertexTexNormal;\n"
//     "smooth out vec4 ioEyeSpacePosition;\n"
//     "smooth out float visibility;\n"
//     "smooth out vec4 posRelativeToCam;\n"
//     "uniform mat4 model;\n"
//     "uniform mat4 proj;\n"
//     "uniform mat4 view;\n"
//     "uniform mat3 norm;\n"
//     "uniform float time;\n"
//     "uniform vec4 vposRelativeToCam;\n"

//     "include tnoise"

//     "vec3 lPos = vec3(0.0,3.0,0.0);\n"
//     "float density = 0.00035;\n"
//     "float gradient = 1.5;\n"

//     "void main()\n"
//     "{\n"
//     "   mat4 mvpMatrix = proj * view * model;\n"
//         "vec4 wPos;\n"

//     "if(time==0.0){\n"
//     "   wPos = model * vec4(vertexPosition,1.0);\n"
//     "   posRelativeToCam = view * wPos;\n"
//     "	gl_Position = mvpMatrix*vec4(vertexPosition, 1.0);\n"
//     "}\n"
//     "if(time>0){\n"
//     "   float noise = pnoise(vec3(vertexPosition) + time,vec3(5));\n"
//     "   float displacement = noise / 10.0;\n"
//     "   vec3 newPos = vec3(vertexPosition);\n"
//     "   float j=2*3.1415/20.0;"
//     "   float wave = 0.01*(33*sin(j*(vertexPosition.x-5*time))+(33*cos(j*(vertexPosition.z-5*time)))) ;\n"
//     "   newPos.y = wave;\n"
//     "   newPos.y += vertexPosition.y + vNorm.y *displacement;\n"
//     "   wPos = model * vec4(newPos,1.0);\n"
//     "   posRelativeToCam = view * wPos;\n"
//     "   vec4 dt=vec4(newPos, 1.0);\n"
//     "	gl_Position = mvpMatrix*dt;\n"
//     "}\n"
//     "	ioVColor = vCol;\n"
//     "   ioVertexTexNormal = norm*vNorm;\n"
//     "   ioEyeSpacePosition = mvpMatrix* vec4(vertexPosition, 1.0);\n"
//             "float distance = length(posRelativeToCam.xyz);\n"
//             // "posRelativeToCam=wPos;\n"
//             "visibility = exp(-pow((distance*density),gradient));\n"
//             "visibility = clamp(visibility,0.0,1.0);\n"
//     "}\n"
// };

// const char *shader04frag = {
//     "#version 460 core\n"

//     "include Ambient.glsl"
//     "include Diffuse.glsl"
//     "include Specular.glsl"

//     "layout(location = 0) out vec4 outputColor;\n"
//     "smooth in vec3 ioVColor;\n"
//     "smooth in vec3 ioVertexTexNormal;\n"
//     "smooth in vec4 ioEyeSpacePosition;\n"
//     "smooth in float visibility;\n"
//     "smooth in vec4 posRelativeToCam;\n"
//     "uniform AmbientLight ambientL;\n"
//     "uniform DiffuseLight diffuseL;\n"
//     "uniform Material materialL;\n"
//     "uniform vec4 color;\n"
//     "uniform int type;\n"
//     "uniform samplerCube skybox;\n"
//     "vec3 skyColor=vec3(0.1,0.1,0.3);\n"

    


//     "void main()\n"
//     "{\n"
//         "vec3 normal = normalize(ioVertexTexNormal);\n"
        
//         "vec3 lightColor = getAmbientLightColor(ambientL)+getDiffuseLightColor(diffuseL,normal)+getSpecularHighlightColor(posRelativeToCam.xyz,normal,ioEyeSpacePosition.xyz,materialL,diffuseL);\n"
//         "if(type==1){\n"

//         "outputColor = vec4(ioVColor, 1.0)*vec4(1,1,1, 1.0)*vec4(lightColor, 1.0);\n"
//         "outputColor= mix(vec4(skyColor,1.0),outputColor,visibility);\n"
//         "}\n"
//         "if(type==2){\n"
//         "float ratio = 1.00 / 1.33;\n"
//         "vec3 I = normalize(vec3(1-ioEyeSpacePosition));\n"
//         "vec3 R = reflect(I, -normal);\n"
//         "outputColor = mix(vec4(ioVColor,0.3),vec4(texture(skybox, R).rgb, 0.4),.5)*vec4(lightColor, 1.0);\n"//*vec4(lightColor, 1.0)
//         "outputColor= mix(vec4(skyColor,1.),outputColor,abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w));\n"//abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w))
//         "}\n"
//     "}\n"};

// const char *skyboxVert = {
//     "#version 460 core\n"
//     "layout(location = 0) in vec3 vertexPosition;\n"

//     "smooth out vec3 TexCoords;\n"
//     "smooth out float visibility;\n"
//     "smooth out vec4 ioEyeSpacePosition;\n"
//     "uniform mat4 proj;\n"
//     "uniform mat4 view;\n"
//     "vec3 lPos = vec3(0.0,3.0,0.0);\n"
//     "float density = 0.036;\n"
//     "float gradient = 1.5;\n"
//     "void main()\n"
//     "{\n"
//     "   TexCoords=vertexPosition;\n"
//     "   mat4 mvpMatrix = proj * view ;\n"
//     "	vec4 pos = mvpMatrix*vec4(vertexPosition, 1.0);\n"
//             "float distance = length(pos.xyz);\n"
//             "visibility = exp(-pow((distance*density),gradient));\n"
//             "visibility = clamp(visibility,0.0,1.);\n"
//     "ioEyeSpacePosition = pos.xyww;\n"
//     "   gl_Position = pos.xyww;\n"
//     "}\n"};
// const char *skyboxFrag = {
//     "#version 460 core\n"

//     "layout(location = 0) out vec4 outputColor;\n"
//     "smooth in vec3 TexCoords;\n"
//     "smooth in float visibility;\n"
//     "smooth in vec4 ioEyeSpacePosition;\n"
//     "uniform samplerCube skybox;"
//     "vec3 skyColor=vec3(0.1,0.1,0.4);\n"
//     "void main()\n"
//     "{\n"
//     "	outputColor = texture(skybox, TexCoords);\n"
//     "outputColor= mix(vec4(skyColor,.1),outputColor,abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w));\n"
//     "}\n"};
#endif

    // "layout (std140) uniform Matrices\n"
    // "{\n"
    // 	"mat4 proj;\n"
    // 	"mat4 view;\n"
    // 	// "mat4 ortho;\n"
    // 	// "mat4 lightSpaceMatrix;"
    // "};\n"