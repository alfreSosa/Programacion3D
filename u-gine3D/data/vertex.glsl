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
attribute vec2 vtex;
attribute vec3 vnormal;
varying vec2 ftex;
varying vec3 fcolor;

void main() 
{
	if (lightingEnabled) 
	{
		vec3 combinedDiffuse = ambient;
		vec3 combinedSpecular = vec3(0,0,0);
		vec3 vposObserver = modelView * vec4(vpos, 1);
		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			if (lightEnabled[i]) 
			{
				vec3 n = normalMatrix * vec4(vnormal, 0);
				vec3 l = lightPos[i];
				float atenuationFactor = 1;
				
				if (lightPos[i].w == 1) 
				{
					l -= vposObserver;
					atenuationFactor = 1 / (1 + lightAtt[i] * length(l));
				}
				vec3 nl = normalize(l);
				float NdotL = max(dot(n, nl), 0.0);
				combinedDiffuse += NdotL * atenuationFactor * lightColor[i];
				if (shininess > 0 && NdotL > 0)
				{
					vec3 h = nl - normalize(vposObserver);
					float NdotH = max(dot(n, normalize(h)), 0.0);
					combinedSpecular += pow(NdotH, shininess) * atenuationFactor;
				}
				
			}
		}
		fcolor = diffuse * combinedDiffuse + combinedSpecular;
	}else
	{
		fcolor = diffuse;
	}
	gl_Position = MVP * vec4(vpos, 1);
	ftex = vtex;
}