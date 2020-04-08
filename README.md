# spaceshooter-game

Common install:
```bash
git clone git@github.com:gloomyzen/spaceshooter-game.git spaceshooter-game 
cd spaceshooter-game
chmod +x game.sh
./game.sh --build # Create docker environments for development
./game.sh --dev file.cpp run.cpp ... # Compile files
```

#
```bash
do-after-change "npm run emcc-dev" src/*.c # dev сборка wasm
npm run dev # dev сборка фронта
```