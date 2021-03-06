#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

//下面所有的向量方向都可以看成从(0,0,0)向外的
void main()
{
    // ambient 环境光照分量；直接给光照颜色乘上一个强度因子
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 漫反射光照分量（离光线方向越近，强度越强）
	//强度由光线与法线的角度来判断
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);//a*b = |a|*|b|*cos
    vec3 diffuse = diff * lightColor;
    
    // specular  镜面光照分量 模拟高光
	//光的反射向量和观察者向量的角度决定镜面光照强度
    float specularStrength = 1;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
	//用变换后的光源颜色，乘上物体颜色 得到片段的颜色
	//之前的result1 = lightColor * objectColor;  即每一片段的颜色都是一样的
	//现在的result2 = {（diff + ami + spec）*lightColor } * objectColor;  //由于每一片段的x,y,z的强度值都不同，所以每个片段的输出颜色也不同
	
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 