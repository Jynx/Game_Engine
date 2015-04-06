#version 130

in vec2 vertexPosition;
in vec4 vertexColor;

out vec2 fragmentPosition;
out vec4 fragColor;

void main() {
    //sets the xy position of vertex of vertexPosition gl position is vec4
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    fragmentPosition = vertexPosition;
    fragColor = vertexColor;
}