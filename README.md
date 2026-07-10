# Cub3D - 42

*This project has been created as part of the 42 curriculum by  **aleconst** and **alejandj**.*

## 📝 Description

**cub3D** is a 3D graphical game engine developed in C, inspired by the classic *Wolfenstein 3D*. The core objective of this project is to explore the foundations of computer graphics, mathematics, and real-time rendering without relying on modern 3D graphics libraries.

Instead, the project utilizes **Raycasting**, a geometric technique that casts rays from the player's perspective to calculate the distance to walls and render a pseudo-3D environment from a 2D map.

### 🎮 Project Overview & Goals

The main goal of **cub3D** is to build a functional, fluid first-person navigation environment. The engine is built on top of **MiniLibX**, a simple graphics library, while solving several computer science challenges:

- **Raycasting Engine:** Simulates a 3D environment by casting one ray for each vertical screen column, calculating the distance to the nearest obstacle and rendering walls with a proportional height.

- **Map Parsing & Validation:** Includes a robust parser that reads `.cub` files, loads textures and color configurations, validates the map structure, and ensures the map is fully enclosed before rendering.

- **Real-Time Input Management:** Handles keyboard events to allow fluid, collision-checked grid movement (W, A, S, D) and camera rotation via arrow keys.

- **Bonus Features Implemented:**

    - **Interactive Minimap:** A clean 2D overlay rendered on top of the 3D scene, displaying walls, hallways, a centered representation of the player, and a directional ray indicating the current line of sight.

    - **Mouse Look:** Fluid camera rotation hooked directly to the mouse movement, to simulate a modern first-person shooter look.

    - **Doors:** Interactive door blocks (`D`) within the map layout that can be dynamically opened or closed (using `space`), affecting both the player's collision matrix and the raycasting detection loop.

## 🚀 Instructions

To build and run **cub3D**, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/Alex-M-C/cub3d.git
    ```

2. Enter the project directory:

    ```bash
    cd cub3d
    ```

3. Build the project:

    ```bash
    make
    ```

4. Run the program:

    ```bash
    ./cub3D <valid-map.cub>
    ```

## 📚 Resources

### 🔗 Documentation & References

- **42 Subject** – Official project specification.
- **MiniLibX Documentation** – Graphics library reference.
- **YouTube** – Video tutorials used to better understand raycasting, DDA, and project structure.
- **Google Images** - Used to find visual references and inspiration for textures and sprites.

### 🤖 AI Usage

Artificial intelligence was used as a supporting tool during the development of this project. It was mainly used for:

- Improving the wording and grammar of the README.
- Clarifying concepts related to the raycasting algorithm and DDA.
- Explaining C programming concepts and debugging strategies.

All the project design, implementation, debugging, and final code were developed and validated manually.