import re
import subprocess
from pathlib import Path
from argparse import ArgumentParser, Namespace

import tqdm
import numpy as np
from scipy.optimize import linear_sum_assignment


def main(opt: Namespace) -> None:
    exec_path: Path = opt.exec_path
    assert exec_path.exists() and exec_path.is_file(), IOError(
        f"Execution File does not exist in `{exec_path}`"
    )

    array_size_pattern = re.compile(r"Cost matrix is initialized \(([\d]+) x ([\d]+)\)")
    data_pattern = re.compile(r"([\d\.]+)")
    result_pattern = re.compile(r"\(([\d+]), ([\d+])\)")

    for _ in tqdm.tqdm(range(opt.num_iter), dynamic_ncols=True):
        lines = iter(
            line.strip()
            for line in subprocess.getoutput(f"{opt.exec_path}").split("\n")
            if line.strip()
        )

        num_rows, num_cols = map(int, array_size_pattern.search(next(lines)).groups())
        cost_matrix = np.zeros((num_rows, num_cols), np.float32)

        for idx in range(num_rows):
            data = data_pattern.findall(next(lines))
            assert len(data) == num_cols, ValueError(
                f"not enough values (expected {num_cols}, got {len(data)})"
            )
            cost_matrix[idx, :] = list(map(float, data))

        next(lines)
        cpp_results = []
        for row, col in result_pattern.findall(next(lines)):
            row, col = map(int, (row, col))
            cpp_results.append((row, col))

        scipy_results = []
        for i, j in zip(*linear_sum_assignment(cost_matrix)):
            scipy_results.append((i, j))

        if cpp_results != scipy_results:
            print(cost_matrix)
            print(cpp_results)
            print(scipy_results)
            break


if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument(
        "--exec_path",
        type=Path,
        default="./install/hungarian_munkres/hungarian_munkres",
    )
    parser.add_argument(
        "--num_iter",
        type=int,
        default=10000,
    )
    main(parser.parse_args())
