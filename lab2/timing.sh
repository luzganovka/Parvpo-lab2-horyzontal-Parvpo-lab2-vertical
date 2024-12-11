#!/bin/bash
for cpus in 0.5 1 1.5 2 2.5 3 3.5 4; do
  echo -en "CPUs:\t$cpus\t"; 
  sed -i 's/cpus: .*$/cpus: "'$cpus'"/' ./docker-compose.yaml; 
  docker-compose up 2>&1 | grep -E 'consumer-1.*Time'; 
done

#bash timing.sh | cut -d":" -f3 | cut -d" " -f2