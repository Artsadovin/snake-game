🐍 Snake Game (Terminal Version)

Простая консольная змейка, написанная на C с использованием библиотеки ncurses.
🛠 Компиляция и запуск
Linux (Arch-based)

1 Установите необходимые зависимости:

    sudo pacman -S gcc ncurses

2 Скомпилируйте и запустите:

    gcc -o snake-game snake-game.c -lncurses
    ./snake-game

Windows (через MinGW)

1 Установите MinGW и PDCurses

2 Компиляция:

    gcc -o snake-game.exe snake-game.c -lpdcurses

🌍 Поддерживаемые ОС

    Linux (тестировалось на Arch Linux)

    macOS

    Windows (требуется PDCurses вместо ncurses)

🎮 Управление

    WASD — движение

    q — выход из игры

📝 Особенности реализации

    Использует связанный список для хранения сегментов змейки

    Реализована система роста при поедании еды

🐛 Известные проблемы

    На Windows может потребоваться ручная настройка размера терминала

    В некоторых терминалах могут некорректно отображаться символы
