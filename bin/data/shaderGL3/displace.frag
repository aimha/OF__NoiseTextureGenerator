// fragment shader

#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;

in vec2 texCoordVarying;

out vec4 outputColor;

// custom

uniform float planeSize;
uniform sampler2DRect tex0;

void main()
{
    vec2 st = gl_FragCoord.xy / vec2(planeSize, planeSize);
    vec3 color = texture(tex0, texCoordVarying.xy).rgb;

    outputColor = vec4(color, 1. );
}