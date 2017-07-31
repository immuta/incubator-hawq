# Centos 6 Installation Instructions

## Build Container To Build RPMs

```bash
docker build -t centos-libhdfs3 -f Dockerfile.centos6 .
```

```bash
docker run -v "`pwd`/../..":/libhdfs -it centos-libhdfs3
```

