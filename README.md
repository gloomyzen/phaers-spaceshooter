# towerdefense-game

Common install:
```bash
git clone --recursive git@github.com:gloomyzen/towerdefense-game.git towerdefense-game 
cd towerdefense-game
chmod +x game.sh
./game.sh --build # Create docker environments for development
```

#
```bash
./game.sh -o ubuntu bash # провалиться в терминал контейнера
npm run dev # dev сборка фронта
```

###Tips:
- for fix error "libpng warning: iCCP: known incorrect sRGB profile"
```bash
mogrify *.png
```
