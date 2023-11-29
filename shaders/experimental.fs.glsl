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
	float x = d * d;
	//color = vec4(sin(d * 50.0) * d, cos(d * 50.0) * d, 1.0 - (d * d), 1.0);//sin(vec4(gl_FragCoord.y)*0.01*d) + cos(vec4(gl_FragCoord.x)*0.05*d) ;
	color = vec4(d + 0.5, 1.0 - (x * x), 1.0 - (x * x), 1.0);//vec4(d * x, 1.0 - d, 1.0 - x, 1.0);
}
