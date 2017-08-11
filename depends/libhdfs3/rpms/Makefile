all: el6 el7 

.PHONY: el6
el6:
	docker build -t centos6-libhdfs3 -f Dockerfile.centos6 .
	docker run -v "`pwd`/../..":/libhdfs -it centos6-libhdfs3
	mv RPMS el6
	rm -rf BUILD* SRPMS* SPECS* SOURCES*

.PHONY: el7
el7:
	docker build -t centos7-libhdfs3 -f Dockerfile.centos7 .
	docker run -v "`pwd`/../..":/libhdfs -it centos7-libhdfs3
	mv RPMS el7
	rm -rf BUILD* SRPMS* SPECS* SOURCES*

.PHONY:
clean: 
	rm -rf el7 el6 
