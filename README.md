# CPrime
### Cliente em C para máquinas simples trabalharem buscando números primos de mersenne.

#### Dependências:

* [GMP](https://gmplib.org/) `sudo apt-get install libgmp3-dev`.
* [libcurl](https://curl.haxx.se/libcurl/) `sudo apt-get install libcurl4-openssl-dev`.

#### Instalação:

`make; sudo make install`

#### Parâmetros:

1. Número de threads em que o processamento vai se dividir `--threads`:

`cprime --threads 2`

2. O nome da interface de rede corrente que vai requisitar os expoentes `--interface`:

`cprime --threads 2 --interface eth0`

Use sempre os dois parâmetros juntos.
