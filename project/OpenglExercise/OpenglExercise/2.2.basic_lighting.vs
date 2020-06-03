#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

//片段位置，在世界空间中的顶点位置
//下面两个都是为了片段着色器使用
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
	//transpose(inverse(model))得到法线矩阵；用以把法向量转换为世界空间中的法向量；这里没有直接使用model矩阵
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    //顶点位置做变换：做到大小、位置、旋转、摄像机、透视效果
    gl_Position = projection * view * vec4(FragPos, 1.0);
}