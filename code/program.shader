#shader vertex 
#version 330 core
        
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;

out vec2 texCoordFrag;

void main() {
   gl_Position = projection * view * vec4(position, 1.0f);
   texCoordFrag = texCoord;
}

#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;

uniform sampler2D texId;

in vec2 texCoordFrag;

void main() {
    color = texture(texId, texCoordFrag);
}