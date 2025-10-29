### Лаба2

## Сборка и запуск

# Windows
```cmd
g++ -o app.exe main.cpp Pipe.cpp CompressorStation.cpp utils.cpp search.cpp file_operations.cpp
.\app.exe
```

# Linux
```bash
g++ -o app main.cpp Pipe.cpp CompressorStation.cpp utils.cpp search.cpp file_operations.cpp
./app
```

Структура проекта
L0_gas_transport/
├──.gitignore
├── app
├── app.exe
├── CompressorStation.cpp
├── CompressorStation.h
├── CS.txt
├── data.txt
├── file_operations.cpp
├── file_operations.h
├── L0_gas_transport.cpp
├── logs.txt
├── main.cpp
├── Pipe.cpp
├── Pipe.h
├── pipe.txt
├── search.cpp
├── search.h
├── utils.cpp
├── utils.h
└── README.md