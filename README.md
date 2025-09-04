# ft_scop

A 3D graphics project using OpenGL, GLFW, and GLAD.

## Dependencies

### Ubuntu/Debian
```bash
make install-deps
```

### Arch Linux
```bash
make install-deps-arch
```

### Fedora/CentOS/RHEL
```bash
make install-deps-fedora
```

## Setting up GLAD

1. Go to [GLAD web service](https://glad.dav1d.de/)
2. Select:
   - Language: C/C++
   - Specification: OpenGL
   - API version: 3.3+ (or your preferred version)
   - Profile: Core
3. Generate and download the files
4. Extract `glad.c` to the `srcs/` directory
5. Extract the `glad/` and `KHR/` folders to `libs/glad/include/`

Or run:
```bash
make setup-glad
```

## Building

```bash
# Build the project
make

# Build with debug information
make debug

# Clean object files
make clean

# Clean everything
make fclean

# Rebuild
make re
```

## Running

```bash
./ft_scop
```

## Project Structure

```
ft_scop/
├── Makefile
├── srcs/           # Source files
│   ├── main.c
│   └── glad.c      # GLAD loader (download separately)
├── includes/       # Header files
├── libs/           # External libraries
│   └── glad/
│       └── include/
│           ├── glad/
│           └── KHR/
└── objs/           # Object files (generated)
```

## Features

- OpenGL 3.3+ Core Profile
- GLFW for window management
- GLAD for OpenGL function loading
- Cross-platform support (Linux, macOS)
- Debug build configuration
- Automatic dependency detection with pkg-config
