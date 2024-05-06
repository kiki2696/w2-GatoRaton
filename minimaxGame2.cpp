#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
using namespace std;

// variables
const string raton = "\033[1;31mR\033[0m"; // R en rojo para representar al raton
const string gato = "\033[1;34mG\033[0m"; // G en azul para representar al gato

// tablero donde inicialmente estan todos vacios
map<int, string> tablero = {
    {1, " "}, {2, " "}, {3, " "}, {4, " "}, {5, " "},
    {6, " "}, {7, " "}, {8, " "}, {9, " "}, {10, " "},
    {11, " "}, {12, " "}, {13, " "}, {14, " "}, {15, " "},
    {16, " "}, {17, " "}, {18, " "}, {19, " "}, {20, " "},
    {21, " "}, {22, " "}, {23, " "}, {24, " "}, {25, " "}
};

// funcion que imprime el tablero dandole un formato mas amigable
void imprimir_tablero(map<int, string> tablero){
    cout << "\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[1] << "  #  " << tablero[2] << "  #  " << tablero[3] << "  #  " << tablero[4] << "  #  " << tablero[5] << "  # \033[1;35mS\033[0m\n";  // S en lila (salida)
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[6] << "  #  " << tablero[7] << "  #  " << tablero[8] << "  #  " << tablero[9] << "  #  " << tablero[10] << "  #\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[11] << "  #  " << tablero[12] << "  #  " << tablero[13] << "  #  " << tablero[14] << "  #  " << tablero[15] << "  #\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[16] << "  #  " << tablero[17] << "  #  " << tablero[18] << "  #  " << tablero[19] << "  #  " << tablero[20] << "  #\n";
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "#  " << tablero[21] << "  #  " << tablero[22] << "  #  " << tablero[23] << "  #  " << tablero[24] << "  #  " << tablero[25] << "  # \033[1;35mE\033[0m\n";  // E en lila (entrada)
    cout << "# # # # # # # # # # # # # # # #\n";
    cout << "\n";
}

// funcion que verifica si una casilla esta libre
bool espacio_libre(int posicion){
    return tablero[posicion] == " ";
}

// funcion para colocar al gato o al raton en la casilla
void colocar_gato_raton(int posicion, string jugador){
    if(espacio_libre(posicion)){
        tablero[posicion] = jugador;
    }
}

// funcion para la primera posicion del jugador (raton)
int movimiento_inicial_jugador(){
    int posicion;
    cout << "Digitar una casilla entre el 21 al 25\nRespuesta: ";
    cin >> posicion;

    while (!(posicion >= 21 && posicion <= 25)){
        cout << "Opcion rechazada, elija una casilla entre el 21 al 25\nRespuesta: ";
        cin >> posicion;
    }

    colocar_gato_raton(posicion, raton);
    return posicion;
}

// funcion que calcula segun tu posicion previa (raton) tu nueva ubicacion y que no te saltes columnas
int obtener_nueva_posicion(int posicion, int direccion){  //posicion: actual - direccion: futuro
    if(direccion == 1){ // subir
        return posicion - 5;  
    } else if(direccion == 2){  // bajar
        return posicion + 5;  
    } else if(direccion == 3){  // izquierda
        if(posicion % 5 == 1){  //residuo 1 (1,6,11,16,21)
            return posicion; 
        }
        return posicion - 1;
    } else if(direccion == 4){  // derecha
        if(posicion % 5 == 0){  //residuo 0 (5,10,15,20,25)
            return posicion; 
        }
        return posicion + 1;
    } else{
        cout << "Opcion no valida";
        return posicion; 
    }
}

// funcion para calcular las distancias de los jugadores - Algoritmo de Manhattan
int calcular_distancia(int posicion_gato, int posicion_raton){
    int fila_gato = (posicion_gato - 1) / 5;  //índice de 0 a 24 (en lugar de 1 a 25) - fila de 0 a 4
    int columna_gato = (posicion_gato - 1) % 5;

    int fila_raton = (posicion_raton - 1) / 5;
    int columna_raton = (posicion_raton - 1) % 5;

    int diferencia_filas = abs(fila_gato - fila_raton);
    int diferencia_columnas = abs(columna_gato - columna_raton);
    //suma  diferencia para obtener la distancia total entre el gato y el ratón.
    return diferencia_filas + diferencia_columnas;
}

// funcion que verifica si el movimiento se puede realizar.
bool es_movimiento_valido(int posicion){
    return posicion >= 1 && posicion <= 25 && (espacio_libre(posicion) || tablero[posicion] == raton);
}

// función que verifica si el ratón ha ganado (llegado a la meta)
bool gano_raton(int posicion_raton){
    return posicion_raton == 5;
}

// funcion que determina la posicion del jugador cada vez que realiza un movimiento.
void determinar_posicion(int &posicion_raton){
    cout << "Estas en la posicion " << posicion_raton << ". En que direccion quieres ir?\n";
    cout << "Seleccione una de las siguientes opciones:\n";
    cout << " - w si desea ir arriba\n";
    cout << " - s si desea ir abajo\n";
    cout << " - a si desea ir izquierda\n";
    cout << " - d si desea ir derecha\n";
    cout << "Respuesta: ";

    char mover;
    cin >> mover;

    int nueva_posicion;
    switch(mover) {
        case 'w':
            nueva_posicion = obtener_nueva_posicion(posicion_raton, 1);
            break;
        case 's':
            nueva_posicion = obtener_nueva_posicion(posicion_raton, 2);
            break;
        case 'a':
            nueva_posicion = obtener_nueva_posicion(posicion_raton, 3);
            break;
        case 'd':
            nueva_posicion = obtener_nueva_posicion(posicion_raton, 4);
            break;
        default:
            cout << "Movimiento no valido. Intenta de nuevo.\n";
            determinar_posicion(posicion_raton);
            return;
    }

    if(es_movimiento_valido(nueva_posicion)){
        tablero[posicion_raton] = ' ';  //borra posicion anterior
        tablero[nueva_posicion] = raton;
        posicion_raton = nueva_posicion; // Actualiza la posición del ratón

        if(gano_raton(nueva_posicion)){
            imprimir_tablero(tablero);
            cout << "Que grandee!! Ganaste!!!!";
            exit(0);  // Terminar el juego
        }
    } else{
        cout << "Movimiento no valido. Intenta de nuevo.\n";
        determinar_posicion(posicion_raton);
        return;
    }
}

// funcion minimax que minimiza la pérdida máxima posible (gato)
float minimax(int posicion_gato, int posicion_raton, int profundidad, float alfa, float beta, bool es_maximizador){
    
    // verifica si se alcanzo profundidad max en el arbol o si raton llego a meta
    if(profundidad == 0 || gano_raton(posicion_raton)){
        //devolver valor de distancia entre ellos como puntaje de evaluacion (manhattan)
        return calcular_distancia(posicion_gato, posicion_raton);
    }

    // cuando sea el turno del jugador maximizador (gato) - movimientos del gato
    if(es_maximizador){
        // se asegura que todo valor encontrado sea mayor
        float maximizar = -INFINITY;
        // recorre el tablero para identificar los movimientos que puede hacer el ratón (las 4 direcciones: arriba,etc)
        for(int direccion = 1; direccion <= 4; direccion++){
            // calcula la nueva posición del ratón (las 4 por iteracion)
            int nueva_posicion = obtener_nueva_posicion(posicion_raton, direccion);
            // verifica el movimiento
            if(es_movimiento_valido(nueva_posicion)){
                // hace la evaluación del movimiento con minimax(), llamamos recursivamente a minimax
                // reduce la profundidad de busqueda a 1 y false porque es turno del raton
                float evaluacion = minimax(posicion_gato, nueva_posicion, profundidad - 1, alfa, beta, false);
                // se actualiza el valor de maximizar siempre y cuando el resultado de la evaluación sea MAYOR, para eso se usa la función max(), devuelve el valor máximo de dos valores dados
                maximizar = max(maximizar, evaluacion);
                // se actualiza alfa, que es el mejor valor que el maximizador encontró hasta ahora.
                alfa = max(alfa, evaluacion);
                // si beta es menor a alfa, paramos e ignoramos todas las ramas innecesarias!.
                if(beta <= alfa){
                    break;
                }
            }
        }
        // se devuelve el valor máximo encontrado. Es decir, mejor jugada del gato
        return maximizar;

        // turno de raton (jugador humano). El gato simula comportamiento del raton 
    } else{
        // inicializa el valor mínimo a infinito
        float minimizar = INFINITY;
        // recorre el tablero probando posiciones
        for(int direccion = 1; direccion <= 4; direccion++){
            int nueva_posicion = obtener_nueva_posicion(posicion_gato, direccion);
            // si el movimiento es válido realiza la evaluación
            if(es_movimiento_valido(nueva_posicion)){
                float evaluacion = minimax(nueva_posicion, posicion_raton, profundidad - 1, alfa, beta, true);
                // actualiza el valor minimizar siempre y cuando el resultado de la evaluación sea mejor
                minimizar = min(minimizar, evaluacion);
                // se actualiza beta, que es el mejor valor que el minimizador encontró.
                beta = min(beta, evaluacion);
                if(beta <= alfa){
                    break;
                }
            }
        }
        return minimizar;
    }
}

// función que determina la mejor opción de movimiento que puede realizar la computadora llamando a minimax
int movimiento_gato(int posicion_gato, int posicion_raton){
    float mejor_evaluacion = INFINITY; 
    int mejor_movimiento = -1;

    // Utilizamos el algoritmo minimax para determinar el mejor movimiento del gato en las 4 direcciones
    for(int direccion = 1; direccion <= 4; direccion++){
        int nueva_posicion = obtener_nueva_posicion(posicion_gato, direccion);
        if(es_movimiento_valido(nueva_posicion)){
            float evaluacion = minimax(nueva_posicion, posicion_raton, 5, -INFINITY, INFINITY, true);
            if(evaluacion < mejor_evaluacion){
                mejor_evaluacion = evaluacion;
                mejor_movimiento = direccion;
            }
        }
    }
    // evaluacion minima que el gato espera obtener, asumiendo el raton tomara la mejor decision para el
    return mejor_movimiento;
}

// función para que la PC pueda jugar, también analiza si se le atrapó al jugador.
int turno_gato(int posicion_gato, int &posicion_raton){
    int direccion = movimiento_gato(posicion_gato, posicion_raton); //vemos la mejor opcion
    int nueva_posicion = obtener_nueva_posicion(posicion_gato, direccion); // movemos al gato
    
    if(es_movimiento_valido(nueva_posicion)){
        if(nueva_posicion == posicion_raton){  // verifica si gana el raton
            cout << "Perdiste!!\nFuiste muy lento!! xD";
            exit(0);
        } else{
            tablero[posicion_gato] = ' ';  //actualiza posicion
            tablero[nueva_posicion] = gato;
            return nueva_posicion;
        }
    } else{
        cout << "Movimiento no valido. El gato se queda en su posicion."; // Se agrega un mensaje de advertencia
        return posicion_gato;
    }    
}

int main(){
    int posicion_gato = 1;
    colocar_gato_raton(posicion_gato, gato);
    imprimir_tablero(tablero);
    int posicion_raton = movimiento_inicial_jugador(); // solocitar al usuario escoger posicion
    imprimir_tablero(tablero);

    // El juego
    while (true){
        //turno gato
        posicion_gato = turno_gato(posicion_gato, posicion_raton);
        imprimir_tablero(tablero);

        // turno raton
        determinar_posicion(posicion_raton);
        imprimir_tablero(tablero);

        if(gano_raton(posicion_raton)){
            imprimir_tablero(tablero);
            cout << "Que grande!!! Ganaste!!! ";
            break;
        }
    }
    return 0;
}