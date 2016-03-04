#!/bin/bash 
rm curlamazonlog
for i in `seq 1 2000`;
do
	curl -s cs360.wesleyackerman.com:3000/pic2.jpg >> curlamazonlog &
	curl -s cs360.wesleyackerman.com:3000/page.html >> curlamazonlog &
	
done    



