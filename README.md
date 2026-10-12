# C++ Voxel Game Engine

A work-in-progress voxel-based 3D engine built from scratch in C++ using OpenGL and GLSL. The project explores procedural terrain generation, graphics programming, texture mapping and rendering a navigable 3D environment.

## Demo

[![Watch the Voxel Game Engine demonstration](https://img.youtube.com/vi/NWVsTFaAgAE/hqdefault.jpg)](https://youtu.be/NWVsTFaAgAE)

[Watch the demonstration on YouTube](https://youtu.be/NWVsTFaAgAE)

## Features

- **Procedural terrain generation** using noise-based terrain generation.
- **Voxel rendering** to construct and display a block-based 3D world.
- **Chunk management and buffering** to organise and render world geometry.
- **Texture mapping** to give generated blocks their visual appearance.
- **Camera movement** to explore the rendered environment from different viewpoints.
- **Graphics pipeline** using OpenGL buffers, GLSL shaders and projection calculations.

## Technologies

- **C++** — engine logic and application development
- **OpenGL** — real-time graphics rendering
- **GLSL** — graphics shaders
- **GLM** — vector and matrix mathematics
- **GLFW and GLEW** — window/input handling and OpenGL functionality
- **FastNoiseLite** — procedural noise generation
- **stb_image** — image loading and texture handling

## Project Structure

- `GraphicsEngine/` — graphics engine source code, shaders, textures, dependencies and Visual Studio project files.
- `ClientTest/` — client testing project.
- `Server/` — server project and related source files.

## Building and Running

The project includes Visual Studio solution and project files and was developed in C++.

1. Clone the repository:

   ```bash
   git clone https://github.com/Plasman786/Voxel_Game_Engine.git
   ```

2. Install Visual Studio with the **Desktop development with C++** workload.
3. Open the graphics engine's `GraphicsEngine.sln` solution in Visual Studio.
4. Select the graphics engine project, choose an available build configuration, and build the solution.
5. Run the application from Visual Studio.

The project includes dependency source files. Depending on your environment, project configuration or dependency paths may require adjustment.

## About

This project is an ongoing exploration of game engine development, with a focus on understanding how procedural world data, graphics programming and rendering systems combine to create a navigable 3D environment.

**Source code:** [GitHub — Voxel_Game_Engine](https://github.com/Plasman786/Voxel_Game_Engine)
<img width="1565" height="654" alt="image" src="https://github.com/user-attachments/assets/204cd460-535b-48c9-862b-5d164660b7ca" />
