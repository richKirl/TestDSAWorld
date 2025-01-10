#ifndef __SHADERS1_T__
#define __SHADERS1_T__

const char *shader01vert = {
    "#version 460 core\n"

    "layout(location = 0) in vec3 vertexPosition;\n"

    "void main()\n"
    "{\n"
    "	gl_Position = vec4(vertexPosition, 1.0);\n"
    "}\n"};
const char *shader01frag = {
    "#version 460 core\n"

    "layout(location = 0) out vec4 outputColor;\n"

    "void main()\n"
    "{\n"
    "	outputColor = vec4(1.0, 0.0, 1.0, 0.7);\n"
    "}\n"};

const char *shader02vert = {
    "#version 460 core\n"
    "layout(location = 0) in vec3 vertexPosition;\n"
    "layout(location = 1) in vec3 vCol;\n"
    "smooth out vec3 ioVColor;\n"
    "void main()\n"
    "{\n"
    "	gl_Position = vec4(vertexPosition, 1.0);\n"
    "	ioVColor = vCol;\n"
    "}\n"};
const char *shader02frag = {
    "#version 460 core\n"

    "layout(location = 0) out vec4 outputColor;\n"
    "smooth in vec3 ioVColor;\n"

    "void main()\n"
    "{\n"
    "	outputColor = vec4(ioVColor, 1.0);\n"
    "}\n"};

const char *shader03vert = {
    "#version 460 core\n"
    "layout(location = 0) in vec3 vertexPosition;\n"
    "layout(location = 1) in vec3 vCol;\n"

    "smooth out vec3 ioVColor;\n"
    "uniform mat4 model;\n"
    "uniform mat4 proj;\n"
    "uniform mat4 view;\n"
    "void main()\n"
    "{\n"
    "   mat4 mvpMatrix = proj * view * model;\n"
    "	gl_Position = mvpMatrix*vec4(vertexPosition, 1.0);\n"
    "	ioVColor = vCol;\n"
    "}\n"};
const char *shader03frag = {
    "#version 460 core\n"

    "layout(location = 0) out vec4 outputColor;\n"
    "smooth in vec3 ioVColor;\n"

    "void main()\n"
    "{\n"
    "	outputColor = vec4(ioVColor, 1.0);\n"
    "}\n"};

const char *shader04vert = 
{
    "#version 460 core\n"

    "layout(location = 0) in vec3 vertexPosition;\n"
    "layout(location = 1) in vec3 vCol;\n"
    "layout(location = 2) in vec3 vNorm;\n"

    "smooth out vec3 ioVColor;\n"
    "smooth out vec3 ioVertexTexNormal;\n"
    "smooth out vec4 ioEyeSpacePosition;\n"
    "smooth out float visibility;\n"
    "smooth out vec4 posRelativeToCam;\n"
    "uniform mat4 model;\n"
    "uniform mat4 proj;\n"
    "uniform mat4 view;\n"
    "uniform mat3 norm;\n"
    "uniform float time;\n"

    "vec3 mod289(vec3 x)\n"
    "{\n"
        "return x - floor(x * (1.0 / 289.0)) * 289.0;\n"
    "}\n"

"vec4 mod289(vec4 x)\n"
"{\n"
  "return x - floor(x * (1.0 / 289.0)) * 289.0;\n"
"}\n"

"vec4 permute(vec4 x)\n"
"{\n"
  "return mod289(((x*34.0)+10.0)*x);\n"
"}\n"

"vec4 taylorInvSqrt(vec4 r)\n"
"{\n"
  "return 1.79284291400159 - 0.85373472095314 * r;\n"
"}\n"

"vec3 fade(vec3 t) {\n"
  "return t*t*t*(t*(t*6.0-15.0)+10.0);\n"
"}\n"

// // Classic Perlin noise
// float cnoise(vec3 P)
// {
//   vec3 Pi0 = floor(P); // Integer part for indexing
//   vec3 Pi1 = Pi0 + vec3(1.0); // Integer part + 1
//   Pi0 = mod289(Pi0);
//   Pi1 = mod289(Pi1);
//   vec3 Pf0 = fract(P); // Fractional part for interpolation
//   vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
//   vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
//   vec4 iy = vec4(Pi0.yy, Pi1.yy);
//   vec4 iz0 = Pi0.zzzz;
//   vec4 iz1 = Pi1.zzzz;

//   vec4 ixy = permute(permute(ix) + iy);
//   vec4 ixy0 = permute(ixy + iz0);
//   vec4 ixy1 = permute(ixy + iz1);

//   vec4 gx0 = ixy0 * (1.0 / 7.0);
//   vec4 gy0 = fract(floor(gx0) * (1.0 / 7.0)) - 0.5;
//   gx0 = fract(gx0);
//   vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
//   vec4 sz0 = step(gz0, vec4(0.0));
//   gx0 -= sz0 * (step(0.0, gx0) - 0.5);
//   gy0 -= sz0 * (step(0.0, gy0) - 0.5);

//   vec4 gx1 = ixy1 * (1.0 / 7.0);
//   vec4 gy1 = fract(floor(gx1) * (1.0 / 7.0)) - 0.5;
//   gx1 = fract(gx1);
//   vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
//   vec4 sz1 = step(gz1, vec4(0.0));
//   gx1 -= sz1 * (step(0.0, gx1) - 0.5);
//   gy1 -= sz1 * (step(0.0, gy1) - 0.5);

//   vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
//   vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
//   vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
//   vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
//   vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
//   vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
//   vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
//   vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

//   vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
//   g000 *= norm0.x;
//   g010 *= norm0.y;
//   g100 *= norm0.z;
//   g110 *= norm0.w;
//   vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
//   g001 *= norm1.x;
//   g011 *= norm1.y;
//   g101 *= norm1.z;
//   g111 *= norm1.w;

//   float n000 = dot(g000, Pf0);
//   float n100 = dot(g100, vec3(Pf1.x, Pf0.yz));
//   float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
//   float n110 = dot(g110, vec3(Pf1.xy, Pf0.z));
//   float n001 = dot(g001, vec3(Pf0.xy, Pf1.z));
//   float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
//   float n011 = dot(g011, vec3(Pf0.x, Pf1.yz));
//   float n111 = dot(g111, Pf1);

//   vec3 fade_xyz = fade(Pf0);
//   vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
//   vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);
//   float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); 
//   return 2.2 * n_xyz;
// }

// Classic Perlin noise, periodic variant
"float pnoise(vec3 P, vec3 rep)\n"
"{\n"
  "vec3 Pi0 = mod(floor(P), rep);\n" // Integer part, modulo period
  "vec3 Pi1 = mod(Pi0 + vec3(1.0), rep);\n" // Integer part + 1, mod period
  "Pi0 = mod289(Pi0);\n"
  "Pi1 = mod289(Pi1);\n"
  "vec3 Pf0 = fract(P);\n" // Fractional part for interpolation
  "vec3 Pf1 = Pf0 - vec3(1.0);\n" // Fractional part - 1.0
  "vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);\n"
  "vec4 iy = vec4(Pi0.yy, Pi1.yy);\n"
  "vec4 iz0 = Pi0.zzzz;\n"
  "vec4 iz1 = Pi1.zzzz;\n"

  "vec4 ixy = permute(permute(ix) + iy);\n"
  "vec4 ixy0 = permute(ixy + iz0);\n"
  "vec4 ixy1 = permute(ixy + iz1);\n"

  "vec4 gx0 = ixy0 * (1.0 / 7.0);\n"
  "vec4 gy0 = fract(floor(gx0) * (1.0 / 7.0)) - 0.5;\n"
  "gx0 = fract(gx0);\n"
  "vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);\n"
  "vec4 sz0 = step(gz0, vec4(0.0));\n"
  "gx0 -= sz0 * (step(0.0, gx0) - 0.5);\n"
  "gy0 -= sz0 * (step(0.0, gy0) - 0.5);\n"

  "vec4 gx1 = ixy1 * (1.0 / 7.0);\n"
  "vec4 gy1 = fract(floor(gx1) * (1.0 / 7.0)) - 0.5;\n"
  "gx1 = fract(gx1);\n"
  "vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);\n"
  "vec4 sz1 = step(gz1, vec4(0.0));\n"
  "gx1 -= sz1 * (step(0.0, gx1) - 0.5);\n"
  "gy1 -= sz1 * (step(0.0, gy1) - 0.5);\n"

  "vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);\n"
  "vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);\n"
  "vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);\n"
  "vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);\n"
  "vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);\n"
  "vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);\n"
  "vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);\n"
  "vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);\n"

  "vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));\n"
  "g000 *= norm0.x;\n"
  "g010 *= norm0.y;\n"
  "g100 *= norm0.z;\n"
  "g110 *= norm0.w;\n"
  "vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));\n"
  "g001 *= norm1.x;\n"
  "g011 *= norm1.y;\n"
  "g101 *= norm1.z;\n"
  "g111 *= norm1.w;\n"

  "float n000 = dot(g000, Pf0);\n"
  "float n100 = dot(g100, vec3(Pf1.x, Pf0.yz));\n"
  "float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));\n"
  "float n110 = dot(g110, vec3(Pf1.xy, Pf0.z));\n"
  "float n001 = dot(g001, vec3(Pf0.xy, Pf1.z));\n"
  "float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));\n"
  "float n011 = dot(g011, vec3(Pf0.x, Pf1.yz));\n"
  "float n111 = dot(g111, Pf1);\n"

  "vec3 fade_xyz = fade(Pf0);\n"
  "vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);\n"
  "vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);\n"
  "float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); \n"
  "return 2.2 * n_xyz;\n"
"}\n"
  "vec3 lPos = vec3(0.0,3.0,0.0);\n"
    "float density = 0.00035;\n"
    "float gradient = 1.5;\n"

    "void main()\n"
    "{\n"
    "   mat4 mvpMatrix = proj * view * model;\n"
    "vec4 wPos;\n"

    "if(time==0.0){\n"
    "   wPos = model * vec4(vertexPosition,1.0);\n"
    "   posRelativeToCam = view * wPos;\n"
    "	gl_Position = mvpMatrix*vec4(vertexPosition, 1.0);\n"
    "}\n"
    "if(time>0){\n"
    "   float noise = pnoise(vec3(vertexPosition) + time,vec3(35));\n"
    "   float displacement = noise / 10.0;\n"
    "   vec3 newPos = vec3(vertexPosition);\n"
    "   float j=2*3.1415/20.0;"
    "   float wave = 0.01*(33*sin(j*(vertexPosition.x-5*time))+33*cos(j*(vertexPosition.z-5*time))) ;\n"
    "   newPos.y = wave;\n"
    "   newPos.y += vertexPosition.y + vNorm.y * displacement;\n"
    "   wPos = model * vec4(newPos,1.0);\n"
    "   posRelativeToCam = view * wPos;\n"
    "   vec4 dt=vec4(newPos, 1.0);\n"
    "	gl_Position = mvpMatrix*dt;\n"
    "}\n"
    "	ioVColor = vCol;\n"
    "   ioVertexTexNormal = norm*vNorm;\n"
    "   ioEyeSpacePosition = mvpMatrix* vec4(vertexPosition, 1.0);\n"
            "float distance = length(posRelativeToCam.xyz);\n"
            // "posRelativeToCam=wPos;\n"
            "visibility = exp(-pow((distance*density),gradient));\n"
            "visibility = clamp(visibility,0.0,1.0);\n"
    "}\n"
};

const char *shader04frag = {
    "#version 460 core\n"

    "struct AmbientLight\n"
    "{\n"
    "    vec3 color;\n"
    "    bool isOn;\n"
    "};\n"
    
    "struct DiffuseLight\n"
    "{\n"
    "    vec3 color;\n"
    "    vec3 direction;\n"
    "    float factor;\n"
    "    bool isOn;\n"
    "};\n"
    "struct Material\n"
    "{\n"
    "bool isEnabled;\n"
    "float specularIntensity;\n"
    "float specularPower;\n"
    "};\n"
    "vec3 getDiffuseLightColor(DiffuseLight diffuseLight, vec3 normal)\n"
    "{\n"
    "if(!diffuseLight.isOn) {\n"
    "   return vec3(0.0, 0.0, 0.0);\n"
    "}\n"

    "float finalIntensity = max(0.0, dot(normal, -diffuseLight.direction));\n"
    "finalIntensity = clamp(finalIntensity*diffuseLight.factor, 0.0, 1.0);\n"
    "return vec3(diffuseLight.color*finalIntensity);\n"
    "}\n"
    
    "vec3 getAmbientLightColor(AmbientLight ambientLight)\n"
    "{\n"
    "return ambientLight.isOn ? ambientLight.color : vec3(0.0, 0.0, 0.0);\n"
    "}\n"

    "vec3 getSpecularHighlightColor(vec3 worldPosition, vec3 normal, vec3 eyePosition, Material material, DiffuseLight diffuseLight)\n"
    "{\n"
    "if(!material.isEnabled) {\n"
        "return vec3(0.0);\n"
    "}\n"

    "vec3 reflectedVector = normalize(reflect(diffuseLight.direction, normal));\n"
    "vec3 worldToEyeVector = normalize(eyePosition - worldPosition);\n"
    "float specularFactor = dot(worldToEyeVector, reflectedVector);\n"

    "if (specularFactor > 0)\n"
    "{\n"
        "specularFactor = pow(specularFactor, material.specularPower);\n"
        "return diffuseLight.color * material.specularIntensity * specularFactor;\n"
    "}\n"

    "return vec3(0.0);\n"
    "}\n"

    "layout(location = 0) out vec4 outputColor;\n"
    "smooth in vec3 ioVColor;\n"
    "smooth in vec3 ioVertexTexNormal;\n"
    "smooth in vec4 ioEyeSpacePosition;\n"
    "smooth in float visibility;\n"
    "smooth in vec4 posRelativeToCam;\n"
    "uniform AmbientLight ambientL;\n"
    "uniform DiffuseLight diffuseL;\n"
    "uniform Material materialL;\n"
    "uniform vec4 color;\n"
    "uniform int type;\n"
    "uniform samplerCube skybox;\n"
    "vec3 skyColor=vec3(0.1,0.1,0.3);\n"
    "void main()\n"
    "{\n"
        "vec3 normal = normalize(ioVertexTexNormal);\n"
        "vec3 lightColor = getAmbientLightColor(ambientL)+getDiffuseLightColor(diffuseL,normal)+getSpecularHighlightColor(posRelativeToCam.xyz,normal,ioEyeSpacePosition.xyz,materialL,diffuseL);\n"
        "if(type==1){\n"

        "outputColor = vec4(ioVColor, 1.0)*vec4(1,1,1, 1.0)*vec4(lightColor, 1.0);\n"
        "outputColor= mix(vec4(skyColor,1.0),outputColor,visibility);\n"
        "}\n"
        "if(type==2){\n"
        "float ratio = 1.00 / 1.33;\n"
        "vec3 I = normalize(vec3(1-ioEyeSpacePosition));\n"
        "vec3 R = reflect(I, normal);\n"
        "outputColor = mix(vec4(ioVColor,0.3),vec4(texture(skybox, R).rgb, 0.4),.5)*vec4(lightColor, 1.0);\n"//*vec4(lightColor, 1.0)
        "outputColor= mix(vec4(skyColor,1.),outputColor,abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w));\n"//abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w))
        "}\n"
    "}\n"};

const char *skyboxVert = {
    "#version 460 core\n"
    "layout(location = 0) in vec3 vertexPosition;\n"

    "smooth out vec3 TexCoords;\n"
    "smooth out float visibility;\n"
    "smooth out vec4 ioEyeSpacePosition;\n"
    "uniform mat4 proj;\n"
    "uniform mat4 view;\n"
    "vec3 lPos = vec3(0.0,3.0,0.0);\n"
    "float density = 0.036;\n"
    "float gradient = 1.5;\n"
    "void main()\n"
    "{\n"
    "   TexCoords=vertexPosition;\n"
    "   mat4 mvpMatrix = proj * view ;\n"
    "	vec4 pos = mvpMatrix*vec4(vertexPosition, 1.0);\n"
            "float distance = length(pos.xyz);\n"
            "visibility = exp(-pow((distance*density),gradient));\n"
            "visibility = clamp(visibility,0.0,1.);\n"
    "ioEyeSpacePosition = pos.xyww;\n"
    "   gl_Position = pos.xyww;\n"
    "}\n"};
const char *skyboxFrag = {
    "#version 460 core\n"

    "layout(location = 0) out vec4 outputColor;\n"
    "smooth in vec3 TexCoords;\n"
    "smooth in float visibility;\n"
    "smooth in vec4 ioEyeSpacePosition;\n"
    "uniform samplerCube skybox;"
    "vec3 skyColor=vec3(0.1,0.1,0.4);\n"
    "void main()\n"
    "{\n"
    "	outputColor = texture(skybox, TexCoords);\n"
    "outputColor= mix(vec4(skyColor,.1),outputColor,abs(ioEyeSpacePosition.z / ioEyeSpacePosition.w));\n"
    "}\n"};
#endif

    // "layout (std140) uniform Matrices\n"
    // "{\n"
    // 	"mat4 proj;\n"
    // 	"mat4 view;\n"
    // 	// "mat4 ortho;\n"
    // 	// "mat4 lightSpaceMatrix;"
    // "};\n"