# Resource Manager Service

## Overview

This project implements a `ComputePipeline` that can load resources from different sources, determine their types, and apply appropriate transformations to process them. It handles various types of resources (images, JSON, compressed files) and applies specific processing actions based on content type.

## Prerequisites to build

- C++20 compatible compiler
- CMake 3.23 or higher

## Usage

Execute with:

```bash
./ResourceManagerService
```

The program will prompt for a resource URI. Examples:

- `file://example.gz`
- `http://example.com/example.png`
- `bundle://example.json`

## Design Decisions

### Resource Management

- Used smart pointers (std::unique_ptr) to manage resource lifetimes and minimize copying
- Implemented move semantics throughout the pipeline to avoid unnecessary data copying
- Resources maintain metadata that captures processing history

### Pipeline Architecture

- Dynamic detection of resource types based on URI and content
- Extensible design that allows adding new loaders and processors without modifying existing code
- Processing stops when no applicable processor is found for a content type

### Performance Considerations

- Minimized copying through move semantics and smart pointers
- Lazy loading of processors - only instantiated when needed
- Type information maintained to enable efficient pipeline routing
- Processing stops as soon as no further transformations are applicable

### Memory Management

- RAII principles applied throughout the codebase
- Smart pointer ownership model ensures proper resource cleanup
- Pipeline stages transfer ownership of resources using move semantics

### Extensibility

The system can be extended by:

- Adding new loader types by extending BaseLoader
- Adding new processor types by extending BaseProcessor
- Registering new content types in the ContentType namespace

### Logging

A simple logging system has been implemented to log the events and errors, via `Logger` class.
