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

uniform vec2 center;

uniform int fbmOctaves, fbmWarp;

uniform float valueNoise, valueAmnt, valueScale, 
              gradientNoise, gradientAmnt, gradientScale, 
              simplexNoise, simplexAmnt, simplexScale,
              voronoiNoise, voronoiAmnt, voronoiScale,
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


// VORONOI NOISE
float voronoi2D(in vec2 st) {
  st *= voronoiScale;

	float minDist = 100.;

  vec2 gv = fract(st) - .5;
  vec2 id = floor(st);
  vec2 cid = vec2(0.);

  for (float y = -1.; y <= 1.; y++) {
    for (float x = -1.; x <= 1.; x++) {
      vec2 offset = vec2(x, y);

      vec2 n = ghash(vec2(id + offset));
      vec2 p = offset + sin(n) * .5;

      float d = length(gv-p) * length(gv-p);

      if (d < minDist) {
        minDist = d;
      }
    }
  }
  return minDist;
}


// FRACTIONAL BROWNIAN MOTION
float fbm (in vec2 st) {
    float value = 0.0;
    float amplitude = fbmHurst;
    float frequency = 0.;
    for (int i = 0; i < fbmOctaves; i++) {
      value += amplitude * (
        (valueAmnt * vnoise2D(st) * valueNoise) +
        (simplexAmnt * snoise2D(st) * simplexNoise) +
        (gradientAmnt * gnoise2D(st) * gradientNoise) +
        (voronoiAmnt * voronoi2D(st) * voronoiNoise)
      );
      st *= fbmFrequency;
      amplitude *= fbmHurst;
    }
    return value;
}

void main()
{
  vec2 st = gl_FragCoord.xy / vec2(planeSize, planeSize);

  // DOMAIN WARPING
  float k = 0.;
  float n = 0.;

  st += center;

  for (int i = 0; i < fbmWarp; i++) {
    n = fbm(st + k);
    k = n;
  }

  // COLORING
  vec3 color1 = mix(
    vec3(colorsColor1Red, colorsColor1Green, colorsColor1Blue),
    vec3(colorsColor2Red, colorsColor2Green, colorsColor2Blue),
    n
  );

  vec3 color2 = mix(
    vec3(colorsColor3Red, colorsColor3Green, colorsColor3Blue),
    vec3(colorsColor4Red, colorsColor4Green, colorsColor4Blue),
    n
  );

  vec3 color = mix(color1, color2, n);

  outputColor = vec4((n*n*n+.6*n*n+.5*n)*color, 1.);
}
