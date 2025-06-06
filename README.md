
# animation-lib
A simple c++ library that wraps up the [Windows Animation Manager](https://learn.microsoft.com/en-us/windows/win32/api/_uianimation/) in a easy to use package. 

The current version, only covers a fraction if the functionality of Windows Animation Manager, but can still be use to make very simple animations.

### Building the Project

#### Debug

Follow these steps to build the project:

1. **Create a build directory & configure the build:**
   ```bash
   cmake -S. -Bbuild
   ```

2. **Build the project:**
   ```bash
   cmake --build build -j
   ```

#### Release

For release build use `--config Release` on Windows:

```bash
cmake -S. -Bbuild
cmake --build build -j --config Release
```

### License

MIT License. Can be used in closed-source commercial products.

