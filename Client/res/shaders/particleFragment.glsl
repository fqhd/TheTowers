#version 330

in vec3 pass_color;

void main(){
    gl_FragColor = vec4(pass_color, 1.0);
}
