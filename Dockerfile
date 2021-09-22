FROM ubuntu
#Install git
RUN apt-get update && \        
	apt-get install -y git build-essential 
RUN 	cd && \
	git clone https://github.com/ralatsdc/itu-r-propagation-models.git && \
	cd itu-r-propagation-models/src && \
	cp propa64.so /usr/lib/libpropa64.so && \
	gcc propa.c -lpropa64 -lm -o propa && \
	cp propa /usr/bin
#Set working directory
WORKDIR /root

