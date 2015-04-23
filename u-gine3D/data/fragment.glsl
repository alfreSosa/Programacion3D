uniform sampler2D texSampler;
varying vec2 ftex;

void main(){
	gl_FragColor0 texture2D(texSampler, ftex);
}