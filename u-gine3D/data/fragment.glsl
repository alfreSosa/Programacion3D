uniform sampler2D texSampler;
uniform bool textEnabled;
uniform bool shadowsEnabled;
uniform sampler2D depthSampler;
uniform vec3 ambient;

varying vec3 depthCoord;
varying vec2 ftex;
varying vec3 fcolor;

void main()
{
	vec4 shadowColor = vec4(1, 1, 1, 1);
	if ( shadowsEnabled && texture2D(depthSampler, vec2(depthCoord)).z < depthCoord.z - 0.0009)
		shadowColor = vec4(ambient, 1);

	if (textEnabled) {
		gl_FragColor = texture2D(texSampler, ftex) * vec4(fcolor, 1) * shadowColor;
	} else {
		gl_FragColor = vec4(fcolor, 1) * shadowColor;
	}
}