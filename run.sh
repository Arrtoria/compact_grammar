#!/bin/zsh

# 编译 handler.c
gcc -o handler handler.c

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "Compilation successful"

    # 执行编译后的可执行文件
    ./handler

    rm handler
else
    echo "Compilation failed"
fi

