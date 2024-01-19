#version 460 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct PointLight
{
    vec3 position;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float constant;
    float linear;
    float quadratic;
    float radius;
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
    float radius;
};

uniform vec3 viewPos;

uniform int nbrDirLights;
uniform int nbrPointLights;
uniform int nbrSpotLights;

uniform DirLight dirLights[3];
uniform PointLight pointLights[100];
uniform SpotLight spotLights[10];

vec4 ProcessDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 ProcessPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 ProcessSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 GoochShading(vec4 color, vec3 dir, vec3 normal, vec3 viewDir);

void main()
{
    // retrieve data from gbuffer
    vec3 fragPos = texture(gPosition, texCoords).rgb;
    vec3 normal = texture(gNormal, texCoords).rgb;
    vec3 diffuse = texture(gAlbedoSpec, texCoords).rgb;

    if (normal == vec3(0))
        discard;

    // Get view direction
    vec3 viewDir = normalize(viewPos - fragPos);

    vec4 light = vec4(0);

    for (int i = 0; i < nbrDirLights; i++)
        light += ProcessDirLight(dirLights[i], normal, viewDir);

    for (int i = 0; i < nbrPointLights; i++)
        light += ProcessPointLight(pointLights[i], normal, fragPos, viewDir);

    for (int i = 0; i < nbrSpotLights; i++)
        light += ProcessSpotLight(spotLights[i], normal, fragPos, viewDir);

    // FragColor = vec4(diffuse * light.rgb, 1.0);
    FragColor = vec4(light.rgb * diffuse, 1.0);
}

vec4 ProcessDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    
    // Get light direction
    vec3 lightDir = normalize(-light.direction);

    // Get diffuse intensity
    float diff = max(dot(normal, lightDir), 0.0);

    // Reflect light direction
    vec3 reflectDir = reflect(-lightDir, normal);

    // Get specular intensity
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Combine
    return GoochShading(ambient + diffuse + specular, lightDir, normal, viewDir);
}

vec4 ProcessPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // calculate distance between light source and current fragment
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

    float radiusSq = light.radius * light.radius;

    float linearAtt = light.radius / (light.radius + light.linear * distance);
    float quadAtt = radiusSq / (radiusSq + light.quadratic * distance * distance);

    // Compute light attenuation
    float attenuation = linearAtt * quadAtt;    

    // Get result lights
    vec4 ambient = light.ambient;
    vec4 diffuse = light.diffuse * diff;
    vec4 specular = light.specular * spec;

    // Apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Combine
    return GoochShading(ambient + diffuse + specular, lightDir, normal, viewDir);
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

    float distance = length(light.position - fragPos);
    float radiusSq = light.radius * light.radius;
    
    float linearAtt = light.radius / (light.radius + light.linear * distance);
    float quadAtt = radiusSq / (radiusSq + light.quadratic * distance * distance);

    // Compute light attenuation
    float attenuation = linearAtt * quadAtt;

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
    return GoochShading(ambient + diffuse + specular, lightDir, normal, viewDir);
}

vec4 GoochShading(vec4 color, vec3 dir, vec3 normal, vec3 viewDir)
{
    //diffuse
    float kd = 1;
    float a = 0.2;
    float b = 0.6;

    float NL = dot(normalize(normal), normalize(dir));
    
    float it = ((1 + NL) / 2);
    vec3 newColor = (1-it) * (vec3(0, 0, 0.4) + a*color.xyz) 
               +  it * (vec3(0.4, 0.4, 0) + b*color.xyz);
    
    //Highlights
    vec3 R = reflect( -normalize(dir), 
                      normalize(normal) );
    float ER = clamp( dot( normalize(dir), 
                           normalize(R)),
                     0, 1);
    
    vec4 spec = vec4(1) * pow(ER, 32);

    return vec4(newColor+spec.xyz, color.a);
}

