# DaisyActionTest

![Build Workflow](https://github.com/stephenhensley/DaisyActionTest/workflows/Build%20All/badge.svg)
![Build Workflow](https://github.com/stephenhensley/DaisyActionTest/workflows/style/badge.svg)
![Build Workflow](https://github.com/stephenhensley/DaisyActionTest/workflows/Run%20Style%20Fix/badge.svg)

Repo to test github actions for the Daisy ecosystem

The CI pipeline used herein falls into three categories:

* Build and Deploy
* Style
* Documentation

Each of those is handled using Github Actions.

## Build And Deploy

This is the meat and potatoes of the CI process here

1. Clone the submodules
2. Setup arm compiler (arm-none-eabi-gcc)
3. Build both libDaisy and DaisySP via `./ci/build_libs.sh`
4. Build all of the examples via `./ci/build_examples.sh`
5. Setup python (python3.8) 
6. Create distributable binary files and metadata via `./ci/build_dist.py`
7. Add, commit, push the new dist/ directory

The build_libs, and build_examples scripts must be edited for the specific repo structure, 
and have no arguments or configuration.

The build_dist.py can be configured from within the workflow:

* `-r (--rewrite)` will completely remove the dist/ folder before regenerating everything, preventing stale examples with old names, etc. from remaining in the dist when that isn't the intent. This is recommended when running with CI
* `-u (--human-readable)` will add some indentation to the json output to make it a bit more human readable. This can be removed when used in CI, but can be helpful if you ever want to read the output.
* Following any optional arguments, a space-separated list of directories will control which folders are scanned for examples. This will ignore any subfolders that do not have any binary files.

## Style

There are currently two workflows here, one that edits and commits the fixes in place.

Both workflows use clang-format to check c++ files within the specified examples.

The `DoozyX/clang-format-lint-action@v0.11` action's exclude data can be edited to ignore additional folders that should not be linted (i.e. third party libraries, resource folders, etc.)

The only differnce between style.yml and fix_style.yml is the distinction that the latter will run clang-format action with the `inplace` attribute set to True (equivalent to running clang-format with the `-i` flag.), and then add, commit, and push those changes.

## Documentation

This has not been added yet, but the first pass of it will use doxygen to build documentation,
and then deploy it to the repos gh-pages branch.
