# Install deps

### SDL
*Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D*

#### Mac OS
```bash
brew install sdl2 sdl2_gfx sdl2_image sdl2_mixer sdl2_net sdl2_ttl
```

###  nlohmann/json
*JSON for Modern C++*

#### Mac OS
```bash
brew install nlohmann-json
```

#### Ubuntu
```bash
apt install nlohmann-json3-dev
```

### [tileson](https://github.com/SSBMTonberry/tileson) - A Tiled JSON parser for modern C++ (C++17) by Robin Berg Pettersen (BSD)
```bash
git clone https://github.com/SSBMTonberry/tileson.git
mkdir -p tileson/build
pushd tileson/build
cmake ../
make
popd
```
