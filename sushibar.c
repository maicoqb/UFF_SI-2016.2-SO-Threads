#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
The Sushi Bar Problem
This problem was inspired by a problem proposed by Kenneth Reek [9]. Imagine
a sushi bar with 5 seats. If you arrive while there is an empty seat, you can take
a seat immediately. But if you arrive when all 5 seats are full, that means that
all of them are dining together, and you will have to wait for the entire party
to leave before you sit down.
Puzzle: write code for customers entering and leaving the sushi bar that
enforces these requirements.
*/

#define MIN_MESAS 3
#define MAX_MESAS 10
#define MAX_CLIENTES 50

typedef struct {
	int i, 
		*mesas, 
		total_mesas;
	pthread_mutex_t 
		*mutex, 
		*cheio;
	pthread_t t;
} pthread_data;

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

/* Retorna um valor aleatório para uma seed */
int getRandom( int seed, int max ) {
	srand( time(NULL) + seed );
	return rand() % max;
}

/* Faz uma espera por um determinado tempo */
void waitFor( int tempo ) {
	int i = 0;
	
	for( i = 0; i < tempo; i++ ) {
		printf(".");
		usleep( 100000 );
	}
}

void clienteChegando( int threadNum, int threadId ) {
	int tempo_chegada = 0;
	
	/* Pega um tempo aleatório de chegada  */
	/* e soma o número da thread * 10 pra deixar mais ou menos em ordem */
	tempo_chegada = getRandom( threadId, 10 ) + (threadNum * 10); 
	
	/* Faz a espera pelo tempo de chegada dos clientes */
	waitFor( tempo_chegada );
}

void clienteComendo( int threadNum, int threadId ) {
	int tempo_comendo = 0;
	
	/* Usa uma seed diferente do tempo_chegada pra evigar que fique o mesmo valor */
	tempo_comendo = getRandom( threadNum * threadId, 100 );
	
	/* Faz a espera pelo tempo que o cliente demora pra comer */
	waitFor( tempo_comendo );
}

void clientePegandoMesa( pthread_data **arg ) {
	pthread_data *data = (*arg);
	
	/* Verifica se esta cheio */
	pthread_mutex_lock( data->cheio );
	/* Dá um lock no mutex das mesas */
	pthread_mutex_lock( data->mutex );
	/* Altera o valor da mesa pra menos 1 */
	*data->mesas = *data->mesas - 1;
	/* Imprime a entrada do cliente */
	printf( "\nCliente %02d: <<<<< \n", data->i );
	/* Só pode deslocar o cheio se o número de mesas for maior que 0 */
	if ( *data->mesas > 0 ) {
		pthread_mutex_unlock( data->cheio );
		
	/* Porque se o número de mesas for menor ou igual a 0 todas as mesas estão cheias */
	} else {
		printf("\n##########: Todas as mesas estão cheias \n");
	}
	/* Dá unlock no mutex da mesa */
	pthread_mutex_unlock( data->mutex );
	
}

void clienteDeixandoMesa( pthread_data **arg ) {
	pthread_data *data = (*arg);
	
	/* Imprime que o cliente acabou de comer */
	printf( "\nCliente %02d: >>>>> \n", data->i );
	
	/* Dá lock no mutex das mesas */
	pthread_mutex_lock( data->mutex );
	/* Aumenta o valor das mesas */
	*data->mesas = *data->mesas + 1;
	/* Se o número de mesas for 5 tem que dar unlock no cheio */
	if ( *data->mesas == data->total_mesas ) {
		printf("\n##########: Todas as mesas foram liberadas\n");
		pthread_mutex_unlock( data->cheio );
	}
	/* Dá unlock no mutex das mesas */
	pthread_mutex_unlock( data->mutex );
	
}

void *arriveSushiBar(void *args)
{
	pthread_data *data;
	
	/* Pega os dados dos argumentos */
	data = (pthread_data *)args;
	
	/* Faz o atraso da chegada do cliente */
	clienteChegando( data->i, pthread_self() );
	
	/* Faz os locks e unlocks do cliente pegando uma mesa */
	clientePegandoMesa( &data );
	
	/* Faz o atraso do cliente comendo */
	clienteComendo( data->i, pthread_self() );
		
	/* Faz os locks e unlocks do cliente deixando a mesa */
	clienteDeixandoMesa( &data );
	
	return NULL;
}

int main( int argc, char* argv[] )
{
	int clientes=0,
		mesas=0, 
		total_mesas=0,
		i=0;
	pthread_data *clientes_data;
	
	pthread_mutex_t 
		mutex, 
		cheio;
	
	/* Pega o número de mesas */
	total_mesas = getInt( "Digite o número de mesas", MIN_MESAS, MAX_MESAS );
	mesas = total_mesas;
	
	/* Pega o número de clientes */
	clientes = getInt( "Digite o numero de clientes", 1, MAX_CLIENTES );
	
	/* Faz a alocação do array de dados das threads */
	clientes_data = malloc( clientes * sizeof( pthread_data ) );
	
	/* Se o array for nulo é porque deu alguma merda, */
	/* Então não deixa continuar */
	if( clientes_data == NULL ) {
		printf( "Deu erro no malloc\n" );
		exit( 1 );
	}
	
	/* Inicia os mutex */
	pthread_mutex_init( &cheio, NULL );
	pthread_mutex_init( &mutex, NULL );
	
	/* Inicia os clientes */
	printf( "Iniciando os clientes\n" );
	for( i=0; i<clientes; i++ ) {
		/* Define os valores dos argumentos da thread */
		clientes_data[i].i = i+1;
		clientes_data[i].mutex = &mutex;
		clientes_data[i].cheio = &cheio;
		clientes_data[i].mesas = &mesas;
		clientes_data[i].total_mesas = total_mesas;
		
		/* Inicia a thread do cliente */
		/* E envia os dados */
		pthread_create( &clientes_data[i].t, NULL, arriveSushiBar, (void *)&clientes_data[i] );
		
	}
	
	/* Faz o join pra esperar todas threads finalizarem */
	for( i=0; i<clientes; i++ ) {
		pthread_join( clientes_data[i].t, NULL );
	}
	
	printf("Tchau!");
	
	return 0;
}






