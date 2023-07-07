#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
  char name[50];
  char cpf[50];
  char address[50];
  char phone[50];
  int ticketNumber;
  int seatNumber;
  int flightNumber;
  char timer[10];
}Passenger;


int getQuantPassenger(int flight) {
	FILE *file_flight;

    char c;

    int passengers = 0;

    if (flight == 1) {
    	file_flight = fopen("../voos/1.txt","r");
    } else if (flight == 2) {
    	file_flight = fopen("../voos/2.txt","r");
    } else {
    	file_flight = fopen("../voos/3.txt","r");
    }
  
    for (c = getc(file_flight); c != EOF; c = getc(file_flight))
        if (c == '\n') 
            passengers = passengers + 1;
  
    fclose(file_flight);

    return passengers;
}

void showPassenger(Passenger passenger, int currentPassenger) {
	printf("Passageiro %d:\n", currentPassenger + 1);
	printf("\tNome: %s\n", passenger.name);
	printf("\tCPF: %s\n", passenger.cpf);
	printf("\tEndereco: %s\n", passenger.address);
	printf("\tTelefone: %s\n", passenger.phone);
	printf("\tNumero da passagem: %d\n", passenger.ticketNumber);
	printf("\tNumero da poltrona: %d\n", passenger.seatNumber);
	printf("\tNumero do voo: %d\n", passenger.flightNumber);
	printf("\tHorario do voo: %s\n", passenger.timer);
}

void showCompleteList(Passenger* passengers, int quant_passenger) {

	for (int i = 0; i < quant_passenger; i++)
	{
		if(i == 10){
			printf("\n----- Lista de espera -----\n\n");
		}

		showPassenger(passengers[i], i);
		
	}
}

void showAwaitList(Passenger* passengers, int quant_passenger) {

	for (int i = 0; i < quant_passenger; i++)
	{
		if(i < 10) {
			continue;
		}
		showPassenger(passengers[i], i - 10);
	}
}

void showPassengers(int flight, int optionShow) {
	FILE *arquivo;
    char linha[300];  // Defina um tamanho adequado para suas linhas
    Passenger passengers[15];
    int passenger = 0;

    // Abre o arquivo para leitura
    if (flight == 1) {
    	arquivo = fopen("../voos/1.txt", "r");
    } else if (flight == 2){
   		arquivo = fopen("../voos/2.txt", "r");
    } else {
    	arquivo = fopen("../voos/3.txt", "r");
    }

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê e imprime cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *ptr = strtok(linha, ",");

        while (ptr != NULL) {
        	strcpy(passengers[passenger].name, ptr);
        	ptr = strtok(NULL, ",");

        	strcpy(passengers[passenger].cpf, ptr);
        	ptr = strtok(NULL, ",");

        	strcpy(passengers[passenger].address, ptr);
        	ptr = strtok(NULL, ",");

        	strcpy(passengers[passenger].phone, ptr);
        	ptr = strtok(NULL, ",");

        	passengers[passenger].ticketNumber = atoi(ptr);
        	ptr = strtok(NULL, ",");

        	passengers[passenger].seatNumber = atoi(ptr);
        	ptr = strtok(NULL, ",");

        	passengers[passenger].flightNumber = atoi(ptr);
        	ptr = strtok(NULL, ",");

        	strcpy(passengers[passenger].timer, ptr);
        	ptr = strtok(NULL, ",");
        }

        passenger++;
    }

    if(optionShow == 1){
    	if (passenger == 0){
    		printf("Nao existem passageiros nesse voo\n");
    		return;
    	}
		showCompleteList(passengers, passenger);
    } else {
    	if (passenger < 10){
    		printf("Nao existe lista de espera para esse voo\n");
    		return;
    	}
    	showAwaitList(passengers, passenger);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

void registerPassenger(int flight) {
	
	Passenger passenger;
	FILE *file_flight;

	int quant_passenger = getQuantPassenger(flight);

	if(quant_passenger >= 15){
		printf("O voo esta cheio\n");
		return;
	}

	printf("\nNome:\n");
	getchar();
	fgets(passenger.name, 50, stdin);
	passenger.name[strcspn(passenger.name, "\n")] = 0;

	printf("\nCPF:\n");
	fgets(passenger.cpf, 50, stdin);
	passenger.cpf[strcspn(passenger.cpf, "\n")] = 0;

	printf("\nAdress:\n");
	fgets(passenger.address, 50, stdin);
	passenger.address[strcspn(passenger.address, "\n")] = 0;

	printf("\nTelefone:\n");
	fgets(passenger.phone, 50, stdin);
	passenger.phone[strcspn(passenger.phone, "\n")] = 0;

	printf("\nNumero da passagem:\n");
	scanf("%d", &passenger.ticketNumber);

	printf("\nNumero da poltrona:\n");
	scanf("%d", &passenger.seatNumber);

	printf("\nNumero do voo:\n");
	scanf("%d", &passenger.flightNumber);

	printf("\nHorario do voo:\n");
	getchar();
	fgets(passenger.timer, 10, stdin);
	passenger.timer[strcspn(passenger.timer, "\n")] = 0;


	if(flight == 1) {

	  file_flight = fopen("../voos/1.txt", "a");
	  fprintf(file_flight, "%s,%s,%s,%s,%d,%d,%d,%s\n", passenger.name, passenger.cpf, passenger.address, passenger.phone, passenger.ticketNumber, passenger.seatNumber, passenger.flightNumber, passenger.timer);
	  
	  if(quant_passenger >= 10) {
	  	printf("O passageiro foi adicionado a lista de espera\n");
	  } else {
	  	printf("O passageiro foi adicionado ao voo\n");
	  }
	} else if(flight == 2) {

	  file_flight = fopen("../voos/2.txt", "a");
	  fprintf(file_flight, "%s,%s,%s,%s,%d,%d,%d,%s\n", passenger.name, passenger.cpf, passenger.address, passenger.phone, passenger.ticketNumber, passenger.seatNumber, passenger.flightNumber, passenger.timer);
	  
	  if(quant_passenger >= 10) {
	  	printf("O passageiro foi adicionado a lista de espera\n");
	  } else {
	  	printf("O passageiro foi adicionado ao voo\n");
	  }
	} else if(flight == 3) {

	  file_flight = fopen("../voos/3.txt", "a");
	  fprintf(file_flight, "%s,%s,%s,%s,%d,%d,%d,%s\n", passenger.name, passenger.cpf, passenger.address, passenger.phone, passenger.ticketNumber, passenger.seatNumber, passenger.flightNumber, passenger.timer);
	  
	  if(quant_passenger >= 10) {
	  	printf("O passageiro foi adicionado a lista de espera\n");
	  } else {
	  	printf("O passageiro foi adicionado ao voo\n");
	  }
	}

	fclose(file_flight);	
}

int getSelectedFlight() {
	printf("\n\nSelecione um voo\n\n");
	printf("1 - BH-RIO\n");
	printf("2 - BH-SP\n");
	printf("3 - BH-BRASILIA\n");
	printf("0 - Sair\n");

	printf("\nDigite a opcao desejada: ");

	int option = 0;

	scanf("%d", &option);

	return option;
}

int getSelectedFunction(int flight) {
	printf("\nEMPRESA AEREA QUEDA LIVRE - VOO ");
	switch (flight) {
		case 1:
			printf("BH-RIO\n\n");
			break;
		case 2:
			printf("BH-SP\n\n");
			break;
		default:
			printf("BH-BRASILIA\n\n");			
	}

	printf("               MENU DE OPCOES\n\n");

	printf("[1] Mostrar a lista completa dos passageiros de um determinado voo\n");
	printf("[2] Cadastrar um passageiro na lista de determinado voo\n");
	printf("[3] Mostrar a fila de espera dos passageiros de um determinado voo\n");
	printf("[4] Testes\n");
	printf("\n\n[0] Sair");

	printf("\n\nDigite sua opcao: ");

	int option = 0;

	scanf("%d", &option);

	return option;
}

void test_showPassenger() {
    Passenger testPassenger;
    strcpy(testPassenger.name, "Teste 1");
    strcpy(testPassenger.cpf, "12345678900");
    strcpy(testPassenger.address, "Main Street");
    strcpy(testPassenger.phone, "555-1234");
    testPassenger.ticketNumber = 1234;
    testPassenger.seatNumber = 5;
    testPassenger.flightNumber = 1;
    strcpy(testPassenger.timer, "10:00");

    FILE *tmpFile = freopen("tmp_output.txt", "w", stdout);

    showPassenger(testPassenger, 0);

    fclose(tmpFile);
    freopen("/dev/tty", "w", stdout);

    FILE *tmpFileRead = fopen("tmp_output.txt", "r");

    char buffer[100];
    fgets(buffer, sizeof(buffer), tmpFileRead);

    const char expectedOutput[] = "Passageiro 1:\n";

    assert(strcmp(buffer, expectedOutput) == 0);

    fclose(tmpFileRead);
    remove("tmp_output.txt");

    printf("Test passed!\n");
}

void test_getQuantPassenger() {
	// Test file 1
	int result = getQuantPassenger(1);
	assert(result == 15);

	// Test file 2
	result = getQuantPassenger(2);
	assert(result == 15); 

	// Test file 3
	result = getQuantPassenger(3);
	assert(result == 9); 

	printf("All test cases passed!\n");
}

void test_showCompleteList() {
    Passenger testPassengers[12];

    for (int i = 0; i < 12; i++) {
        sprintf(testPassengers[i].name, "Passenger %d", i + 1);
        sprintf(testPassengers[i].cpf, "CPF%d", i + 1);
        sprintf(testPassengers[i].address, "Address%d", i + 1);
        sprintf(testPassengers[i].phone, "Phone%d", i + 1);
        testPassengers[i].ticketNumber = i + 1;
        testPassengers[i].seatNumber = i + 1;
        testPassengers[i].flightNumber = 1;
        sprintf(testPassengers[i].timer, "10:00 AM");
    }

    FILE *tmpFile = freopen("tmp_output.txt", "w", stdout);

    showCompleteList(testPassengers, 12);

    fclose(tmpFile);
    freopen("/dev/tty", "w", stdout);

    FILE *tmpFileRead = fopen("tmp_output.txt", "r");

    char buffer[100];
    fgets(buffer, sizeof(buffer), tmpFileRead);

    const char expectedOutput[] = "Passageiro 1:\n";

    assert(strcmp(buffer, expectedOutput) == 0);

    fclose(tmpFileRead);
    remove("tmp_output.txt");

    printf("Test passed!\n");
}

void test_showAwaitList() {
    Passenger testPassengers[12];

    for (int i = 0; i < 12; i++) {
        sprintf(testPassengers[i].name, "Passenger %d", i + 1);
        sprintf(testPassengers[i].cpf, "CPF%d", i + 1);
        sprintf(testPassengers[i].address, "Address%d", i + 1);
        sprintf(testPassengers[i].phone, "Phone%d", i + 1);
        testPassengers[i].ticketNumber = i + 1;
        testPassengers[i].seatNumber = i + 1;
        testPassengers[i].flightNumber = 1;
        sprintf(testPassengers[i].timer, "10:00 AM");
    }

    FILE *tmpFile = freopen("tmp_output.txt", "w", stdout);

    showAwaitList(testPassengers, 12);

    fclose(tmpFile);
    freopen("/dev/tty", "w", stdout);

    FILE *tmpFileRead = fopen("tmp_output.txt", "r");

    char buffer[100];
    fgets(buffer, sizeof(buffer), tmpFileRead);

    const char expectedOutput[] = "Passageiro 1:\n";

    assert(strcmp(buffer, expectedOutput) == 0);

    fclose(tmpFileRead);
    remove("tmp_output.txt");

    printf("Test passed!\n");
}

void test_showPassengers() {
    FILE *tmpFile = freopen("tmp_output.txt", "w", stdout);

    showPassengers(1, 1);

    fclose(tmpFile);
    freopen("/dev/tty", "w", stdout);

    FILE *tmpFileRead = fopen("tmp_output.txt", "r");

    char buffer[100];
    fgets(buffer, sizeof(buffer), tmpFileRead);

    const char expectedOutput[] = "Passageiro 1:\n";

    assert(strcmp(buffer, expectedOutput) == 0);

    fclose(tmpFileRead);
    remove("tmp_output.txt");

    printf("Test passed!\n");
}


void tests () {
	test_getQuantPassenger();
	test_showPassenger();
	test_showCompleteList();
	test_showAwaitList();
	test_showPassengers();
}

int main() {

	int option = 0;
	int flight = 0;

	do{
		system("cls");
		system("clear");

		flight = getSelectedFlight();

		if(flight == 0) {
			return 0;
		}

	}while((flight > 3) || (flight < 0));


	do{
		system("cls");
		system("clear");

		option = getSelectedFunction(flight);
	}while((option > 4) || (option < 0));

	system("cls");
	system("clear");

	switch(option){
		case 1:
			showPassengers(flight, 1);
			break;
		case 2:
			registerPassenger(flight);
			break;
		case 3:
			showPassengers(flight, 2);
			break;
		case 4:
			tests();
			break;
		default:
			return 0;
	}

	
	return 0;
}

