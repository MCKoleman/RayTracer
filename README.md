# Ray Tracer
This program is a very simple raytracing application made using OpenGL. The core libraries used are GLEW, GLFW, and GLM.

## Compilation
The project uses CMake to build. Running the CMake GUI application and selecting the project's root directory, ie. `<location>/RayTracer/` as the source code location, and `<location>/RayTracer/build` as the build location, and then running `configure` and `generate` allows the user to create visual studio project files for the project. After these files are generated, the program can be opened in visual studio by opening the `RayTracer.sln` project file. To build the program in visual studio, right click the 'RayTracer' project inside the solution hierarchy in visual studio and select `Set as startup project`. Finally, right click the 'RayTracer' project, select properties, and in the 'Configuration Properties >> Linker >> Input' section, add `glew32s.lib` to the 'Additional Dependencies' field. Now the project can be recompiled by pressing F7 or selecting 'Build >> Build Solution' in Visual Studio.

## Operation
Press 1 to between the orthographic (default) and perspective cameras.
Press W, A, S, D, Space, and Shift to move the camera forward, left, back, right, up, and down respective to world space (not camera space).
Press 0 to refresh the screen (not necessary when using any other input).
Press 2 to toggle mirror reflections on and off.
Press 3 to toggle shadows on and off.
Press 4 to toggle ambient lighting on and off.
Press 5 to toggle diffuse lighting on and off.
Press 6 to toggle specular lighting on and off.
Press Esc to exit the program.

## Links to libraries:
http://glew.sourceforge.net/

https://www.glfw.org/

https://github.com/g-truc/glm
