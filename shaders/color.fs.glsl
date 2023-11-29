#version 150 core

in vec4 v_clr;

out vec4 color;

float near = 0.1;
float far = 50.0;

float linearize_Depth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

void main()
{
	float d = 1.0 - linearize_Depth(gl_FragCoord.z) / 50.0;
	color = vec4(d, d, d, 1.0) * v_clr;
	//color = v_clr;
}
