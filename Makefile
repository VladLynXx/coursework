# Компилятор
CXX = g++
# Флаги компиляции
CXXFLAGS = -Wall -Wextra -std=c++11 -pthread
# Флаги для библиотек
LIBS = -lUnitTest++ -lcryptopp

# Общие зависимости
COMMON_SRC = client.cpp data.cpp error.cpp cli.cpp
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)

# Цели
UNIT_SRC = unit.cpp
UNIT_OBJ = $(UNIT_SRC:.cpp=.o)
UNIT_TARGET = unit

CLIENT_SRC = main.cpp
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)
CLIENT_TARGET = client

VIEW_SRC = view.cpp
VIEW_OBJ = $(VIEW_SRC:.cpp=.o)
VIEW_TARGET = view

# Правило по умолчанию
all: $(UNIT_TARGET) $(CLIENT_TARGET) $(VIEW_TARGET) clean

# Правила сборки целей
$(UNIT_TARGET): $(UNIT_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(CLIENT_TARGET): $(CLIENT_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(VIEW_TARGET): $(VIEW_OBJ) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Правила сборки объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка сгенерированных файлов
clean:
	rm -f $(UNIT_OBJ) $(CLIENT_OBJ) $(VIEW_OBJ) $(COMMON_OBJ)

.PHONY: all clean
