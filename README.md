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

# Usage

1. copy the .github/workflows that you want to use
2. copy the ci/ directory to your local project
3. edit the workflow for any paths that are specific to your project (specifically extensions, excludes, etc. for style workflows)
4. edit the build scripts to match any local directory structure.
5. Set the `ci/*.sh` scripts to be executable by running: `git update-index --chmod=+x ./ci/build_libs.sh ./ci/build_examples.sh ./ci/build_dist.py`

As mentioned below, there are two style workflows. The only difference between them being that one will actually apply the style fixes inplace and commit them.

There isn't any reason to use both, and without proper sequencing the check-without-fix workflow will fail before the fix is applied, causing a false fail if using both workflows. (This can be fixed by triggering the check from the fix workflow, but it seems suitable just to choose one or the other.)

# Overview of Contents

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

### Testing Builds Locally

As long as you have a terminal capable of running sh scripts (i.e. git-bash on windows, etc.) the build libs, and the arm-none-eabi toolchain installed the build_libs and build_examples scripts will run the same as they do in the workflows.

For the build_dist.py python3 is needed. The packages used within are all part of the standard python install.

```sh

# navigate to the repo
cd path/to/DaisyActionTest

# Rebuild the libraries
./ci/build_libs.sh

# Rebuild Examples
./ci/build_examples.sh

# rewrite the dist/ folder, and provide human readable output for the content in examples/
./ci/build_dist -ru examples

```

## Style

There are currently two workflows here, one that edits and commits the fixes in place.

Both workflows use clang-format to check c++ files within the specified examples.

The `DoozyX/clang-format-lint-action@v0.11` action's exclude data can be edited to ignore additional folders that should not be linted (i.e. third party libraries, resource folders, etc.)

The only differnce between style.yml and fix_style.yml is the distinction that the latter will run clang-format action with the `inplace` attribute set to True (equivalent to running clang-format with the `-i` flag.), and then add, commit, and push those changes.

There is no sequencing built into this repo yet. So if the fix style script needs to fix things it will likely still cause the normal style check to fail. The next push will pass for both tests.

There are ways to work around this, but realisitcally it doesn't seem like both of these need to 

### Testing Style Locally

This requires that you clang-format and python installed. as it uses the local/run-clang-format.py script.

You can run a style check by running:

`./local/run-clang-format.py -r examples/`

A fix-style script will be added here as well.

There is a way to test the actual same action, but it requires setting up docker on your local machine, which is a bit outside of the scope of this project.

## Documentation

This has not been added yet, but the first pass of it will use doxygen to build documentation,
and then deploy it to the repos gh-pages branch.
