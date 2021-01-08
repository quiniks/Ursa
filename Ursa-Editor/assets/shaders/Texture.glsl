#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec2 a_TexScale;
layout(location = 4) in float a_TexIndex;
layout(location = 5) in int a_ObjectID;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec2 v_TexScale;
out float v_TexIndex;
out flat int v_ObjectID;

void main() {
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexScale = a_TexScale;
	v_TexIndex = a_TexIndex;
	v_ObjectID = a_ObjectID;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int o_IDBuffer;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec2 v_TexScale;
in float v_TexIndex;
in flat int v_ObjectID;

uniform sampler2D u_Textures[32];

void main() {
	color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TexScale) * v_Color;
	o_IDBuffer = v_ObjectID;
}