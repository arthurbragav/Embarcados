#include<wiringPi.h> 
#include<stdio.h>
#include<stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <softPwm.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <linux/i2c-dev.h>
unsigned int ldr=0;
int i2c_fd;
const int nconversores = 1;

void int_trata_alarme(int sig) 
{
	softPwmWrite(1,0);
}

void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}
 
void myInterrupt(void)
{
	int i=0;
	if (digitalRead(6)== 1)
		system("python push.py");
	if(ldr<740)
	{
		for (i=0;i<100;i++)
		{
			softPwmWrite(1,100);

		}
	
	}
	else
		softPwmWrite(1,0);
	alarm(30);
}

PI_THREAD (myThread)
{
	unsigned char user_input=85, msp430_ret[2*nconversores];
	unsigned int i,resultado_conversao[2*nconversores];
	while(1)
	{
	
		write(i2c_fd, &user_input, 1); //Escrevendo no msp para inciar conversao
		usleep(100); // Espera o msp terminar a conversao
		read(i2c_fd, msp430_ret, 2*nconversores); //Recebe a conversao
		for (i=0; i<nconversores;i++)
		{
			resultado_conversao[i] = (int) msp430_ret[2*i];
			resultado_conversao[i] |= (int) ((msp430_ret[2*i+1]&0x03)*256);
		}
		ldr = resultado_conversao[0]; // colocando o valor da conversao na variavel global ldr
		printf("Valor lido = %d\n",ldr);
		sleep(1);
	}


}

void setup()
{
	unsigned char rpi_addr = 0xDA, slave_addr = 0x2D;
	wiringPiSetup(); // iniciando wiring pi
	signal(SIGALRM,int_trata_alarme); // criando funcao alarm
	signal(SIGINT, ctrl_c); //criando funcao para control c
	wiringPiISR(4,INT_EDGE_FALLING,&myInterrupt);
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);	
	alarm(30); //iniciando alarm
	pinMode (1, OUTPUT); //led	
	pinMode (6, INPUT); // chave
	pinMode (4, INPUT); //sensor ivp
	softPwmCreate(1,0,100); //Criando pwm do led


	softPwmWrite(1,0); // Apagando led
	piThreadCreate(myThread);
	
}


int main()
{

	setup();
	while(1);
	return 0;
}
