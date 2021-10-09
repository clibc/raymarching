#version 330 core

#define MAX_RAY  100
#define MAX_DIST 100.0
#define MIN_DIST 0.0
#define EPS      0.01

in  vec2 tCoord;
out vec4 color;

uniform float time;

float smoothMin(float a, float b, float k){
    float h = max(k - abs(a - b), 0) / k;
    return min(a, b) - h*h*h*k * 1/6.0;
}

float sdEllipsoid( vec3 p, vec3 pos, vec3 r )
{
    float k0 = length((p-pos)/r);
    float k1 = length((p-pos)/(r*r));
    return k0*(k0-1.0)/k1;
}

float sphereSDF(vec3 point, vec3 spherePos)
{
    return length(point - spherePos) - 0.5;
}

float planeSDF(vec3 point)
{
    return point.y;
}

float sceneSDF(vec3 p) {
    float m1 = smoothMin(sphereSDF(p, vec3(cos(time) - 0.5, sin(time) +1, 4.0)), planeSDF(p), 0.4);
    float m2 = smoothMin(m1, sphereSDF(p, vec3(cos(-time) - 0.5, sin(-time) +1, 4.0)), 0.4);
    float m3 = smoothMin(m2, sdEllipsoid(p, vec3(1.,1.,4.), vec3(0.4, 0.9, 0.3)), 0.4);
    return m3;
}

float GetSceneDistance(vec3 eye, vec3 dir)
{
    float depth = MIN_DIST;

    for(int i = 0; i < MAX_RAY; ++i){
        float dist = sceneSDF(eye + depth * dir);
        depth += dist;
        if(depth>MAX_DIST || dist<EPS) break;
    }

    return depth;
}

vec3 GetNormal(vec3 p)
{
    float dist = sceneSDF(p);
    vec2 e = vec2(0.01, 0.0);

    vec3 n = dist - vec3(sceneSDF(p - e.xyy),
                         sceneSDF(p - e.yxy),
                         sceneSDF(p - e.yyx));

    return normalize(n);
}

float GetLight(vec3 p)
{
    vec3 lightPos = vec3(cos(time * 2.0), 5.0, sin(time * 3.) + 1.0);
    vec3 l = normalize(lightPos - p);
    vec3 n = GetNormal(p);

    float dif = clamp(dot(n, l), 0.0, 1.0);
    float d = GetSceneDistance(p + n * EPS * 2.0, l);
    if(d < length(lightPos - p)) dif *= 0.1;
    return dif;
}

void main()
{
    vec3 eye = vec3(0.0, 1.0, 0.0);
    vec2 uv = tCoord - 0.5;
    vec3 dir = vec3(uv.x, uv.y, 1.0);

    float dist = GetSceneDistance(eye, dir);

    float light = GetLight(eye + dir * dist);

    vec3 col = vec3(GetLight(eye + dist * dir));
    color = vec4(col, 1.0f) * vec4(0.5,0.7,0.0,1);
}
