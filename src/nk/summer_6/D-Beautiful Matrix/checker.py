#!/usr/bin/env python3
import subprocess
import time
import glob
import os


def main():
    exe = "./D_unknown.O2"
    if not os.path.isfile(exe):
        print(f"可执行文件 {exe} 不存在")
        return

    files = sorted(glob.glob("*.in"), key=lambda x: int(os.path.splitext(x)[0]))
    if not files:
        print("当前目录下没有找到 *.in 文件")
        return

    for f in files:
        with open(f, "rb") as fin:
            start = time.perf_counter()
            subprocess.run(
                [exe], stdin=fin, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
            )
            end = time.perf_counter()
            elapsed = end - start
            print(f"{f}: {elapsed:.6f} s")


if __name__ == "__main__":
    main()
