#!/usr/bin/env python3

import argparse
import subprocess


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Run the program")
    parser.add_argument("-d", help="Dimension of the board", type=int)

    args = parser.parse_args()

    dim = args.d

    if dim:
        # Run the program.
        subprocess.call(["sh", "./driver.sh", f"{dim}"])
    else:
        print("Need to provide dimension with -d")
