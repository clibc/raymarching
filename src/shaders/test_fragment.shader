#version 330 core

#define MAX_RAY  100
#define MAX_DIST 10000
#define MIN_DIST 0
#define EPS      0.001

in  vec2 tCoord;
out vec4 color;

float sphereSDF(in vec3 point, in vec3 spherePos){
    return length(point - spherePos) - 0.5;
}

float planeSDF(in vec3 point){
    return point.y;
}

float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

float sceneSDF(in vec3 p) {
    float m1 = min(sphereSDF(p, vec3(0.0, 2.0, 4.0)), planeSDF(p));
    float m2 = min(m1, sphereSDF(p, vec3(1.3, 2.0, 4.0)));
    return m2;
}

float GetSceneDistance(in vec3 eye, in vec3 dir, float start, float end)
{
    float depth = start;

    for(int i = 0; i < MAX_RAY; ++i){
        float dist = sceneSDF(eye + depth * dir);

        if(dist < EPS){
            return depth;
        }
        depth += dist;
        if(depth >= end){
            return end;
        }
    }

    return end;
}

void main()
{
    /* tCoord.xxyy */
    vec3 eye = vec3(0.0, 1.0, 0.0);
    vec2 uv = tCoord - 0.5;
    vec3 dir = vec3(uv.x, uv.y, 1.0);

    float dist = GetSceneDistance(eye, dir, MIN_DIST, MAX_DIST);

    if(dist > MAX_DIST - EPS){
        color = vec4(0, 0, 0, 1.0);
    }
    else {
        color = vec4(1.0, 1.0, 0.0, 1.0);
    }
}
