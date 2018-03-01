__Assume-se para este tutorial que o computador configurado possui ambiente Linux.__

sudo apt-get install gcc git -y
sudo apt-get install ....

gcc server.c -lpthread -o servidor
gcc client.c -lpthread -o cliente
gcc bath.c -lpthread -o banheiro

========

[1] Executando a primitiva MUTEX
-----------

```
./banheiro


[2] Executando a primitiva SEMAFORO
-----------

```
./semaforo


[3] Executando a primitiva MPI
-----------

./matrix

```
./banheiro

[4] Executando a primitiva RPC
-----------

```
./servidor 5555
./cliente IPv4 5555
```
