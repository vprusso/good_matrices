# good_matrices

The `good_matrices` package is fork of the MathCheck repo for studying good
matrices.

## Dependencies

You must have the `fftw` package installed. 

On OSX, you can install this package via `brew` as such
```
brew install fftw
```

On Debian/Ubuntu:
```
sudo apt-get install libfftw3-dev
```

If on a ComputeCanada instance, this would be invoked by `module load fftw`.

You must have the `coreutils` package installed. 

On OSX, you can install this package via `brew` as such:
```
brew install coreutils
```

The `make` utility must also be installed. 

On Debian/Ubuntu:

```
sudo apt-get install -y make
```

Python 3.9+ is required along with the `poetry` program. To install a virtual
environment with the package along with all dependencies installed, one may run
the following command:

```
poetry install
```

To invoke the virtual environment in the shell, one may run:

```
poetry shell
```

## Run

After invoking the `poetry` shell, run `python main -d 5`

