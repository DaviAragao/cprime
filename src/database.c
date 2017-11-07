#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "database.h"

char *response;
int responsePosition;

int getNextPrime(void)
{
	generateGetRequest();
	return atoi(getPrimeToJson());
}

bool putPrime(int prime, char *macAddres, char* name, bool mersenne)
{
	return generatePutRequest(makePutJson(macAddres, name, mersenne), prime);
}

const char *makePutJson(char *macAddres, char* name, bool mersenne)
{
	static char body[110];
	sprintf(body, "{\"calc\": 2, \"machine\": {\"clientType\": 1,\"macAddres\": \"%s\",\"name\": \"%s\"},\"mersenne\": %d}", macAddres, name, mersenne);

	return body;
}

void writefunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	response = (char *) ptr;
}

bool generatePutRequest(const char *body, int prime)
{
	struct curl_slist *headers = NULL;
	char url[100];
	CURL *curl;
	CURLcode res;

	sprintf(url, "%s%d", API, prime);

	curl = curl_easy_init();
	headers = curl_slist_append(headers, "Content-Type: application/json");
	
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);

	res = curl_easy_perform(curl);
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return res == CURLE_OK;
}


void generateGetRequest(void)
{
	CURL *curl;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, API);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

char *getPrimeToJson()
{
	return getValueFromKey("nextPrime");
}

char *getValueFromKey(char *key)
{
	char *value;
	responsePosition = 0;
	while((strcmp(getNetxValue(), key) != 0) && (responsePosition < strlen(response)));
	value = getNetxValue();
	return value;
}

char *getNetxValue()
{
	int initialPosition = 0, finalPosition = 0;
	char *nextValue;

	while(finalPosition == 0)
	{
		if (response[responsePosition] == 34)
		{
			if (initialPosition == 0)
			{
				initialPosition = responsePosition;
			}
			else
			{
				finalPosition = responsePosition;
				nextValue = substr(response, ++initialPosition, finalPosition);
			}
		}
		responsePosition++;
	}

	return nextValue;
}

char *substr(char *str, int offset, int len)
{
	char *newStr = malloc(len - offset);
	strncpy(newStr, str + offset, len - offset);
	newStr[len - offset] = '\0';
	return newStr;
}
