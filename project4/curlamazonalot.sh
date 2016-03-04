#!/bin/bash 
rm output
for i in `seq 1 200`;
do
	/home/bitnami/exampleCode/project4/webtest localhost 80 /projects/test4.jpg 100 >> output 
	#ab -n 100 -c 10 localhost:80/projects/test1.html/ >>output
	
done    



