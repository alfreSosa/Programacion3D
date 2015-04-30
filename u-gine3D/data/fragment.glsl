uniform sampler2D texSampler;
uniform bool textEnabled;

varying vec2 ftex;
varying vec3 fcolor;

void main(){
	if (textEnabled) {
		gl_FragColor = texture2D(texSampler, ftex) * vec4(fcolor, 1);
	} else {
		gl_FragColor = vec4(fcolor, 1);
	}
}