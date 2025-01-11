
struct AmbientLight 
{
    vec3 color;
    bool isOn;
};

vec3 getAmbientLightColor(AmbientLight ambientLight) {
    return ambientLight.isOn ? ambientLight.color : vec3(0.0, 0.0, 0.0);
}