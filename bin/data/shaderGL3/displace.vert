// vertex shader

#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;

// custom

uniform float planeSize;
uniform sampler2DRect tex0;

out vec2 texCoordVarying;

void main(){
    vec4 modifiedPosition = modelViewProjectionMatrix * position;

    float scale = 400;

    modifiedPosition.y += ((texture(tex0, texcoord).r * scale) - scale / 2.);
    // modifiedPosition.x += ((texture(tex0, texcoord).g * scale) - scale / 2.);
    // modifiedPosition.z += ((texture(tex0, texcoord).b * scale) - scale / 2.);

    gl_Position = modifiedPosition;

    texCoordVarying = texcoord;
}