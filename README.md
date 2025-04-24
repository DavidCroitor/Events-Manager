# Event Manager

A Qt-based application for managing events with both admin and user interfaces.

## Features

- Event creation, modification, and deletion
- Administrative interface for event management
- User interface for browsing and registering for events
- Sorting and filtering capabilities for events
- File-based persistence for storing event data

## Technical Details

- Built with C++ and Qt 6.9.0
- Uses CMake as the build system
- Follows Model-View-Controller architecture
- Implements custom event models and views

## Building the Project

This project requires:
- Qt 6.9.0
- MinGW compiler
- CMake 3.28 or higher

### Build Steps

1. Clone the repository
2. Navigate to the project directory
3. Configure with CMake:
   ```
   cmake --preset mingw
   ```
4. Build the project:
   ```
   cmake --build build
   ```
5. Run the application:
   ```
   ./build/EventManager.exe
   ```

## Project Structure

- `Header Files/` - Contains all header files
- `Source Files/` - Contains all implementation files
- Main components:
  - Event data model
  - Repository for data access
  - Service layer for business logic
  - UI components for admin and user interfaces

## License

This project is for educational purposes.