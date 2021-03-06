#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

//通过两个贴图，达到每个片段的diffuse分量和specular分量都不一样；也就是说上一节中每个片段的漫反射效果不一样，但是镜面效果是一样的；但是这一节每个片段的漫反射效果不一样；有些片段的镜面效果也不一样
//此节就模拟出不同的漫反射效果，同一物体不同地方的镜面效果可能不一样的效果；
void main()
{
    // ambient
	//最终输出的环境光分量 = 光源的的环境光分量 * 物体的纹理
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
	//最终输出的漫反射分量 = 光源的漫反射分量 * 漫反射强度 * 物体的纹理
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//最红输出的镜面反射分量 = 光源的镜面反射分量 * 镜面反射强度 * 物体的纹理（另一张：这一张图中间部分为全黑）
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 