#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

struct pthread_data {
	int i;
	pthread_t t;
};

pid_t gettid() {
	return syscall(SYS_gettid);
}

int getInt(char *str, int min, int max)
{
	int n;
	char *output = malloc( 255 * sizeof( char ) );
	char *none = malloc( 1 * sizeof( char ) );
	
	/* Cria a string que vai exibir pro usuario */
	sprintf( output, "%s [%d-%d]: ", str, min, max );
	do {
		/* Exibe a msg de entrada */
		printf ("%s", output );
		/* Repete enquanto o scanf for 0 */
		while( scanf ( "%d", &n ) == 0 ) {
			/* Exibe a msg de entrada */
			printf( "%s", output );
			/* Limba o buffer */
			scanf( "%s", none );
		}
	} while( n < min || n > max );
	
	return n;
}

void *olaThread(void *args)
{
	struct pthread_data *data = (struct pthread_data *)args;
	
	printf( "Thread%02u: Eu sou a thread%02u e meu ID é %02u\n", data->i, data->i, (unsigned int)data->t );
	printf( "Thread%02u: pthread_self() = %02u\n", data->i, (unsigned int)pthread_self() );
	printf( "Thread%02u: gettid() = %02u\n", data->i, gettid() );
	
	return NULL;	
}

int main( int argc, char* argv[] )
{
	int n=0, 
		i=0;
	struct pthread_data *threads_data;
	
	n = getInt("Digite o numero de threads que serão executadas", 1, 100);
	
	/* Faz a alocação do array de dados das threads */
	threads_data = malloc( n * sizeof( struct pthread_data ) );
	
	/* Se o array for nulo é porque deu alguma merda, */
	/* Então não deixa continuar */
	if( threads_data == NULL ) {
		printf( "Deu erro no malloc\n" );
		exit( 1 );
	}
	
	/* Inicia as threads */
	for( i=0; i<n; i++ ) {
		/* Define os valores dos argumentos da thread */
		threads_data[i].i = i+1;
		
		printf( "Iniciando a thread %d\n", threads_data[i].i );
		
		/* Inicia a thread na posição dela no array */
		/* E envia o identificador de criação dela */
		pthread_create( &threads_data[i].t, NULL, olaThread, (void *)&threads_data[i] );
		
		/* printf("%02u ~> %02u / %02u ~> %02u \n", &threads_data[i].t, threads_data[i].t ); */
	}
	
	/* Faz o join pra esperar todas threads finalizarem */
	for( i=0; i<n; i++ ) {
		pthread_join( threads_data[i].t, NULL );
	}
	
	printf("Tchau!");
	
	return 0;
}






