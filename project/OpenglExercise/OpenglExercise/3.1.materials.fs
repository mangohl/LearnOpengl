#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
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
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;


//之前的result1 = lightColor * objectColor;  即每一片段的颜色都是一样的
//之前的result2 = {(diff + spec + amb)*lightColor } * objectColor;  等价于 {环境光分量 + 漫反射分量 + 镜面分量}  //由于每一片段的diff,spec,amb的强度值都不同，所以每个片段的输出颜色也不同   ;模拟了光的漫反射和镜面效果
//现在的result3 =  指定的分量1*强度值1 + 指定的分量2*强度值2 + 指定的分量3*强度值3
//不同之处在于分量的计算，而这里的分量值是手动设置的。这里就有个问题 就是每个片段的分量都是一样的，只是强度不同

void main()
{
    // ambient
	//光源的环境光分量和物体的环境光分量相乘（分量相乘）
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
	//光源的漫反射分量*漫反射强度*物体的漫反射分量
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//光源的镜面分量*镜面强度*物体的镜面分量
    vec3 specular = light.specular * (spec * material.specular);  
    
	//各分量相加得到片段颜色向量
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 