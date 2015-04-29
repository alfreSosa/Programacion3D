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

void main() 
{
	if (lightingEnabled) 
	{
		vec3 combinedDiffuse = ambient;
		vec3 combinedSpecular = vec3(0,0,0);
		for (int i = 0; i < MAX_LIGHTS; ++i)
		{
			vec4 vnormalAux = vec4(vnormal.x, vnormal.y, vnormal.z, 0);
			vec4 n = normalMatrix * modelView * vnormalAux;
			vec4 l = lightPos[i];
			float atenuationFactor = 1;
			if (l.w == 1) 
			{
				l.x -= vpos.x;
				l.y -= vpos.y;
				l.z -= vpos.z;
				atenuationFactor = 1 / (1 + lightAtt[i] * length(l));
				vec3 nl = normalize(l);
				float NdotL = max(dot(n, nl), 0.0);
				combinedDiffuse += NdotL * atenuationFactor * lightColor[i];
				if (shininess > 0 && NdotL > 0)
				{
						vec4 vposlAux = vec4(vpos.x, vpos.y, vpos.z, 1);
						vec4 nvpos = normalMatrix * modelView * vposlAux;
						vec4 h = l - nvpos;
						float NdotH = max(dot(n, h), 0.0);
						if (NdotH > 0)
							combinedSpecular += pow(NdotH, shininess) * atenuationFactor;
				}
			}
		}
	}

	gl_Position = MVP * vec4(vpos, 1);
	ftex = vtex;
}