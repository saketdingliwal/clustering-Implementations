#!/bin/bash


if [ "$1" == "-kmeans" ]; then
    ./kmeans $2 $3 > kmeans.txt
else 
	if [ "$1" == "-dbscan" ]; then
    	./dbscan $2 $3 $4 > dbscan.txt
    else
    	./optics $2 $3 $4 > optics.txt
    	python plot.py optics.txt
    fi
fi
