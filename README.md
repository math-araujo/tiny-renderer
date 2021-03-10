# Tiny Renderer

A basic software rasterizer based on Sokolov's [Tiny Renderer](https://github.com/ssloy/tinyrenderer) and Gabriel Gambetta's [Compute Graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/).

> - [Gallery](#Gallery)
> - [Building](#Building)

<!-- -->
## Gallery

**Head Model**
| | | |
| :---: | :---: | :---: |
| ![Wire frame model](images/african_head/5.line_face_model.png?raw=True) <br/> 1 - Wire frame model | ![Filled triangles](images/african_head/7.random_colored.png?raw=True) <br/> 2 - Filled triangles | ![Model with back face culling](images/african_head/8.back_face_culling.png?raw=True) <br/> 3 - Back Face Culling |
| ![Depth Buffering](images/african_head/9.depth_buffer.png?raw=True) <br/> 4 - Depth buferring | ![UV Textures](images/african_head/10.texture_depth_buffer.png?raw=True) <br/> 5 - UV Textures | ![Perspective Projection](images/african_head/11.perspective_projection.png?raw=True) <br/> 6 - Perspective Projection |
| ![Gouraud Perspective](images/african_head/12.perspective_gouraud_shading.png?raw=True) <br/> 7 - Gouraud Perspective | ![View Transformation](images/african_head/13.look_at.png?raw=True) <br/> 8 - View Transform | ![Gouraud Shading](images/african_head/14.our_gl_gouraud.png?raw=True) <br/> 9 - Our GL using Gouraud Shading | 
| ![Basic Texture](images/african_head/15.our_gl_basic_texture.png?raw=True) <br/> 10 - Our GL using Basic Texture | ![Tangent Space Normal Mapping Texture](images/african_head/16.our_gl_normal_mapping.png?raw=True) <br/> 11 - Our GL using Normal Mapping | ![Phong Illumination](images/african_head/17.our_gl_phong.png?raw=True) <br/> 12 - Our GL using Phong Illumination |



**Diablo 3 Pose**
| | | |
| :---: | :---: | :---: |
| ![Wire frame model](images/diablo3/1.diablo3_pose_wire_mesh.png?raw=True) <br/> 1 - Wire frame model | ![Filled triangles](images/diablo3/2.diablo3_pose_colored_filled_triangle.png?raw=True) <br/> 2 - Filled triangles | ![Model with back face culling](images/diablo3/3.diablo3_pose_back_face_culling.png?raw=True) <br/> 3 - Back Face Culling |
| ![Depth Buffering](images/diablo3/4.diablo3_pose_depth_buffer.png?raw=True) <br/> 4 - Depth buferring | ![UV Textures](images/diablo3/5.diablo3_pose_texture_depth_buffer.png?raw=True) <br/> 5 - UV Textures | ![Perspective Projection](images/diablo3/6.diablo3_pose_projective_perspective.png?raw=True) <br/> 6 - Perspective Projection |
| ![Gouraud Perspective](images/diablo3/7.diablo3_pose_perspective_gouraud_shading.png?raw=True) <br/> 7 - Gouraud Perspective | ![View Transformation](images/diablo3/8.diablo3_pose_look_at.png?raw=True) <br/> 8 - View Transform | ![Gouraud Shading](images/diablo3/9.diablo3_pose_our_gl_gouraud.png?raw=True) <br/> 9 - Our GL using Gouraud Shading | 
| ![Basic Texture](images/diablo3/9.diablo3_pose_our_gl_basic_texture.png?raw=True) <br/> 10 - Our GL using Basic Texture | ![Tangent Space Normal Mapping Texture](images/diablo3/9.diablo3_pose_our_gl_normal_mapping.png?raw=True) <br/> 11 - Our GL using Normal Mapping | ![Phong Illumination](images/diablo3/9.diablo3_pose_our_gl_phong.png?raw=True) <br/> 12 - Our GL using Phong Illumination |

<!-- -->
## Building

Requirements: C++17, CMake >= 3.12

`git clone https://github.com/math-araujo/tiny-renderer.git`

`cd tiny-renderer`

`cd build`

`cmake ..`

`cmake --build .` (add other CMake options as desired e.g. `cmake --build . --config Release`)

Run: for example, `Debug\main.exe` or `Release\main.exe` on MSVC or `./main` on Linux

Command-line arguments: path (parts separated by `/`) to the .obj file to be rendered e.g. `Release\main.exe obj/diablo3_pose/diablo3_pose.obj`