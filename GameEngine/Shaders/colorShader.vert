#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragUV;

void main() {
    //sets the xy position of vertex of vertexPosition gl position is vec4
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    fragPosition = vertexPosition;
    fragColor = vertexColor;
    fragUV = vertexUV;
}