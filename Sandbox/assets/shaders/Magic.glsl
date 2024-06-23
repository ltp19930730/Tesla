#type vertex
#version 330 core

layout(location = 0) in vec3 aPos;
out vec2 TexCoords;
void main() {
	TexCoords = aPos.xy * 0.5 + 0.5;
	gl_Position = vec4(aPos, 1.0);
}

#type fragment
#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
    
uniform vec3 iResolution;
uniform float iTime;
uniform vec3 color1;
uniform vec3 color2;

vec3 palette(float d){
    return mix(color1,color2,d);
}

vec2 rotate(vec2 p, float a){
    float c = cos(a);
    float s = sin(a);
    return p * mat2(c, s, -s, c);
}

float map(vec3 p){
    for (int i = 0; i < 8; ++i){
        float t = iTime * 0.2;
        p.xz = rotate(p.xz, t);
        p.xy = rotate(p.xy, t * 1.89);
        p.xz = abs(p.xz);
        p.xz -= 0.5;
    }
    return dot(sign(p), p) / 5.0;
}

vec4 rm(vec3 ro, vec3 rd){
    float t = 0.0;
    vec3 col = vec3(0.0);
    float d;
    for (int i = 0; i < 64; i++){
        vec3 p = ro + rd * t;
        d = map(p) * 0.5;
        if (d < 0.02){
            break;
        }
        if (d > 100.0){
            break;
        }
        col += palette(length(p) * 0.1) / (400.0 * (d));
        t += d;
    }
    return vec4(col, 1.0 / (d * 100.0));
}

void mainImage(out vec4 fragColor, in vec2 fragCoord){
    vec2 uv = (fragCoord - (iResolution.xy / 2.0)) / iResolution.x;
    vec3 ro = vec3(0.0, 0.0, -50.0);
    ro.xz = rotate(ro.xz, iTime);
    vec3 cf = normalize(-ro);
    vec3 cs = normalize(cross(cf, vec3(0.0, 1.0, 0.0)));
    vec3 cu = normalize(cross(cs, cf));
        
    vec3 uuv = ro + cf * 3.0 + uv.x * cs + uv.y * cu;
        
    vec3 rd = normalize(uuv - ro);
        
    vec4 col = rm(ro, rd);
        
    fragColor = col;
}

void main(){
    mainImage(FragColor, gl_FragCoord.xy);
}