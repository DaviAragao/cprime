#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <getopt.h>
#include <gmp.h>
#include <pthread.h>
#include "database.h"

#ifndef NULL
#define NULL ((void *) 0)
#endif

void logMessage(char *message);
void *calcMersenne(void *interface);
char *getMacAddres();
char *getHostName();

int main(int argc, char** argv)
{
	int i, processors;
	char optc = 0;
	char interface[] = "eth0";
	pthread_t tid;

	struct option OpcoesLongas[] = {
		{"interface", required_argument, NULL, 'i'},
		{"processors", required_argument, NULL, 'p'},
		{0, 0, 0, 0}
	};

	if(argc == 1)
	{
		printf("Parâmetros faltando%c", 10);
		exit(0);
	}

	while((optc = getopt_long(argc, argv, "ip::", OpcoesLongas, NULL)) != -1) {
		switch(optc) {
			case 'i':
				strcpy(interface, optarg);
				break;
			case 'p':
				processors = atoi(optarg);
				break;
			default:
				printf("Parâmetros incorretos.%c", 10);
				exit(0);
		}
	}

	for (i = 0; i < processors; i++) {
		sleep(1);
		pthread_create(&tid, NULL, calcMersenne, (void *) interface);
	}

	pthread_exit(NULL);
}

void *calcMersenne(void *interface)
{
	int i, expoente;
	mpz_t mersenneNumber, s, aux;

	mpz_init(mersenneNumber);
	mpz_init(s);
	mpz_init(aux);

	while(true)
	{
		logMessage("Vou pegar um expoente.");

		expoente = getNextPrime();
		printf("M%d%c", expoente, 10);

		logMessage("Peguei, agora vou calcular o número de Mersenne.");

		mpz_ui_pow_ui(mersenneNumber, (long)(2), expoente);
		mpz_sub_ui(mersenneNumber, mersenneNumber, (long)(1));
		mpz_set_ui(s, (long)(4));

		logMessage("Já calculei, agora vou testar usando Lucas-Lehmer.");

		for (i = 1; i <= expoente - 2; i++)
		{
			mpz_powm_ui(aux, s, (long)(2), mersenneNumber); 
			mpz_sub_ui(s, aux, (long)(2)); 
		}

		logMessage("Está calculado, vou salvar os resultados.");

		putPrime(expoente, getMacAddres((char *) interface), getHostName(), (mpz_sgn(s) == 0));

		logMessage("Salvo!");

		if (mpz_sgn(s) == 0)
			gmp_printf("M%d%c%Zd %c%c", expoente, 10, mersenneNumber, 10, 10);
		else
			gmp_printf("%d Não é primo.%c", expoente, 10);
	}
}

char *getMacAddres(char *interface)
{
	int fd;
	struct ifreq ifr;
	char iface[] = "enp9s0";
	static char macAddres[50];
	unsigned char *mac;

	strcpy(iface, interface);
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);

	ioctl(fd, SIOCGIFHWADDR, &ifr);

	close(fd);

	mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;

	sprintf(macAddres, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	return macAddres;
}

char *getHostName()
{
	static char name[150];
	gethostname(name, 150);

	return name;
}

void logMessage(char *message)
{
	system("date");
	printf("%s%c%c", message, 10, 10);
}