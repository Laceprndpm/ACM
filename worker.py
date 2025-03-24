import os

def remove_prefix_from_filenames(directory, k):
    # 获取当前目录下的所有文件和文件夹
    for filename in os.listdir(directory):
        # 检查是否为文件
        if os.path.isfile(os.path.join(directory, filename)) and filename != "new.py":
            # 生成新的文件名，跳过前k个字符
            new_filename = filename[k:]
            # 重命名文件
            os.rename(
                os.path.join(directory, filename),
                os.path.join(directory, new_filename)
            )

# 设置要删除的字符数
k = 5  # 例如，这里设置为5，根据需要修改

# 调用函数，传入当前目录和k值
remove_prefix_from_filenames('.', k)
