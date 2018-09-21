#!/bin/bash


case "$1" in 
	-kmeans) ./kmeans $2 $3 > kmeans.txt ;;
	-dbscan) ./dbscan $2 $3 $4 > dbscan.txt ;;
	-optics) ./optics $2 $3 $4 > optics.txt ; python plot.py optics.txt;;
esac

# if [ "$1" != "-kmeans" ]; then
    
# else 
# 	if [ "$1" != "-dbscan" ]; then
#     	./dbscan $2 $3 $4 > dbscan.txt
#     else
#     	./optics $2 $3 $4 > optics.txt
#     	python plot.py optics.txt
#     fi
# fi
