#shader vertex 
#version 330 core
        
layout(location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 projection;

void main() {
   gl_Position = projection * view * vec4(position, 1.0f);
}

#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;


void main() {
    color = vec4(0.8f, 0.8f, 0.8f, 1.0f);
}