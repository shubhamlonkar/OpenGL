All the codes are carried out on Ubuntu 12.04 LTS precise pangoline.

1) You will need to run following commands to install all required openGL packages:--

sudo apt-get install libx11-dev -y
sudo apt-get install libsoil-dev -y
sudo apt-get install mesa-common-dev -y
sudo apt-get install libglu1-mesa-dev -y

2) command to run the program:--
g++ -o ogl ogl_xwindows.cpp -lX11 -lGL -lGLU -lSOIL


3) header file for SOIL is "SOIL/SOIL.h"
   For info about SOIL visit -- http://www.lonesock.net/soil.html
  eg.  GLuint tex_2d = SOIL_load_OGL_texture("img.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
