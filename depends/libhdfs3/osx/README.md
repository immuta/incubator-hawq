# Packging LibHdfs3 for Mac OS X
This directory contains 
- build script for osx for developign libhdfs3
- homebrew formula to install libhdfs3 on osx

## Installing libhdfs3
All you need to do is run

```bash
./install_homebrew_pkg.sh
```

What that will do is setup a local tap for immuta and then "install" our
homebrew formula into that tap. It will then run the install.
