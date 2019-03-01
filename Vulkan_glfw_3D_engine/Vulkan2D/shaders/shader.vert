#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    //mat4 model;
    mat4 view;
    mat4 proj;
	vec3 cameraPos;
} ubo;

layout(binding=2,set=0)buffer TRANSFORM_DATA
{
  mat4 transform[500];
} objects;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 FragPos;  
layout(location = 3) out vec3 Normal;
layout(location = 4) out vec3 cameraPos;

layout(push_constant) uniform transformData
{
  int index;
} object;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = ubo.proj * ubo.view /* ubo.model */ * objects.transform[object.index] * vec4(inPosition, 1.0);
	/*gl_Position.x = objects.transform[object.index][0][0] + objects.transform[object.index][0][1] + objects.transform[object.index][0][2] + objects.transform[object.index][0][3];
	gl_Position.x += objects.transform[object.index][1][0] + objects.transform[object.index][1][1] + objects.transform[object.index][1][2] + objects.transform[object.index][1][3];
	gl_Position.x += objects.transform[object.index][2][0] + objects.transform[object.index][2][1] + objects.transform[object.index][2][2] + objects.transform[object.index][2][3];
	gl_Position.x += objects.transform[object.index][3][0] + objects.transform[object.index][3][1] + objects.transform[object.index][3][2] + objects.transform[object.index][3][3];*/
    fragColor = inColor;
	FragPos = vec3(objects.transform[object.index] * vec4(inPosition, 1.0));
    Normal = mat3(transpose(inverse(objects.transform[object.index]))) * inNormal;;
	cameraPos = ubo.cameraPos;
    fragTexCoord = inTexCoord;
}