# RPM Build Instructions

## Quick Summary

To build the RPMS (el6 and el7) for libhdfs3 simply use the provided Makefile.

```bash
make
```

## How does it work?

Everything is controlled via Makefile which does the two following things:

1. It will use docker to create the appropriate build environment (Centos 6 or 7).
2. It will then run the build using the build.sh shell script which was provided
   with libhdfs3. When it runs this it mounts the 'depends' directory in the
   incubator hawq project as we need to build google test.

## Makefile

The make file contains a few targets that can be used to build things

Target       | Description
------------ | -----------
all          | Build both el6 and el7 targets then make sure to clean up
el6          | Build libdhfs for el6 (RHEL6 & Centos 6)
el7          | Build libhdfs for el7 (RHEL7 & Centos 7)
clean        | Remove the el7 and el6 directories and then try to build again
