uniform mat4 MVP;
attribute vec3 vpos;

void main() 
{
	gl_Position = MVP * vec4(vpos, 1);
}

