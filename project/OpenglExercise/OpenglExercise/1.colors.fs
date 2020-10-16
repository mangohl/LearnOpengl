#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

//这个也理解：物体最终的颜色由光源的颜色和物体自身的颜色混合而成
void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
}