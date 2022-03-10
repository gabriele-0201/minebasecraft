#shader vertex 
#version 330 core
        
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float coefficient;

out vec2 texCoordFrag;
flat out vec4 colorShadow;

uniform mat4 view;
uniform mat4 projection;

void main() {
   gl_Position = projection * view * vec4(position, 1.0f);
   texCoordFrag = texCoord;
   colorShadow = vec4(1.0, 1.0, 1.0, coefficient);
}

#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;

flat in vec4 colorShadow;
in vec2 texCoordFrag;

uniform sampler2D texId;

void main() {
    color = texture(texId, texCoordFrag) * colorShadow;
}