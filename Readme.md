fastWeb is a compact C++ web engine.

Most of the settings are made in the source code.

In order to compile the project, run make in the main directory.
The binary file, along with sample files needed to run the server, will be located in build/bin. You can transfer this file to a directory convenient for you, but remember, you need at least - index.html and robots.txt. 
Also, if you want to use https, you will have to get the certificate and private key, and place it in the folder with the binary file.

launch examples:
	./fastWeb 80 nossl 
		for start HTTP

	./fastWeb 442 ssl
		for start HTTPS

in case your site uses long paths, you will have to edit the file robots/spisok.cpp and robots/spisok.h

if you want to add support for new file formats, you should edit the lists in the file HTTP/HTTP.cpp
also the processing of request forms, and adding your modules should be done in this file.

example file robots.txt:
	build/bin/robots.txt


This version does not support logs and daemon...
