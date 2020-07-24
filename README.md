# towerdefense-game

Common install:
```bash
git clone --recursive git@github.com:gloomyzen/towerdefense-game.git towerdefense-game 
cd towerdefense-game
```

#Configure project
```bash
chmod +x generate.sh
./generate.sh -create win32    #create MVS project
./generate.sh -create mac      #create XCode project
```

#Using docker
```bash
chmod +x docker_run.sh
./docker_run.sh --build           # Create and run docker containers 
./docker_run.sh --run             # Run docker
./docker_run.sh --down            # Stop docker containers
./docker_run.sh -o ubuntu bash    # Open container cli
./docker_run.sh --wasm-build      # build in container
```

###Tips:
- for fix error "libpng warning: iCCP: known incorrect sRGB profile"
```bash
mogrify *.png
```
