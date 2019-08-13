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

out vec4 outputColor;

// custom

uniform float time;

float random2D(in vec2 p) {
  return fract(sin(dot(p, vec2(12.9898, 78.238))) * 43758.5453123);
}

float random3D(in vec2 p, in float t) {
  return fract(sin(dot(vec3(p, t), vec3(12.9898, 78.238, t * 0.1660292952273831))) * 43758.5453123);
}

void main()
{
    vec2 st = gl_FragCoord.xy / vec2(1920., 1200.);

    vec3 color = vec3(random3D(st.xy, time));

    outputColor = vec4(color, 1.);
}