#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//这里简单理解就是通过ourTexture即可使用到texture.cpp程序中的texture对象。
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord)* vec4(ourColor, 1.0);
}