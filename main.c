#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include <ctype.h>
#include<conio.h>
#include <windows.h>
#define R "\x1b[31m"
#define B "\x1b[34m"
#define M "\x1b[35m"
#define RESET "\x1b[0m"
// bajar volumen 
typedef struct{
	char nombre[30];
	int cant;
}item;

typedef struct{
	List *Equipable;
	List *Consumible;
	int cantidad;
}Inventario;
typedef struct{
	char nombre[50];
	Inventario *Inventario;
}pj;
void CrearPersonaje();
pj * Buscar_pj();
void AgregarItemNuevo();
void ExportarItem();
void MostrarEquipables();
void MostrarTodosItems();
void MostrarConsumibles();
void EliminarItemSeleccion();
const char *get_csv_field ();
void AgregarItem();
void MostrarPersonajes();
void EliminarItemTodos();
void EliminarItem();
void ImportarFichero();
void chi(){// funcion para generar la bandera de chile
	printf(B"*********************"B);
	printf(RESET"******************************************"RESET);
	printf(B"\n**********"B);
	printf(RESET"*"RESET);
	printf(B"**********"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"********"B);
	printf(RESET"*****"RESET);
	printf(B"********"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"****"B);
	printf(RESET"*************"RESET);
	printf(B"****"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"******"B);
	printf(RESET"*********"RESET);
	printf(B"******"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"*******"B);
	printf(RESET"*******"RESET);
	printf(B"*******"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"******"B);
	printf(RESET"****"RESET);
	printf(B"*"B);
	printf(RESET"****"RESET);
	printf(B"******"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"*****"B);
	printf(RESET"****"RESET);
	printf(B"***"B);
	printf(RESET"****"RESET);
	printf(B"*****"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"*********************"B);
	printf(RESET"******************************************\n"RESET);
	printf(B"*********************"B);
	printf(RESET"******************************************\n"RESET);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
	printf(R"***************************************************************\n"R);
}
int main(){
	system("COLOR A");
	int p = 0,op = -1;
	FILE * fachero;
	char nombre[100];
	chi();
	PlaySound("consentida8bits.wav",NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
	List *Lista_pj = createList();
	while(op!=0){
		printf("\nSeleccione una opcion\n");
		while(1){
			printf(B"\n1.- Importar items\n"B);
			printf(B"2.- Exportar items\n"B);
			printf(B"3.- Agregar item\n"B);
			printf(R"4.- Mostrar items equipables de un personaje\n"R);
			printf(R"5.- Mostrar items consumibles de un personaje\n"R);
			printf(R"6.- Eliminar item de un personaje\n"R);
			printf(RESET"7.- Eliminar item de todos los personajes\n"RESET);
			printf(RESET"8.- Mostrar nombres de los personajes\n"RESET);
			printf(RESET"9.- Mostrar todos los items\n"RESET);
			printf(M"10.- Ingrese 10 para salir\n"M);
			scanf("%d",&op);
			if(op <= 10 && op >= 1){
				break;
			}
		}
		switch(op){
			case 1: ImportarFichero(fachero,Lista_pj);break;
			case 2: ExportarItem(fachero,Lista_pj);break;
			case 3: AgregarItemNuevo(Lista_pj);break;
			case 4: MostrarEquipables(Lista_pj);break;
			case 5: MostrarConsumibles(Lista_pj);break;
			case 6: EliminarItem(Lista_pj);break;
			case 7: EliminarItemTodos(Lista_pj);break;
			case 8: MostrarPersonajes(Lista_pj);break;
			case 9: MostrarTodosItems(Lista_pj);break;
			case 10:exit(-1);
		}
	}
	return 0;
}
void ImportarFichero(FILE *file, List *Lista_pj){// Importa el fichero senalado por el usuario, comprueba que exista, una vez hecho, mediante el while se crea una lista para llenarla de personajes y al mismo tiempo sublistas para anadir su respectivo inventario.
	char filename[100];
	printf("Ingrese el nombre del fichero (inlcuyendo la extension): \n");
    while(1){
		scanf("%s",filename);   
		if ((file = fopen(filename, "r")) != NULL){
      		printf("El fichero fue importado correctamente\n");
			break;
			}
		printf("Fichero no existente, porfavor reintente : \n");// se asegura que el nombre del fichero se encuentre
    }
    char linea[200];
    int i;
    fgets (linea, 199, file);
    int k=0;
    while (fgets (linea, 199, file) != NULL) { 
    	pj *Personaje = (pj*)malloc(sizeof(pj));
    	Personaje->Inventario = (Inventario*)malloc(sizeof(Inventario));
    	
    	strcpy(Personaje->nombre,get_csv_field(linea,3));
    	if(firstList(Lista_pj) == NULL){
    		CrearPersonaje(Lista_pj,Personaje,get_csv_field(linea,0),get_csv_field(linea,1),atoi(get_csv_field(linea,2)));
		}else{
			VerificarExistente(Lista_pj,Personaje,get_csv_field(linea,0),get_csv_field(linea,1),atoi(get_csv_field(linea,2)));
		}
        
        k++;
    }
    fclose(file);
	
}
const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}
void CrearPersonaje(List* Lista_pj,pj *Personaje,char *tipo,char *nombre,int *cant){// crea un personaje con su lista de consumibles y su lista de equipables, ademas agrega sus items correspondientes.
	Personaje->Inventario->Consumible = createList();
	Personaje->Inventario->Equipable = createList();
	Personaje->Inventario->cantidad = 0;
	AgregarItem(Lista_pj,Personaje,tipo,nombre,cant);
	pushFront(Lista_pj,Personaje);
} 
void AgregarItem(List* Lista_pj,pj *Personaje,char *tipo,char *nombre,int *cant){// agrega un item a una lista segun su tipo
	item *Newitem = (item*)malloc(sizeof(item));
	strcpy(Newitem->nombre,nombre);
	Newitem->cant = cant;
	if(strcmp(tipo,"Equipable") == 0){
		pushFront(Personaje->Inventario->Equipable,Newitem);
		Personaje->Inventario->cantidad = Personaje->Inventario->cantidad + 1;
	}
	if(strcmp(tipo,"Consumible") == 0){
		pushFront(Personaje->Inventario->Consumible,Newitem);
		Personaje->Inventario->cantidad = Personaje->Inventario->cantidad + 1;	
	}
	
}
void VerificarExistente(List* Lista_pj,pj *Personaje,char *tipo,char *nombre,int *cant){ // funcion que verifica si existe el personaje, si no existe con su primer if llama a una funcion para crearlo, si existe, agrega los items al personaje.
	pj * Personaje_Existente = (pj*)malloc(sizeof(pj));
	Personaje_Existente->Inventario = (Inventario*)malloc(sizeof(Inventario));
	Personaje_Existente = firstList(Lista_pj);
	while(1){
		if(Personaje_Existente->nombre == NULL){
			CrearPersonaje(Lista_pj,Personaje,tipo,nombre,cant);
			break;
			
		}
		else if(strcmp(Personaje->nombre,Personaje_Existente->nombre) == 0 ){
			AgregarItem(Lista_pj,Personaje_Existente,tipo,nombre,cant); 
			break;
			
		}
		Personaje_Existente = nextList(Lista_pj);
	}
	
	
}
void MostrarPersonajes(List* Lista_pj){
  pj * mostrar = (pj*)malloc(sizeof(pj));
  mostrar = firstList(Lista_pj);

  printf("Lista a imprimir es de:\n");
  while(mostrar != NULL){
    printf("%s\n",mostrar->nombre);
    printf("%d Items\n",mostrar->Inventario->cantidad);
    mostrar = nextList(Lista_pj);
  }
  printf("Final de lista de personajes.\n");
}
void MostrarEquipables(List* Lista_pj){
	char nombre_Personaje[30];
	printf("Ingrese nombre Personaje\n");
    fflush(stdin);
     scanf("%30[^\n]", nombre_Personaje);
    pj * mostrar = Buscar_pj(Lista_pj,nombre_Personaje);
    if (mostrar==NULL){
        printf("Personaje No Encontrado");
        return 0;
    }
    printf("Personaje Encontrado\n");
    item * itemEquipable = firstList(mostrar->Inventario->Equipable);
    printf("%s",itemEquipable->nombre);
   	while(1){
        itemEquipable=nextList(mostrar->Inventario->Equipable);
        if(itemEquipable==NULL){
            break;
        }
        printf("%s ",itemEquipable->nombre);
        printf("%d\n",itemEquipable->cant);

   	}

}
void MostrarConsumibles(List* Lista_pj){
	char nombre_Personaje[30];
	printf("Ingrese nombre Personaje\n");
    fflush(stdin);
    scanf("%30[^\n]", nombre_Personaje);
	pj * mostrar = Buscar_pj(Lista_pj,nombre_Personaje);
    if (mostrar==NULL){
        printf("Personaje No Encontrado");
        return 0;
    }
    printf("Personaje Encontrado\n");
    item * itemConsumible = firstList(mostrar->Inventario->Consumible);
    printf("%s",itemConsumible->nombre);
    while(1){
        itemConsumible=nextList(mostrar->Inventario->Consumible);
        if(itemConsumible==NULL){
            break;
        }
        printf("%s ",itemConsumible->nombre);
        printf("%d\n",itemConsumible->cant);

   	}

	
}
pj * Buscar_pj(List *Lista_pj, char *nombre_Personaje){ //Funcion que busca el personaje dentro dse su lista.
	 pj * mostrar = (pj*)malloc(sizeof(pj));
	 mostrar = firstList(Lista_pj);
	 while(1){
	 	if(mostrar == NULL){
	 		return NULL;
		 }else if(strcmp(mostrar->nombre, nombre_Personaje) == 0){
		 	return mostrar;	
		 }
		 mostrar = nextList(Lista_pj);
	 }
	 
}
void AgregarItemNuevo(List* Lista_pj){
	char nombre_Personaje[30];
	char nombre_item[30];
	char tipo_item[30];
	int cant;
	printf("Ingrese nombre Personaje\n");
    fflush(stdin);
    scanf("%30[^\n]", nombre_Personaje);
	pj * mostrar = Buscar_pj(Lista_pj,nombre_Personaje);
	pj * Personaje = (pj*)malloc(sizeof(pj));
	Personaje->Inventario = (Inventario*)malloc(sizeof(Inventario));
    if (mostrar==NULL){
    	strcpy(Personaje->nombre,nombre_Personaje);
    	printf("Ingrese tipo de Item (Equipable/Consumible)\n");
    	fflush(stdin);
    	scanf("%30[^\n]", tipo_item);
    	printf("Ingrese nombre item\n");
    	fflush(stdin);
    	scanf("%30[^\n]", nombre_item);
    	printf("Ingrese cantidad/nivel del item\n");
    	fflush(stdin);
    	scanf("%d", &cant);
    	CrearPersonaje(Lista_pj,Personaje,tipo_item,nombre_item,cant);
    	printf("Su Personaje fue creado, y su item añadido\n");
    }else{
    	printf("Ingrese tipo de Item (Equipable/Consumible)\n");
    	fflush(stdin);
    	scanf("%30[^\n]", tipo_item);
    	printf("Ingrese nombre item\n");
    	fflush(stdin);
    	scanf("%30[^\n]", nombre_item);
    	printf("Ingrese cantidad/nivel del item\n");
    	fflush(stdin);
    	scanf("%d", &cant);
    	AgregarItem(Lista_pj,mostrar,tipo_item,nombre_item,cant);
    	printf("su item fue añadidos\n");
	}
    

	
}
void ExportarItem(FILE * file, List *Lista_pj){
	char filename[100];
	printf("Ingrese el nombre del fichero (inlcuyendo la extension): \n");
	scanf("%s",filename);
	FILE  *archivoPJ = fopen(filename,"w");  
	if (filename== NULL){
		return;
	}
	pj *pjafile = firstList(Lista_pj);
	while (pjafile != NULL){
		item *itemsexp = firstList(pjafile->Inventario->Consumible);
		
		while(pjafile->Inventario->Consumible !=NULL){
			if (pjafile->Inventario->Consumible !=NULL){
			
				fputs("Consumible",archivoPJ);
				fputc(',',archivoPJ);
				fputs(itemsexp->nombre,archivoPJ);
				fputc(',',archivoPJ);
				fputs(itemsexp->cant,archivoPJ);
				fputc(',',archivoPJ);
				fputs(pjafile->nombre,archivoPJ);
				fputc('\n',archivoPJ);
			}
			itemsexp = nextList(pjafile->Inventario->Consumible);
		}
		
		item *itemsexp2 = firstList(pjafile->Inventario->Equipable);
		while(pjafile->Inventario->Equipable !=NULL){
			if (pjafile->Inventario->Equipable !=NULL){
		
			fputs("Equipable",archivoPJ);
			fputc(',',archivoPJ);
			fputs(itemsexp2->nombre,archivoPJ);
			fputc(',',archivoPJ);
			fputs(itemsexp2->cant,archivoPJ);
			fputc(',',archivoPJ);
			fputs(pjafile->nombre,archivoPJ);
			fputc('\n',archivoPJ);
			}
		
		}
		
	}
	fclose(archivoPJ);
	
	
	
}
void EliminarItem(List *Lista_pj){
	char nombre_Personaje[30];
	char nombre_item[30];
	char tipo_item[30];
	int cant;
	printf("Ingrese nombre Personaje\n");
    fflush(stdin);
     scanf("%30[^\n]", nombre_Personaje);
    pj * mostrar = Buscar_pj(Lista_pj,nombre_Personaje);
    if (mostrar==NULL){
        printf("Personaje No Encontrado");
        return 0;
    }else{
    	printf("Ingrese tipo de Item (Equipable/Consumible)\n");
    	fflush(stdin);
    	scanf("%30[^\n]", tipo_item);
    	printf("Ingrese nombre item\n");
    	fflush(stdin);
    	scanf("%30[^\n]", nombre_item);
    	printf("Ingrese cantidad/nivel del item\n");
    	fflush(stdin);
    	scanf("%d", &cant);
    	EliminarItemSeleccion(Lista_pj,mostrar,tipo_item,nombre_item,cant);
    	

	}
	
}	
void EliminarItemTodos(List *Lista_pj){
	
}
void MostrarTodosItems(List *Lista_pj){
	pj * p_m = firstList(Lista_pj);
    while (1){
        printf("%s:\n",p_m->nombre);
        if(p_m == NULL){
            break;
        }
        item * iMostrarC = firstList(p_m->Inventario->Consumible);
        while(1){
            if(iMostrarC == NULL){
                break;
            }
            printf("%s, ",iMostrarC->nombre);
            printf("%d\n",iMostrarC->cant);
            iMostrarC=nextList(p_m->Inventario->Consumible);
        }
        item * iMostrarE = firstList(p_m->Inventario->Equipable);
        while(1){
            if(iMostrarE == NULL){
                break;
            }
            printf("%s, ",iMostrarE->nombre);
            printf("%d\n",iMostrarE->cant);
            iMostrarE = nextList(p_m->Inventario->Equipable);
        }
        p_m = nextList(Lista_pj);
    }
	
}
void EliminarItemSeleccion(List* Lista_pj,pj *Personaje,char *tipo,char *nombre,int *cant){
	
}
