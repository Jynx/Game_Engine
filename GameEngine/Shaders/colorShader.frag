#version 130

in vec4 fragColor;
in vec2 fragmentPosition;
in vec2 fragUV;
//specifying output to screen;
out vec4 color;
//can use thisto change things over time.
uniform float time;
uniform sampler2D tex;

void main() {    
	//sampler color target, 
	//UV coordinates (texture coordinates, coords of texture for a particular pixel)
	//  |      (1,1)
	// v|
	//  |_____
	//     u
	//returns rgbv
	vec4 texColor = texture(tex, fragUV);
	//cos from 0 -1 for red
    
    color =
   	vec4(fragColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5,
        fragColor.g * (cos(fragmentPosition.y * 8.0 + time) + 1.0) * 0.5,
        fragColor.b * (cos(fragmentPosition.x * 2.0 + time) + 1.0) * 0.5,
        1.0) * texColor;

}