#version 330
smooth out vec4 vFragColor;

uniform vec4 ourColor; 

void main() { 
 
 if(dot(gl_PointCoord-0.5,gl_PointCoord-0.5)>0.25) 
   discard;
 else
   
   vFragColor = ourColor;

}
