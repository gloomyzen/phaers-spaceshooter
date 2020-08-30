# towerdefense-game

#### First of all, be sure to clone all submodules:
```bash
git clone --recursive git@github.com:gloomyzen/towerdefense-game.git towerdefense-game 
cd towerdefense-game
```

#### Usage (WebAssembly) :
Install emscripten, then
```bash
mkdir public
cd public
emmake cmake ..
make -j$(nproc)
```

#### Usage (Linux) :

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
./main
```

#### Simple way to up and run local development (docker and bash required) :
```bash 
./docker_run.sh -r
./docker_run.sh -o ubuntu bash
build_in_container
```
Now, visit https://localhost:8080/.

More about utilities, you can read in [docs page](https://github.com/gloomyzen/tgengine/blob/master/docs/UTILITIES.md)

List of [examples](https://github.com/gloomyzen/tgengine/blob/master/docs/EXAMPLES.md)