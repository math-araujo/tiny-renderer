# Tiny Renderer

A basic software renderer based on Sokolov's [Tiny Renderer](https://github.com/ssloy/tinyrenderer) and Gabriel Gambetta's [Compute Graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/).

> - [Description](#Description)
> - [Gallery](#Gallery)
> - [Building](#Building)

<!-- -->
## Description
This repository implements a basic software renderer including space transformations (model-view, projection and viewport), a simple rasterizer and elementary shading functions.

The code is structured to reproduce the output of each chapter of [Sokolov's book](https://github.com/ssloy/tinyrenderer), including
four types of shaders for the last chapter. The result of executing the code is 12 images, whose descriptions are given below.

Note that the implementation was incremental; therefore a posterior image likely uses the algorithms implemented on previous images (e.g. to render image 8, it's necessary to use almost all the algorithms used in images 1 to 7).


A brief summary of the images generated and the algorithms implemented:


1. __Wire frame model__: draw lines between the vertices of the triangles of the model using the [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm);

2. __Filled triangles__: fill the triangles with a random color by drawing horizontal lines between the triangle left and right ends;

3. __Back Face Culling__: discard triangles that aren't visible based on the angle between the surface normal and the view vector, and colors the visible triangles proportionaly to the dot product of these vectors;

4. __Depth Buffering__: for each pixel, determines the visible triangle (if any) by ordering the triangles using the z-coordinate, fixing the problems of the [Painter's algorithm](https://en.wikipedia.org/wiki/Painter%27s_algorithm); see more details here: [Hidden Surface Removal](https://www.gabrielgambetta.com/computer-graphics-from-scratch/12-hidden-surface-removal.html);

5. __UV Textures__: add textures to the image rendered using depth buffering and back face culling;

6. __Perspective Projection__: add [perspective projection](https://www.gabrielgambetta.com/computer-graphics-from-scratch/09-perspective-projection.html);

7. __Gouraud Perspective__: similar to the previous image, but using [Gouraud Shading](https://en.wikipedia.org/wiki/Gouraud_shading) instead of textures to color the pixels;

8. __View Transform__: add a camera transform to change the camera's point of view;

9. __Our GL__: corresponds to images 9 to 12. Uses the previous algorithms to render a model and use [shading](https://www.gabrielgambetta.com/computer-graphics-from-scratch/13-shading.html) functions, such as Gouraud, a basic texture, a tangent space normal mapping texture and [Phong shading](https://en.wikipedia.org/wiki/Phong_shading).

<!-- -->
## Gallery

**Head Model**
| | | |
| :---: | :---: | :---: |
| ![Wire frame model](images/african_head/5.line_face_model.png?raw=True) <br/> 1 - Wire frame model | ![Filled triangles](images/african_head/7.random_colored.png?raw=True) <br/> 2 - Filled triangles | ![Model with back face culling](images/african_head/8.back_face_culling.png?raw=True) <br/> 3 - Back Face Culling |
| ![Depth Buffering](images/african_head/9.depth_buffer.png?raw=True) <br/> 4 - Depth buferring | ![UV Textures](images/african_head/10.texture_depth_buffer.png?raw=True) <br/> 5 - UV Textures | ![Perspective Projection](images/african_head/11.perspective_projection.png?raw=True) <br/> 6 - Perspective Projection |
| ![Gouraud Perspective](images/african_head/12.perspective_gouraud_shading.png?raw=True) <br/> 7 - Gouraud Perspective | ![View Transformation](images/african_head/13.look_at.png?raw=True) <br/> 8 - View Transform | ![Gouraud Shading](images/african_head/14.our_gl_gouraud.png?raw=True) <br/> 9 - Our GL using Gouraud Shading | 
| ![Basic Texture](images/african_head/15.our_gl_basic_texture.png?raw=True) <br/> 10 - Our GL using Basic Texture | ![Tangent Space Normal Mapping Texture](images/african_head/16.our_gl_normal_mapping.png?raw=True) <br/> 11 - Our GL using Normal Mapping | ![Phong Illumination](images/african_head/17.our_gl_phong.png?raw=True) <br/> 12 - Our GL using Phong |



**Diablo 3 Pose**
| | | |
| :---: | :---: | :---: |
| ![Wire frame model](images/diablo3/1.diablo3_pose_wire_mesh.png?raw=True) <br/> 1 - Wire frame model | ![Filled triangles](images/diablo3/2.diablo3_pose_colored_filled_triangle.png?raw=True) <br/> 2 - Filled triangles | ![Model with back face culling](images/diablo3/3.diablo3_pose_back_face_culling.png?raw=True) <br/> 3 - Back Face Culling |
| ![Depth Buffering](images/diablo3/4.diablo3_pose_depth_buffer.png?raw=True) <br/> 4 - Depth buferring | ![UV Textures](images/diablo3/5.diablo3_pose_texture_depth_buffer.png?raw=True) <br/> 5 - UV Textures | ![Perspective Projection](images/diablo3/6.diablo3_pose_projective_perspective.png?raw=True) <br/> 6 - Perspective Projection |
| ![Gouraud Perspective](images/diablo3/7.diablo3_pose_perspective_gouraud_shading.png?raw=True) <br/> 7 - Gouraud Perspective | ![View Transformation](images/diablo3/8.diablo3_pose_look_at.png?raw=True) <br/> 8 - View Transform | ![Gouraud Shading](images/diablo3/9.diablo3_pose_our_gl_gouraud.png?raw=True) <br/> 9 - Our GL using Gouraud Shading | 
| ![Basic Texture](images/diablo3/9.diablo3_pose_our_gl_basic_texture.png?raw=True) <br/> 10 - Our GL using Basic Texture | ![Tangent Space Normal Mapping Texture](images/diablo3/9.diablo3_pose_our_gl_normal_mapping.png?raw=True) <br/> 11 - Our GL using Normal Mapping | ![Phong Illumination](images/diablo3/9.diablo3_pose_our_gl_phong.png?raw=True) <br/> 12 - Our GL using Phong |

<!-- -->
## Building

Requirements: C++17, CMake >= 3.12

`git clone https://github.com/math-araujo/tiny-renderer.git`

`cd tiny-renderer`

`cd build`

`cmake ..`

`cmake --build .` (add other CMake options as desired e.g. `cmake --build . --config Release`)

Run: for example, `Debug\main.exe` or `Release\main.exe` on MSVC or `./main` on Linux

Command-line arguments: path (parts separated by `/`) to the .obj file to be rendered e.g. `Release\main.exe obj/diablo3_pose/diablo3_pose.obj`; if no command-line argument is provided, the Head Model is used.
