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

uniform float time, planeSize, seed;

uniform float valueScale, gradientScale, simplexScale,
              valueAmnt, gradientAmnt, simplexAmnt,
              fbmHurst, fbmFrequency,
              colorsColor1Red, colorsColor1Green, colorsColor1Blue,
              colorsColor2Red, colorsColor2Green, colorsColor2Blue,
              colorsColor3Red, colorsColor3Green, colorsColor3Blue,
              colorsColor4Red, colorsColor4Green, colorsColor4Blue;

/**************************************************************/

// PALETTE


// HASH FUNCTIONS
float vhash (uvec2 x) {
  uvec2 q = 1103515245U * ((x>>1U) ^ (x.yx));
  uint n = 1103515245U * ((q.x) ^ (q.y>>3U));
  return float(n) * (1. / float(0xffffffffU));
}

vec2 ghash (vec2 x) {
  const vec2 k = vec2(0.3183099, 0.3678794);
  x = x*k + k.yx + seed;
  return -1.0 + 2.0 * fract(16.0 * k * fract(x.x * x.y * (x.x + x.y)));
} 

// VALUE NOISE
float vnoise2D(in vec2 st) {
  st *= valueScale;

  vec2 ipos = floor(st);
  vec2 fpos = fract(st);

  uvec2 i = uvec2(ipos.x, ipos.y);

  float a = vhash(i);
  float b = vhash(i + uvec2(1., 0.));
  float c = vhash(i + uvec2(0., 1.));
  float d = vhash(i + uvec2(1., 1.));

  vec2 u = smoothstep(0., 1., fpos);

  return mix(
    mix(a, b, u.x),
    mix(c, d, u.x),
    u.y
  );
}

// GRADIENT NOISE
float gnoise2D(vec2 st) {
  st *= gradientScale;

  vec2 ipos = floor(st);
  vec2 fpos = fract(st);

  float a = dot(ghash(ipos + vec2(0., 0.)),fpos - vec2(0., 0.));
  float b = dot(ghash(ipos + vec2(1., 0.)), fpos - vec2(1., 0.));
  float c = dot(ghash(ipos + vec2(0., 1.)), fpos - vec2(0., 1.));
  float d = dot(ghash(ipos + vec2(1., 1.)), fpos - vec2(1., 1.));

  vec2 u = smoothstep(0., 1., fpos);

  return mix(
    mix(a, b, u.x),
    mix(c, d, u.x),
    u.y
  );
}

// SIMPLEX NOISE
float snoise2D (vec2 st) {
  st *= simplexScale;

  const float K1 = 0.366025404;                 // (sqrt(3)-1)/2;
  const float K2 = 0.211324865;                 // (3-sqrt(3))/6;
    
	vec2  i = floor( st + (st.x + st.y) * K1 );   // integer part
  vec2  a = st - i + (i.x + i.y) * K2;          // fract part

    
    float m = step(a.y, a.x);                   // which triangle we are in
    vec2 o = vec2(m,1.0-m);                     // origin selector
    
    vec2  b = a - o + K2;                       // distance between a and the origin
    vec2  c = a - 1.0 + 2.0 * K2;               // distance between a and other vertex
    
    vec3  h = max( 0.5 - vec3(                  // kernel
      dot(a,a),                               // same as magnitude squared
      dot(b,b),                               // same as magnitude squared
      dot(c,c)                                // same as magnitude squared
    ), 0.0 );
    
    
    vec3  n = h*h*h*h*vec3(
      dot(a, ghash( i + 0.)),                 // gradient computation
      dot(b, ghash( i + o)),                  // gradient computation
      dot(c, ghash( i + 1.0))                 // gradient computation
    );
    
    return dot( n, vec3(70.) );              // scaling up the noise
}

// FRACTIONAL BROWNIAN MOTION
#define OCTAVES 8
float fbm (in vec2 st) {
    float value = 0.0;
    float amplitude = fbmHurst;
    float frequency = 0.;
    for (int i = 0; i < OCTAVES; i++) {
      value += amplitude * (
        (valueAmnt * vnoise2D(st)) +
        (simplexAmnt * snoise2D(st)) +
        (gradientAmnt * gnoise2D(st))
      );
      st *= fbmFrequency;
      amplitude *= fbmHurst;
    }
    return value;
}

void main()
{
  vec2 st = gl_FragCoord.xy / vec2(planeSize, planeSize);

  float n = fbm(st + fbm(st + fbm(st + fbm(st)))); // DOMAIN WARPING

  vec3 color1 = mix(
    vec3(colorsColor1Red, colorsColor1Green, colorsColor1Blue),
    vec3(colorsColor2Red, colorsColor2Green, colorsColor2Blue),
    n
  );

  vec3 color2 = mix(
    vec3(colorsColor3Red, colorsColor3Green, colorsColor3Blue),
    vec3(colorsColor4Red, colorsColor4Green, colorsColor4Blue),
    1. - n
  );

  vec3 color = mix(color1, color2, n);

  outputColor = vec4(color, 1.);
}