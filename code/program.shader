#shader vertex 
#version 330 core
        
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float coefficient;

out vec2 texCoordFrag;
flat out float colorShadow;

uniform mat4 view;
uniform mat4 projection;

void main() {
   gl_Position = projection * view * vec4(position, 1.0f);
   texCoordFrag = texCoord;
   colorShadow = coefficient;
}

#shader fragment
#version 330 core
        
layout(location = 0) out vec4 color;

flat in float colorShadow;
in vec2 texCoordFrag;

uniform sampler2D texId;

void main() {
    color = texture(texId, texCoordFrag) * colorShadow;
}