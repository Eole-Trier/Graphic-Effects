#version 460 core

out vec4 outColor;
  
in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D ourTexture;

struct PointLight
{
    vec3 position;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;
  
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    
    float constant;
    float linear;
    float quadratic; 
};

uniform vec3 viewPos;

uniform int nbrDirLights;
uniform int nbrPointLights;
uniform int nbrSpotLights;

uniform DirLight dirLights[3];
uniform PointLight pointLights[10];
uniform SpotLight spotLights[10];

vec4 ProcessDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 ProcessPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 ProcessSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Get view direction
    vec3 viewDir = normalize(viewPos - fragPos);

    vec4 light = vec4(0);

    for (int i = 0; i < nbrDirLights; i++)
        light += ProcessDirLight(dirLights[i], normal, viewDir);

    for (int i = 0; i < nbrPointLights; i++)
        light += ProcessPointLight(pointLights[i], normal, fragPos, viewDir);

    for (int i = 0; i < nbrSpotLights; i++)
        light += ProcessSpotLight(spotLights[i], normal, fragPos, viewDir);

    outColor = light * texture(ourTexture, texCoords);
}

vec4 ProcessDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // Get light direction
    vec3 lightDir = normalize(-light.direction);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    diff = ceil(diff * toon_color_levels) * toon_scale_factor; // toonification

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Combine
    return ambient + diffuse + specular;
}

vec4 ProcessPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Get light direction
    vec3 lightDir = normalize(light.position - fragPos);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Get the distance between the light and the pixel
    float distance = length(light.position - fragPos);

    // Compute light attenuation
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Combine
    return ambient + diffuse + specular;
}

vec4 ProcessSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Get light direction
    vec3 lightDir = normalize(light.position - fragPos);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    
    // Get the distance between the light and the pixel
    float dist = length(light.position - fragPos);
    
    // Compute light attenuation
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));    

    // Compute cutoff
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Apply attenuation
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    // Combine
    return ambient + diffuse + specular;
}
