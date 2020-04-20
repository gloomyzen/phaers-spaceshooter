# spaceshooter-game

Common install:
```bash
git clone --recursive git@github.com:gloomyzen/spaceshooter-game.git spaceshooter-game 
cd spaceshooter-game
chmod +x game.sh
./game.sh --build # Create docker environments for development
```

#
```bash
./game.sh -o ubuntu bash # провалиться в терминал контейнера
npm run dev # dev сборка фронта
```

###Examples:
- [resources/js/examples](https://github.com/gloomyzen/spaceshooter-game/tree/master/resources/js/examples)
- [resources/stub](https://github.com/gloomyzen/spaceshooter-game/tree/master/resources/stub)
- [src/examples](https://github.com/gloomyzen/spaceshooter-game/tree/master/src/examples)

###Tips:
- for fix error "libpng warning: iCCP: known incorrect sRGB profile"
```bash
mogrify *.png
```
