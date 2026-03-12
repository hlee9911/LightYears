# C++ SFML 2D Engine

A small 2D game engine written in C++ using SFML.  
This project explores core game engine architecture concepts such as game loops, scene management, rendering, and component-based GameObjects.

The engine includes a playable 2D scrolling spaceship bullet-hell prototype used to test gameplay systems and engine features.

## Features

- Component-based GameObject system
- Scene management
- Real-time rendering with SFML
- Input handling
- Basic 2D physics and collision
- Bullet hell gameplay prototype
- Resource management for textures and assets

## Tech Stack

- C++
- SFML
- CMake

## Architecture

The engine follows a component-based architecture similar to modern game engines.

Key systems include:

- **Application Layer** – manages the main loop and lifecycle
- **Scene System** – manages GameObjects and components
- **Rendering System** – handles sprite rendering and drawing
- **Input System** – processes keyboard input
- **Gameplay Layer** – bullet hell demo built on top of the engine

## Building

Requirements:

- C++14 compatible compiler
- CMake
- SFML

Build steps:

```plaintext
mkdir build
cd build
cmake -S .. -B .
```


## To fix linking error after making a visual studio build

1. In Visual Studio, right-click **Project** in the **Solution Explorer**.
2. Go to: Properties -> Linker -> Input -> Additional Dependencies
3. Copy and Paste the following libraries:
```plaintext
..\LightYearsEngine\Debug\LightYearsEngine.lib
..\_deps\sfml-build\lib\Debug\sfml-window-d.lib
..\_deps\sfml-build\lib\Debug\sfml-system-d.lib
..\_deps\sfml-build\lib\Debug\sfml-audio-d.lib
..\_deps\sfml-build\lib\Debug\sfml-graphics-d.lib
..\_deps\box2d-build\bin\Debug\box2d.lib
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
comdlg32.lib
advapi32.lib
```
4. Retry building
