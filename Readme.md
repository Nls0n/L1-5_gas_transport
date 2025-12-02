### Лаба2

## Сборка и запуск

# Windows
```cmd
g++ -o app.exe .\compressor_station.cpp .\pipe.cpp .\search_utils.cpp .\utils.cpp .\main.cpp
.\app.exe
```

# Linux
```bash
g++ -o app main.cpp Pipe.cpp CompressorStation.cpp utils.cpp search.cpp file_operations.cpp
./app
```

Структура проекта
L0_gas_transport/
- .gitignore                 # Git ignore rules
- app                        # Linux executable
- app.exe                    # Windows executable
- CompressorStation.cpp      # CS class implementation
- CompressorStation.h        # CS class header
- data.txt                   # General data file
- file_operations.cpp        # File operations implementation
- file_operations.h          # File operations header
- L0_gas_transport.cpp       # Main program file
- logs.txt                   # Program logs
- main.cpp                   # Entry point
- Pipe.cpp                   # Pipe class implementation
- Pipe.h                     # Pipe class header
- pipe.txt                   # Pipe data file
- search.cpp                 # Search functions implementation
- search.h                   # Search functions header
- utils.cpp                  # Utilities implementation
- utils.h                    # Utilities header
- README.md                  # Project documentation
