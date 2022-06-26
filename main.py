import argparse
import subprocess


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Run the program")
    parser.add_argument("-d", help="Dimension of the board", type=int)

    args = parser.parse_args()

    dim = args.d

    # Update MAX_N to the dimension specified (prevents unnecessary memory
    # allocation).
    with open("constants.h", "w") as f:
        f.write(f"#define MAX_N {dim}\n")
        f.write(f"#define HALF_MAX_N 1+MAX_N/2\n")

    # Run the program.
    subprocess.call(["sh", "./driver.sh", f"{dim}"])
