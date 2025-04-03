# Компилятор и флаги
CXX = clang++
CXXFLAGS = -fsanitize=address -g -std=c++11 -Wall -Wextra -Wpedantic -fno-strict-aliasing

# Папки
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Исполняемый файл
TARGET = $(BIN_DIR)/lab2

# Список исходников
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Объектные файлы (каждый .cpp превращается в .o)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Правило сборки всего проекта
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Компиляция исходников в объектные файлы
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Создание папок
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Очистка проекта
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Полная пересборка
rebuild: clean $(TARGET)

# Запуск отладки через LLDB
debug: $(TARGET)
	lldb $(TARGET)
