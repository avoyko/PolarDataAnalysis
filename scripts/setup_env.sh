#!/bin/bash

# install tools in venv
poetry install

# install pre-commit hooks
poetry run pre-commit install --hook-type pre-commit
poetry run pre-commit install --hook-type commit-msg

# setup build directory
meson setup bld
