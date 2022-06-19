import argparse
import os
import subprocess
import time
from pathlib import Path


def odd_numbers(n):
    return [x for x in range(0, n+1) if x%2 != 0]


def get_dir_size(path="."):
    total = 0
    with os.scandir(path) as it:
        for entry in it:
            if entry.is_file():
                total += entry.stat().st_size
            elif entry.is_dir():
                total += get_dir_size(entry.path)
    return total

odd_nums = [53]
fle = Path("metrics.txt")
fle.touch(exist_ok=True)

for dim in odd_nums:
    subprocess.call(["sh", "./cleanup.sh"])

    # Run driver script for dimension d
    start_time = time.time()
    subprocess.call(["sh", "./driver.sh", f"{dim}"])

    f = open(fle)
    f = open("metrics.txt", "a+")

    dim_output = f"Dimension: {dim}\n"
    time_output = f"Time (seconds): {time.time() - start_time}\n"
    memory_output = f"Memory {0.000001 * get_dir_size()}\n"
    
    print("***")
    print(dim_output)
    print(time_output)
    print(memory_output)
    print("***\n")

    f.write(dim_output)
    f.write(time_output)
    f.write(memory_output)
    f.close()
