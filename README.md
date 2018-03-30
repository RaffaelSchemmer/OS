# Instruções para compilar e rodar os códigos do diretório:

- Todos os problemas que utilizam <pthread.h> devem ser compilados com a flag -pthread 
- Lembre de modificar o número de threads e o tamanho dos programas dentro do file

- Todos os problemas que utilizam <mpi.h> devem ser compilados com mpicc
- Para rodar os programas mpi utilize mpirun -np X mpiprog
- Troque X pelo número de processos a serem executados e mpiprog pelo programa mpi
- Utilize (apt install libopenmpi-dev) para instalar o mpicc e o mpirun

