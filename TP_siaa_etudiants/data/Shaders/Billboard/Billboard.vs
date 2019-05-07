uniform vec3 position ;

void main(void)
{
   // We compute the coordinates of the vertex
   gl_Position = gl_ProjectionMatrix * (gl_Vertex+gl_ModelViewMatrix*vec4(position,0.0)) ;
   // We transmit the texture coordinates
   gl_TexCoord[0] = gl_MultiTexCoord0 ;
}
