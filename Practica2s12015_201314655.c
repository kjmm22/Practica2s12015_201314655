#include <stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>
#include <windows.h>



/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}



//DECLARANDO MI ARBOL AVL ARBOL BINARIO DE BUSQUEDA EQUILIBRADO

struct nodoArbolAVL {
    
	int date;
	struct nodoArbolAVL *node_izq;
	struct nodoArbolAVL *node_der;
	int alturaArbol;
};

int alturaArbol(struct nodoArbolAVL *H) {
	if (H == NULL)
		return 0;
	return H->alturaArbol;
}

struct nodoArbolAVL* new_nodoAVL(int dato) {
	struct nodoArbolAVL* nodoAVL = (struct nodoArbolAVL*) malloc(sizeof(struct nodoArbolAVL));
	nodoAVL->date = dato;
	nodoAVL->node_izq = NULL;
	nodoAVL->node_der = NULL;
	nodoAVL->alturaArbol = 1;
	return (nodoAVL);
}

int comparaAltura(int num, int num1) {
	if (num > num1)
            return num;
	else
            return num1;
}

struct nodoArbolAVL *rotacionDD(struct nodoArbolAVL *h) {
	struct nodoArbolAVL *raiz = h->node_izq;
	struct nodoArbolAVL *newder = raiz->node_der;

	raiz->node_der = h;
	h->node_izq = newder;

	h->alturaArbol = comparaAltura(alturaArbol(h->node_izq), alturaArbol(h->node_der)) + 1;
	raiz->alturaArbol = comparaAltura(alturaArbol(raiz->node_izq), alturaArbol(raiz->node_der)) + 1;

	return raiz;
}

struct nodoArbolAVL *rotacionII(struct nodoArbolAVL *raiz) {
	struct nodoArbolAVL *newder = raiz->node_der;
	struct nodoArbolAVL * newizq= newder->node_izq;
        newder->node_izq = raiz;
	raiz->node_der = newizq;
	raiz->alturaArbol = comparaAltura(alturaArbol(raiz->node_izq), alturaArbol(raiz->node_der)) + 1;
	newder->alturaArbol = comparaAltura(alturaArbol(newder->node_izq), alturaArbol(newder->node_der)) + 1;

	return newder;
}

int verificaFactorEquilibrio(struct nodoArbolAVL *N) {
	if (N == NULL)
		return 0;
	return alturaArbol(N->node_izq) - alturaArbol(N->node_der);
}

struct nodoArbolAVL* insertAVL(struct nodoArbolAVL* nodoAVL, int dato) {
	if (nodoAVL == NULL)
            return (new_nodoAVL(dato));

	if (dato < nodoAVL->date)
            nodoAVL->node_izq = insertAVL(nodoAVL->node_izq, dato);
	else
            nodoAVL->node_der = insertAVL(nodoAVL->node_der, dato);
            nodoAVL->alturaArbol = comparaAltura(alturaArbol(nodoAVL->node_izq), alturaArbol(nodoAVL->node_der)) + 1;

	int fe = verificaFactorEquilibrio(nodoAVL);

	if (fe > 1 && dato < nodoAVL->node_izq->date)
		return rotacionDD(nodoAVL);
        if (fe < -1 && dato > nodoAVL->node_der->date)
		return rotacionII(nodoAVL);
        if (fe > 1 && dato > nodoAVL->node_izq->date) {
		nodoAVL->node_izq = rotacionII(nodoAVL->node_izq);
		return rotacionDD(nodoAVL);
	}
        if (fe < -1 && dato < nodoAVL->node_der->date) {
		nodoAVL->node_der = rotacionDD(nodoAVL->node_der);
		return rotacionII(nodoAVL);
	}

	return nodoAVL;
}

void recorridoInOrden(struct nodoArbolAVL *raiz) {
	if (raiz != NULL) {

		recorridoInOrden(raiz->node_izq);
		printf("%d ", raiz->date);
		recorridoInOrden(raiz->node_der);
	}
}

void devuelveTiempoInOrden(struct nodoArbolAVL *raiz) {
	if (raiz != NULL) {

		devuelveTiempoInOrden(raiz->node_izq);
		devuelveTiempoInOrden(raiz->node_der);
	}
}

void recorridoPreOrden(struct nodoArbolAVL *raiz)
{
    if(raiz != NULL)
    {
        printf("%d ", raiz->date);
        recorridoPreOrden(raiz->node_izq);
        recorridoPreOrden(raiz->node_der);
    }
}

void recorridoPostOrden(struct nodoArbolAVL *raiz)
{
    if(raiz != NULL)
    {
        printf("%d ", raiz->date);
        recorridoPostOrden(raiz->node_izq);
        recorridoPostOrden(raiz->node_der);
    }
}


void ordenamientoBubbleSort(int arrayBubble[],int n){
    int i,j,temp;
    for (i = 1; i < n; i++) {
      for (j = 0; j < n - 1; j++) {
         if (arrayBubble[j] > arrayBubble[j + 1]) {
            temp = arrayBubble[j];
            arrayBubble[j] = arrayBubble[j + 1];
            arrayBubble[j + 1] = temp;
         }
      }
    }
}

void ordenamientoQuicksort(int arrayQuick[], int primero, int ultimo)
{
    // Declarando las variables índice
    int comparar, temp, aux, aux1;

    if(primero < ultimo)
    {
        comparar = primero;
        aux = primero;
        aux1 = ultimo;

        while(aux < aux1)
        {
            while(arrayQuick[aux] <= arrayQuick[comparar] && aux < ultimo)
            {
                aux++;
            }
            while(arrayQuick[aux1]>arrayQuick[comparar])
            {
                aux1--;
            }

            if(aux<aux1)
            {
                temp = arrayQuick[aux];
                arrayQuick[aux] = arrayQuick[aux1];
                arrayQuick[aux1] = temp;
            }
        }

        temp = arrayQuick[comparar];
        arrayQuick[comparar] = arrayQuick[aux1];
        arrayQuick[aux1] = temp;

        // SE LLAMA EL METODO HASTA QUE ESTE ESTE ORDENADO
        ordenamientoQuicksort(arrayQuick, primero, aux1-1);
        ordenamientoQuicksort(arrayQuick, aux1+1, ultimo);
    }
}

int main() {
	
    FILE *ptr_file;
	char buf[1000];
	struct nodoArbolAVL *raiz = NULL;
	char dir[500];
	struct timeb start, end;
	double insertarAVL, InOrden, bubbleSort, quickSort;
	int tiempoArbol, tiempoInOrden, tiempoBurbuja, tiempoQuick;
	LARGE_INTEGER t_ini, t_fin;
	puts("INGRESE LA DIRECCION DEL ARCHIVO QUE DESEEA LEER: ");
	scanf("%s", &dir);
	int n = 0;
	
	ptr_file = fopen(dir, "r");
	if (ptr_file) {
		//ftime(&start);
		QueryPerformanceCounter(&t_ini);
		while (fgets(buf, 1000, ptr_file) != NULL) {
			n = n + 1;
			int w = atoi(buf);
			raiz = insertAVL(raiz, w);
		}

		//ftime(&end);
		//tiempoArbol = (int) (1000.0*(end.time-start.time) + (end.millitm-start.millitm));
	    QueryPerformanceCounter(&t_fin);
		insertarAVL=performancecounter_diff(&t_fin, &t_ini);
		printf("Ingresar Arbol - %f segundos.\n", insertarAVL);
	}

	fclose(ptr_file);

	QueryPerformanceCounter(&t_ini);
	devuelveTiempoInOrden(raiz);
	QueryPerformanceCounter(&t_fin);
	//tiempoInOrden = (int) (1000.0*(end.time - start.time) + (end.millitm-start.millitm));
	InOrden = performancecounter_diff(&t_fin, &t_ini);

	printf("Recorrido Arbol - %f segundos.\n", InOrden);
        

	int arrayBubble[n];
        int count;
        int i;
        int arrayQuick[n];

	ptr_file = fopen(dir, "r");
	if (ptr_file) {
		count = 0;
		while (fgets(buf, 1000, ptr_file) != NULL) {
			int w = atoi(buf);
			arrayBubble[count] = w;
			arrayQuick[count] = w;
			count = count + 1;
		}
	}
	
	fclose(ptr_file);

	//ftime(&start);
	QueryPerformanceCounter(&t_ini);
	ordenamientoBubbleSort(arrayBubble,n);
    //ftime(&end);
    QueryPerformanceCounter(&t_fin);
	//tiempoBurbuja = (int) (1000.0*(end.time - start.time)+(end.millitm-start.millitm));
		     bubbleSort=performancecounter_diff(&t_fin, &t_ini);
	printf("Ordenado Burbuja - %f segundos.\n", bubbleSort);

	QueryPerformanceCounter(&t_ini);
	int aux, temp, j;
    ordenamientoQuicksort(arrayQuick, 0, (n-1));
	QueryPerformanceCounter(&t_fin);
	//tiempoQuick = (int) (1000.0*(end.time - start.time)+(end.millitm-start.millitm));
		     quickSort=performancecounter_diff(&t_fin, &t_ini);
	printf("Ordenado quicksort - %f segundos.\n", quickSort);

        //RESULTADOS
    
	printf("\nSalida Recorrido Arbol - \n", n);
	recorridoInOrden(raiz);
	
	printf("\nSalida Ordenada BUBBLESORT - \n");
		for (i = 0; i < n; i++) {
			printf("%d ", arrayQuick[i]);
	}

	printf("\nSalida Ordenada QUICKSORT - \n");
		for (i = 0; i < n; i++) {
			printf("%d ", arrayBubble[i]);
	}
     
	//CREANDO LOS ARCHIVOS QUE SE ENVIARAN PARA GRAFICAR
	
	FILE *archivoAVL;
	archivoAVL=fopen("archivoAVL.txt","w");
	fprintf(archivoAVL,"0	0.0\n");
	fprintf(archivoAVL,"%d	%f",n,insertarAVL);
	fclose(archivoAVL);
	
	FILE *archivoInOrden;
	archivoInOrden=fopen("archivoInOrden.txt","w");
	fprintf(archivoInOrden,"0	0.0\n");
	fprintf(archivoInOrden,"%d	%f",n,InOrden);
	fclose(archivoInOrden);
	
	FILE *archivoBurbuja;
	archivoBurbuja=fopen("archivoBurbuja.txt","w");
	fprintf(archivoBurbuja,"0	0.0\n");
	fprintf(archivoBurbuja,"%d	%f",n,bubbleSort);
	fclose(archivoBurbuja);
	
	FILE *archivoQuick;
	archivoQuick=fopen("archivoQuick.txt","w");
	fprintf(archivoQuick,"0	0.0\n");
	fprintf(archivoQuick,"%d	%f",n,quickSort);
	fclose(archivoQuick);
	
// PARA REALIZAR LAS GRAFICAS LO QUE NECESITAREMOS SERA:
        
		FILE *gnuplotPipe = popen("gnuplot -persist", "w");
		if (gnuplotPipe) {
			fprintf(gnuplotPipe, "set style data lines\n");
			fprintf(gnuplotPipe, "set title 'Grafica AVL '\n");
			fprintf(gnuplotPipe,
					"plot [:][:0.000004] 'archivoAVL.txt' title 'pendiente AVL'\n");
			fflush(gnuplotPipe);
			fflush(stderr);
			getchar();
			// exit gnuplot
			fprintf(gnuplotPipe, "exit \n");
			pclose(gnuplotPipe);
		}

		FILE *gnuplotPipe2 = popen("gnuplot -persist", "w");
				if (gnuplotPipe2) {
					fprintf(gnuplotPipe2, "set style data lines\n");
					fprintf(gnuplotPipe2, "set title 'Grafica InOrden'\n");
					fprintf(gnuplotPipe2,
							"plot [:][:0.000004] 'archivoInOrden.txt' title 'pendiente  InOrden'\n");
					fflush(gnuplotPipe2);
					fflush(stderr);
					getchar();
					// exit gnuplot
					fprintf(gnuplotPipe2, "exit \n");
					pclose(gnuplotPipe2);
				}
		
		
		FILE *gnuplotPipe3 = popen("gnuplot -persist", "w");
		if (gnuplotPipe3) {
			fprintf(gnuplotPipe3, "set style data lines\n");
			fprintf(gnuplotPipe3, "set title 'Grafica de BubbleSort'\n");
			fprintf(gnuplotPipe3,
					"plot [:][:0.000004] 'archivoBurbuja.txt' title 'pendiente Bubble'\n");
			fflush(gnuplotPipe3);
			fflush(stderr);
			getchar();
			// exit gnuplot
			fprintf(gnuplotPipe3, "exit \n");
			pclose(gnuplotPipe3);
		}

		FILE *gnuplotPipe4 = popen("gnuplot -persist", "w");
				if (gnuplotPipe4) {
					fprintf(gnuplotPipe4, "set style data lines\n");
					fprintf(gnuplotPipe4, "set title 'Grafica de QuickSort'\n");
					fprintf(gnuplotPipe4,
							"plot [:][:0.000004] 'archivoQuick.txt' title 'pendiente Quick'\n");
					fflush(gnuplotPipe4);
					fflush(stderr);
					getchar();
					// exit gnuplot
					fprintf(gnuplotPipe4, "exit \n");
					pclose(gnuplotPipe4);
				}
		
		
		
		
		return 0;

}

