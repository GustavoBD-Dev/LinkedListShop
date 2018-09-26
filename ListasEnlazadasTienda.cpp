#include <iostream>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;
//NODO
struct Music{
    int clave;//tipo de dato
    char nombre [20];//tipo de dato, nombre de cancion
    double precio;
    int productos;
    struct Music *siguiente;//puntero a la siguiente estructura
}*aux1, *aux2;
Music *Lista = NULL; // se crea un puntero y se iguala a NULL
struct MusicBuy{
    int claveBuy;//tipo de dato
    char nombreBuy [20];//tipo de dato, nombre de cancion
    int productosBuy;
    struct MusicBuy *siguienteBuy;//puntero a la siguiente estructura
}*aux1Buy, *aux2Buy;
MusicBuy *ListaBuy = NULL;

//prototipo de funcion
void insertarMusic (int , char [], double, int);
void insertarMusicBuy(int, char [], int);
void deletePlace(int);
void pedirDatos();
void showData();
void menu();
int searchSong(int);
int searchSongBuy(int);
void searchSongPass(int, double*);//paso por referencia del credito
void showDataBuy();
int main(){
    double credit = 100;
    int opcion;
    do{
        menu();
        cin >> opcion;
        switch(opcion){
            case 1:
                system("cls");
                pedirDatos();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                int optionKey, songPlace;
                showData();
                cout << endl;
                cout << "inserte clave de la cancion a comprar: ";
                cin >> optionKey;
                songPlace =searchSong(optionKey);//busca la cancion en la lista
                if(songPlace == -1){//se busca la cancion
                    cout << " No Encontrado " << endl;
                }else{
                    int c=searchSongBuy(optionKey);
                    if (c != -1){//productos en la lista comprada
                        cout << "ya tienes comprada esta cancion" << endl;
                        system("pause");
                    }else{
                        searchSongPass(optionKey, &credit);//pasar los datos
                    }
                }
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                showData();
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                showDataBuy();
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                cout << "CREDITO:  " << credit << endl;
                system("pause");
                system("cls");
                break;
            case 6:

                break;
            default:
                system("cls");
                cout << "opcion invalida..." ;
                system("pause");
                system("cls");
                break;
        }//fin de switch
    }while(opcion != 6);
    delete aux1;
    delete aux2;
	return 0;
}
void menu(){
    cout << "   INICIO " << endl;
	cout << "1.-Agregar canciones" << endl;
	cout << "2.-Comprar canciones" << endl;
	cout << "3.-ver canciones " << endl;
	cout << "4.-ver canciones compradas" << endl;
	cout << "5.-consultar Credito " << endl;
	cout << "6.-salir" << endl;
	cout << "inserta tu opcion: " ;
}
void pedirDatos(){
    int claveN;
    char nombreN[20];
    double precioN;
    int productosN;
    cout << "inserte clave: " ;
    cin >> claveN;
    cin.ignore();
    cout << "inserte nombre: ";
    cin.getline(nombreN,20,'\n');
    cout << "inserte precio: ";
    cin >> precioN;
    cout << "inserte total de productos: ";
    cin >> productosN;

    insertarMusic(claveN, nombreN, precioN, productosN);
}

void insertarMusic (int key, char newName[], double nPrice, int nProductos){
    /*PASO 1: CREAR UN NUEVO NODO*/
    Music *newmusic = new Music ();//se reserva memoria de tipo nodo

    /*PASO 2: ASIGNAR A LAS VARIABLES DEL NODO LOS DATOS NUEVOS*/
    newmusic->clave = key;//se le asigna el elemento que se quiere agregar
    strcpy(newmusic->nombre , newName);
    newmusic->precio = nPrice;
    newmusic->productos = nProductos;

    /*PASO 3: CREAR DOS NODOS AUXILIARES, SE LE ASIGNA LA LISTA AL PRIMERO*/
    //ya se han creado al principio
    //Music *aux1 = Lista;
    //Music *aux2;
    aux1 = Lista;//como lista señala a NULL, aux1 tambien

    /*PASO 4: INSERTAR LOS ELEMENTOS EN LA LISTA*/
    /*TRES CASOS
        1.- cuando la lista este vacia, es decir apunte a NULL,
            es decir es el primer elemnto de la lista
        2.- cuando ya se tenga un nodo, y se puede agregar al inicio o al final
        3.- cuando se tienen dos o mas nodos, se puede agregar al inicio, en medio
            o al final de la lista
    */
    //while para que siempre esten ordenados los elementos de la lista
    while((aux1 != NULL) && (aux1->clave < key)){
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }
    /*
    si el siguiente condicional se cumple, significa que no ha entrado
    a el while, por lo tanto el elemento va al principio
    */
    if(Lista == aux1){
        Lista = newmusic;
    }
    /*
    si entra el else, significa que ha entrado al while
    por lo tanto se ha recorrido una posicion
    */
    else{
        aux2 -> siguiente = newmusic;
    }
    newmusic -> siguiente = aux1;
    cout << "elemento insertado ..." << endl;
}//fin de la funcion insertarLista

void showData(){
  //se crea un nuevo nodo
  Music *actual = new Music ();
  //se le asigna al nodo Lista
  actual = Lista;
  cout << endl;
    cout << setw(6) << "TRACK"
            << setw(20) << "NAME"
            << setw(15) << "PRICE"
            << setw(15) << "PRODUCTS" << endl;
  while (actual != NULL) {
    //imprime el valor del primer nodo
    cout << setw(6)<<actual -> clave
            << setw(20) << actual->nombre
            << setw(15) << actual->precio
            << setw(15) << actual->productos << endl;;
    //avanza hasta que actual sea igual a NULL
    actual = actual -> siguiente;
  }
}

int searchSong(int n){
  Music *actual = new Music ();
  actual = Lista;
  bool band = false;
  while ((actual != NULL) && (actual->clave<= n)) {
    if (actual->clave == n) {
      band = true;
    }
    actual = actual->siguiente;
  }
  if (band == true) {
    return 1;
  }else{
    return -1;
  }
}//fin de buscarLista

void insertarMusicBuy(int cB, char nB []){
    /*PASO 1: CREAR UN NUEVO NODO*/
    MusicBuy *newmusicBuy = new MusicBuy ();//se reserva memoria de tipo nodo

    /*PASO 2: ASIGNAR A LAS VARIABLES DEL NODO LOS DATOS NUEVOS*/
    newmusicBuy->claveBuy = cB;//se le asigna el elemento que se quiere agregar
    strcpy(newmusicBuy->nombreBuy , nB);
    //newmusicBuy->productosBuy = pB;

    /*PASO 3: CREAR DOS NODOS AUXILIARES, SE LE ASIGNA LA LISTA AL PRIMERO*/
    //ya se han creado al principio
    //Music *aux1 = Lista;
    //Music *aux2;
    aux1Buy = ListaBuy;//como lista señala a NULL, aux1 tambien

    /*PASO 4: INSERTAR LOS ELEMENTOS EN LA LISTA*/
    /*TRES CASOS
        1.- cuando la lista este vacia, es decir apunte a NULL,
            es decir es el primer elemnto de la lista
        2.- cuando ya se tenga un nodo, y se puede agregar al inicio o al final
        3.- cuando se tienen dos o mas nodos, se puede agregar al inicio, en medio
            o al final de la lista
    */
    //while para que siempre esten ordenados los elementos de la lista
    while((aux1Buy != NULL) && (aux1Buy->claveBuy < cB)){
        aux2Buy = aux1Buy;
        aux1Buy = aux1Buy->siguienteBuy;
    }
    /*
    si el siguiente condicional se cumple, significa que no ha entrado
    a el while, por lo tanto el elemento va al principio
    */
    if(ListaBuy == aux1Buy){
        ListaBuy = newmusicBuy;
    }
    /*
    si entra el else, significa que ha entrado al while
    por lo tanto se ha recorrido una posicion
    */
    else{
        aux2Buy -> siguienteBuy = newmusicBuy;
    }
    newmusicBuy -> siguienteBuy = aux1Buy;
}

int searchSongBuy(int n){
    MusicBuy *actualBuy = new MusicBuy ();
    actualBuy = ListaBuy;
    bool band = false;
    while ((actualBuy != NULL) && (actualBuy->claveBuy<= n)){
        if (actualBuy->claveBuy == n){
            band = true;
        }
        actualBuy = actualBuy->siguienteBuy;
    }
    if (band == true){
        return 1;//elemento encontrado
    }else{
        return -1;//elemento no encontrado
    }
}

void deletePlace(int n){
    //preguntar si la lista no esta vacia
    if (Lista != NULL){
        Music *aux_borrar;
        Music *anterior = NULL;

        aux_borrar = Lista;

        //recorremos la Lista
        while ((aux_borrar != NULL) && (aux_borrar -> clave != n)){
            anterior = aux_borrar;
            aux_borrar = aux_borrar -> siguiente;
        }
        //el elemento no ha sido encontrado
        if(aux_borrar == NULL){
            cout << "No encontrado " << endl;
        }
        //el primer elemento es que se va a aux_borra
        else if (anterior == NULL){
            Lista = Lista -> siguiente;
            delete aux_borrar;
        }
        //el elemento a borrar no es el primer nodo
        else{
            anterior -> siguiente = aux_borrar -> siguiente;
            delete aux_borrar;
        }
    }
}



void searchSongPass(int n, double *credit){
  Music *actual = new Music ();
  actual = Lista;
  bool band = false;
  while ((actual != NULL) && (actual->clave<= n)) {
    if (actual->clave == n) {
      band = true;
      int cB;
    char nB [20];
    int pB;
    cB = actual->clave;
    strcpy(nB,actual->nombre);
    pB = actual->precio;
    insertarMusicBuy(cB, nB);
    //se resta el saldo
    *credit =(*credit) - (pB);
    //se elimina una unidad de los productos
    actual->productos = (actual->productos) - 1;
    }
    actual = actual->siguiente;
  }
}//fin de buscarLista

void showDataBuy(){
    //se crea un nuevo nodo
  MusicBuy *actualBuy = new MusicBuy ();
  //se le asigna al nodo Lista
  actualBuy = ListaBuy;
  cout << endl;
    cout << setw(6) << "TRACK"
            << setw(20) << "NAME"
            //<< setw(15) << "PRICE"
            //<< setw(15) << "PRODUCTS"
            << endl;
  while (actualBuy != NULL) {
    //imprime el valor del primer nodo
    cout << setw(6)<<actualBuy -> claveBuy
            << setw(20) << actualBuy->nombreBuy
            //<< setw(15) << actualBuy->precioBuy
            //<< setw(15) << actualBuy->productosBuy
            << endl;;
    //avanza hasta que actual sea igual a NULL
    actualBuy = actualBuy -> siguienteBuy;
  }
}



