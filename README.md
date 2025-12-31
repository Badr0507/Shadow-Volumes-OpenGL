# Shadow Volumes OpenGL

Real-time shadow rendering implementation using Z-Pass shadow volumes algorithm with OpenGL 3.3.

## Student Information
- **Student ID:** F23040113
- **Course:** Computer Graphics
- **Project:** Shadow Volume Rendering System

## Overview

This project implements geometrically accurate real-time shadows using the stencil shadow volume technique. The implementation employs the Z-Pass (depth-pass) algorithm with multi-pass rendering to achieve pixel-perfect shadow boundaries that dynamically respond to moving light sources.

## Features

- ✅ Real-time shadow volume generation
- ✅ Z-Pass algorithm implementation
- ✅ Dynamic point light source
- ✅ Multi-pass stencil rendering
- ✅ Silhouette edge detection
- ✅ Interactive camera controls
- ✅ OpenGL 3.3 core profile

## Technical Details

### Shadow Volume Algorithm
The system implements the Z-Pass (traditional) shadow volumes approach:
1. **Silhouette Detection:** Identifies edges where front-facing triangles adjoin back-facing triangles
2. **Volume Extrusion:** Projects silhouette edges away from light source
3. **Stencil Counting:** Uses depth-pass stencil operations to mark shadowed regions

### Rendering Pipeline
Three-pass rendering approach:
1. **Ambient Pass:** Base lighting independent of shadow
2. **Shadow Volume Pass:** Populates stencil buffer with shadow information
3. **Lighting Pass:** Applies diffuse lighting only to non-shadowed regions

### Key Components
- **Edge Table:** Precomputed topological data structure for efficient silhouette detection
- **Dynamic Generation:** Shadow volumes regenerated each frame based on light position
- **Stencil Operations:** Increment on front faces, decrement on back faces (depth pass)

## Project Structure

```
Shadow-Volumes-OpenGL/
├── src/
│   ├── main.cpp           # Main rendering loop and shadow generation
│   ├── Shader.h           # Shader compilation and management
│   └── Camera.h           # Camera controls and view matrix
├── res/
│   └── shaders/
│       ├── core.vs        # Standard vertex shader
│       ├── core.fs        # Standard fragment shader
│       ├── ambient.fs     # Ambient lighting shader
│       ├── lighting.fs    # Diffuse lighting shader
│       ├── shadow.vs      # Shadow volume vertex shader
│       ├── shadow.fs      # Shadow volume fragment shader
│       ├── light.vs       # Light source vertex shader
│       └── light.fs       # Light source fragment shader
└── README.md
```

## Dependencies

- **OpenGL 3.3+**
- **GLFW 3.x** - Window management and input
- **GLEW** - OpenGL extension loading
- **GLM** - Mathematics library for graphics

## Build Instructions

### Windows (Visual Studio)
1. Install dependencies (GLFW, GLEW, GLM)
2. Configure include directories
3. Configure library directories
4. Link libraries: `opengl32.lib`, `glfw3.lib`, `glew32.lib`
5. Build and run

### Linux
```bash
# Install dependencies
sudo apt-get install libglfw3-dev libglew-dev libglm-dev

# Compile
g++ -std=c++11 src/main.cpp -o shadow_volumes \
    -lGL -lGLEW -lglfw -I./src

# Run
./shadow_volumes
```

## Implementation Highlights

### Shadow Volume Generation
The `GenerateShadowVolume()` function (src/main.cpp, lines ~180-250):
- Transforms cube vertices to world space
- Classifies triangles as front/back-facing relative to light
- Identifies silhouette edges using edge table lookup
- Extrudes quadrilaterals from silhouette edges
- Dynamically updates GPU buffer with shadow geometry

### Edge Table Structure
```cpp
struct Edge {
    int v0, v1;         // Vertex indices
    int tri0, tri1;     // Adjacent triangle indices
};
```

The edge table explicitly encodes cube topology, enabling O(1) silhouette detection per edge.

### Stencil Operations
```cpp
// Front faces: increment on depth pass
glCullFace(GL_BACK);
glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

// Back faces: decrement on depth pass  
glCullFace(GL_FRONT);
glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
```

## Algorithm Complexity

- **Silhouette Detection:** O(E) where E = number of edges (12 for cube)
- **Volume Generation:** O(S) where S = number of silhouette edges
- **Per-Pixel Operations:** O(P) where P = screen pixels (GPU parallelized)

## Visual Results

The system produces geometrically accurate shadows with:
- Sharp, pixel-perfect shadow boundaries
- Real-time response to dynamic light movement
- Proper integration with ambient and diffuse lighting
- No shadow artifacts (acne, peter-panning)

## Academic Context

This implementation serves as a course project demonstrating:
- Advanced OpenGL rendering techniques
- Stencil buffer operations
- Multi-pass rendering architecture
- Real-time computational geometry
- GPU state management

## References

1. Everitt, C. and Kilgard, M. J. (2002). "Practical and Robust Stenciled Shadow Volumes for Hardware-Accelerated Rendering"
2. Lengyel, E. (2005). "Mathematics for 3D Game Programming and Computer Graphics"
3. OpenGL Programming Guide (Red Book) - Stencil Test chapter

## License

Academic project - Educational use only

## Contact

Student ID: F23040113
Repository: https://github.com/Badr0507/Shadow-Volumes-OpenGL
