#define MAX_LIGHTS 8
uniform mat4 modelView;
uniform mat4 normalMatrix;
uniform bool lightingEnabled;
uniform bool lightEnabled[MAX_LIGHTS];
uniform vec4 lightPos[MAX_LIGHTS];
uniform vec3 lightColor[MAX_LIGHTS];
uniform float lightAtt[MAX_LIGHTS];
uniform vec3 diffuse;
uniform vec3 ambient;
uniform int shininess;

uniform mat4 MVP;
attribute vec3 vpos;
attribute vec3 vtex;
attribute vec3 vnormal;
varying vec2 ftex;

void main() {
	if (lightingEnabled) {
		vec3 combinedDiffuse = ambient;
		vec3 combinedSpecular = vec3(0,0,0);
		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
		
		}
	}
	gl_Position = MVP * vec4(vpos, 1);
	ftex = vtex;
}