# spaceshooter-game

Common install:
```bash
git clone git@github.com:gloomyzen/spaceshooter-game.git spaceshooter-game 
cd spaceshooter-game
chmod +x game.sh
./game.sh --build # Create docker environments for development
```

#
```bash
./game.sh -o ubuntu bash # провалиться в терминал контейнера
do-after-change "npm run emcc-dev" src/*.c resources/js/*.js # dev сборка wasm
npm run dev # dev сборка фронта
```