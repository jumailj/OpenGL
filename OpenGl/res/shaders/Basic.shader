#shader vertex

#version 330 core
layout (location = 0) in vec3 aPos;
 out vec4 vertexColor;
void main()
{
   vec4 someval = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = someval;
   vertexColor = vec4(0.5, 0.3, 0.7, 1.0);
}


#shader fragment
#version 330 core
layout (location = 0) out vec4 fgColor;
in vec4 vertexColor; 
 uniform vec4 u_Color; 

void main()
{
   fgColor = u_Color;

}

