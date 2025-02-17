CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = program

# 获取当前目录（pwd）
CUR_DIR := $(shell pwd)

# 查找当前目录下的所有 .c 文件
SRCS := $(wildcard $(CUR_DIR)/*.c)

# 交互式选择 `.c` 文件的脚本
SELECT_SCRIPT = /home/aethernet/Documents/workspace/A00-C/select_files.sh

# 让用户选择要编译的文件
CHOSEN_SRCS := $(shell bash $(SELECT_SCRIPT) $(SRCS))
CHOSEN_OBJS := $(CHOSEN_SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(CHOSEN_OBJS)
	$(CC) $(CFLAGS) -o $(CUR_DIR)/$(TARGET) $(CHOSEN_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CUR_DIR)/*.o $(CUR_DIR)/$(TARGET)
