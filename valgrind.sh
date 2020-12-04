g++ -Wall -pthread -g src/*.cpp -o OSSim && valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./OSSim templates/terminal.txt 3
