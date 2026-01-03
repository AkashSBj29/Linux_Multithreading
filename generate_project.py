#!/usr/bin/env python3
import sys
from pathlib import Path


CMAKE_TEMPLATE = """cmake_minimum_required(VERSION 3.20)

project({project_name}
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

add_executable({project_name}
    main.c
)
"""


C_TEMPLATE = """
#include <stdio.h>

int main() {{
  printf("Welcome to {project_name}!\\n");

  return 0;
}}
"""


BUILD_TEMPLATE = """
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B dbuild
cmake --build dbuild --config Debug
"""


RUN_TEMPLATE = """
./dbuild/{project_name}
"""


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <project_name>")
        sys.exit(1)

    project_name = sys.argv[1]
    directory = Path(sys.argv[1])

    directory.mkdir(parents=True, exist_ok=True)

    cmake_content = CMAKE_TEMPLATE.format(project_name=project_name)
    c_content = C_TEMPLATE.format(project_name=project_name)
    build_content = BUILD_TEMPLATE.format()
    run_content = RUN_TEMPLATE.format(project_name=project_name)

    cmake_output_path = directory / "CMakeLists.txt"
    c_output_path = directory / "main.c"
    build_output_path = directory / "build.sh"
    run_output_path = directory / "run.sh"

    cmake_output_path.write_text(cmake_content)
    c_output_path.write_text(c_content)
    build_output_path.write_text(build_content)
    run_output_path.write_text(run_content)

    print(f"Generated project '{project_name}'")


if __name__ == "__main__":
    main()

