# --- 1. KONFIGURACJA ---
CXX = g++
# Flagi:
# -Wall -Wextra -pedantic : Włącza surowe sprawdzanie błędów (Twój przyjaciel)
# -std=c++17              : Ustawia standard języka
# -g                      : Dodaje informacje dla debuggera (gdb)
# -I.                     : Szuka plików .hh w bieżącym katalogu
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g -I.

# Biblioteki (Linkujemy ncurses)
LDFLAGS = -lncurses

# Nazwa pliku wynikowego
TARGET = program

# --- 2. PLIKI ŹRÓDŁOWE ---
# Tutaj wpisujemy TYLKO pliki .cpp.
# UWAGA: Upewnij się, że masz plik 'actors.cpp' (z literą 's'), a nie 'actor.cpp'!
SRCS = main.cpp actors.cpp io.cpp logic.cpp

# Automatyczna zamiana listy .cpp na listę .o
OBJS = $(SRCS:.cpp=.o)

# --- 3. REGUŁY GŁÓWNE ---

# Domyślny cel (wpisanie 'make')
all: $(TARGET)

# Linkowanie (Sklejanie wszystkich .o w jeden program)
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Kompilacja (Zamiana każdego .cpp na .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Sprzątanie (wpisz 'make clean' żeby usunąć śmieci)
clean:
	rm -f $(OBJS) $(TARGET)

# Szybkie uruchamianie (wpisz 'make run')
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

# --- 4. ZALEŻNOŚCI ---
# To mówi make'owi: "Jeśli zmienię nagłówek X, muszę przekompilować plik Y"
# Jest to kluczowe dla poprawności działania programu po zmianach.

# Main spina wszystko, więc zależy od każdego nagłówka
main.o: main.cpp defs.hh actors.hh io.hh logic.hh

# Moduły zależą od swoich nagłówków oraz wspólnych definicji (defs.hh)
actors.o: actors.cpp actors.hh defs.hh
io.o: io.cpp io.hh defs.hh
logic.o: logic.cpp logic.hh defs.hh