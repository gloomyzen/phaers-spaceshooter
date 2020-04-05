# spaceshooter-game

Common install:
```
#> git clone git@github.com:gloomyzen/spaceshooter-game.git spaceshooter-game 
#> cd spaceshooter-game
#> chmod +x game.sh
#> ./game.sh --build # Create docker environments for development
#> ./game.sh --dev file.cpp run.cpp ... # Compile files
```

#
###Последовательность сборки:
1. Собираем верстку и стили 
    - resources/sass -> public/css
    - resources/js -> public/js
    - resources/img -> public/img
2. Собираем WASM 
    - src/* -> resources/temp
3. Финальная сборка...