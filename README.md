# DirectXApplication

A graphical scene with user input created in DirectX 11 written in C++.
Build of the project can be found here: https://www.dropbox.com/sh/jjukzntio8f4kxg/AAArF7W8HrDLhCrLM_H3UQwva?dl=0

Coppies of the source files can be found in the "SourceCode" folder

Project files cna be found inside the "bin folder"

###Notable classes:

Gameobjectclass.cpp: A class created to allow model loading regardless of the graphical system being used.

RenderListclass.cpp: A class that allows for the creation of a list of gameobjects that need to be rendered. Seperate render lists can be set up for different render passes

SceneGraphObjectClass.cpp: A class that is created using a gameobject that renders it using DirectX. Could be extended to support multiple graphical systems (OpenGl for example)

ParticleSystemClass.cpp: An implementation of bilboarding particles that are depth sorted.
