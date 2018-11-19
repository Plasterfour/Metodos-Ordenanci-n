#include <stdio.h>
#include <stdlib.h>
#define Nodo struct Nodo
#define List struct lista

Nodo{
	int dato;
	Nodo*siguiente;
};

List{
	Nodo*inicio;
	Nodo*final;
}list[10];

List crearLista();
void insertarNodo(List*lista,int dato);
void recorrer(List lista);
int digitoMax(int *array,int N);
void Radix(int *array, int N);
Nodo*desencolar(List*lista);
void visualizarLista(List lista);

int main(){
	int i,digito=1,N,dato,*array;
	printf("No. de dato:");
	scanf("%i",&N);
	array=(int*)malloc(N*sizeof(int));
	printf("Ingresar datos:\n");
	for(i=0;i<N;i++){
		scanf("%i",&array[i]);
	}
	Radix(array,N);
	return 1;
}

void Radix(int *array, int N){
	int Maximo=digitoMax(array,N);
	int indice=1,i;
	Nodo*n=NULL;
	for(i=0;i<10;i++){
		list[i]=crearLista();
	}
	while(Maximo/indice>0){
		printf("------------------\n");
		printf("Nivel: %i\n",indice);
		for(i=0;i<N;i++){
			insertarNodo(&list[(array[i] / indice) % 10],array[i]);
		}
		for(i=0;i<10;i++){
			printf("%i: ",i);
			visualizarLista(list[i]);
			printf("\n");
		}
		int x=0;
		for(i=0;i<10;i++){
			do{
				n=desencolar(&list[i]);
				if(n!=NULL){
					array[x]=n->dato;
				//	printf("[%i] %i\n",x,subarray[x]);
					x++;
					free(n);
				}
			}while(n!=NULL);
		}
		printf("Lista Ordenada: ");
		for(i=0;i<N;i++){
			printf("%i ",array[i]);
		}
		printf("\n");
		indice*=10;
	}
}

Nodo*desencolar(List*lista){
	Nodo*aux;
	if(lista->inicio==NULL && lista->final==NULL){
		return NULL;
	}else{
		aux=lista->inicio;
		lista->inicio=lista->inicio->siguiente;
		aux->siguiente=NULL;
		if(lista->inicio==NULL){
			lista->final=NULL;
		}
	}
	return aux;
}

void insertarNodo(List*lista,int dato){
	Nodo*nuevo=(Nodo*)malloc(sizeof(Nodo));
	nuevo->dato=dato;
	nuevo->siguiente=NULL;
	if(lista->inicio==NULL){
		lista->inicio=nuevo;
		lista->final=nuevo;
	}else{
		lista->final->siguiente=nuevo;
		lista->final=nuevo;
	}
}

int digitoMax(int *array,int N){
	int Max=array[0],i;
	for(i=0;i<N;i++){
		if(array[i]>Max){
			Max=array[i];
		}
	}
	return Max;
}

List crearLista(){
	List lista;
	lista.inicio=NULL;
	lista.final=NULL;
	return lista;
}

void visualizarLista(List lista){
	Nodo*aux=lista.inicio;
	while(aux!=NULL){
		printf("%i ",aux->dato);
		aux=aux->siguiente;
	}
}
