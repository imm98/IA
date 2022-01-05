#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;

const int PROFUNDIDAD_ALFABETA=8;
// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar









// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}


void heuristicaEnlinea(int jugador, int &ntres, int &ndos, Environment e) {
    
    for (int fila=0; fila < 7 ; fila++){
    	for (int columna=0; columna<7 ; columna++){
    
		    if (columna<5){
		      if ((e.See_Casilla(fila, columna)%3)   == (e.See_Casilla(fila, columna+1)%3) and
		          (e.See_Casilla(fila, columna+1)%3) == (e.See_Casilla(fila, columna+2)%3) and
		          (e.See_Casilla(fila, columna+2)%3) == jugador){
		          
		          ntres++;
		      }
		    }
		    //En la misma columna
		    if (fila<5){
		      if ((e.See_Casilla(fila, columna)%3)   == (e.See_Casilla(fila+1, columna)%3) and
		          (e.See_Casilla(fila+1, columna)%3) == (e.See_Casilla(fila+2, columna)%3) and
		          (e.See_Casilla(fila+2, columna)%3) == jugador){

		          
		          ntres++;
		      }
		    }
		    //En la diagonal hacia arriba
		    if (fila<5 and columna<5){
		      if ((e.See_Casilla(fila, columna)%3)     == (e.See_Casilla(fila+1, columna+1)%3) and
		          (e.See_Casilla(fila+1, columna+1)%3) == (e.See_Casilla(fila+2, columna+2)%3) and
		          (e.See_Casilla(fila+2, columna+2)%3) == jugador){

		          
		          ntres++;
		      }
		    }

		    //En la diagonal hacia abajo
		    if (fila>1 and columna<5){
		      if ((e.See_Casilla(fila, columna)%3)   == (e.See_Casilla(fila-1, columna+1)%3) and
		          (e.See_Casilla(fila-1, columna+1)%3) == (e.See_Casilla(fila-2, columna+2)%3) and
		          (e.See_Casilla(fila-2, columna+2)%3) == jugador){

		          
		          ntres++;
		        }
		    }

		}
	}


	for (int fila=0; fila < 7 ; fila++){
    	for (int columna=0; columna<7 ; columna++){
    
		    if (columna<6){
		      if ((e.See_Casilla(fila, columna)%3)   == (e.See_Casilla(fila, columna+1)%3) and
		          (e.See_Casilla(fila, columna+1)%3) == jugador){
		      		
		          
		          ndos++;
		      }
		    }
		    //En la misma columna
		    if (fila<6){
		      if ((e.See_Casilla(fila, columna)%3)   == (e.See_Casilla(fila+1, columna)%3) and
		          (e.See_Casilla(fila+1, columna)%3) == jugador){
		          

		          
		          ndos++;
		      }
		    }
		    //En la diagonal hacia arriba
		    if (fila<6 and columna<6){
		      if ((e.See_Casilla(fila, columna)%3)     == (e.See_Casilla(fila+1, columna+1)%3) and
		          (e.See_Casilla(fila+1, columna+1)%3) == jugador){
		          

		          
		          ndos++;
		      }
		    }

		    //En la diagonal hacia abajo
		    if (fila>0 and columna<6){
		      if ((e.See_Casilla(fila, columna)%3)   == (e.See_Casilla(fila-1, columna+1)%3) and
		          
		          (e.See_Casilla(fila-1, columna+1)%3) == jugador){
		          

		          
		          ndos++;
		        }
		    }

		}
	}
	ndos-=2*ntres;

}

// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &e, int jugador){
	double val;
	if (e.RevisarTablero()==jugador)
		val=masinf;
	else if(e.RevisarTablero()==((jugador%2)+1))
		val=menosinf;
	else{
		int num_dos_jug=0;
		int num_tres_jug=0;
		heuristicaEnlinea(jugador, num_tres_jug, num_dos_jug, e);
		int num_dos_otro_jug=0;
		int num_tres_otro_jug=0;
		heuristicaEnlinea(((jugador%2)+1), num_tres_otro_jug, num_dos_otro_jug, e);

		val=((num_dos_otro_jug-num_dos_jug)*10+(num_tres_otro_jug-num_tres_jug)*100);
	}
	
	return val;

}


double alphabeta(Environment e, bool maximizador, int jugador_, int depth , const int PROFUNDIDAD_ALFABETA,Environment::ActionType &accion, double alpha, double beta){
	
	if (depth==PROFUNDIDAD_ALFABETA){
		
		return Valoracion(e,jugador_);
	}
	
	if (maximizador){
		double best=menosinf;
		Environment *vect;
		vect=new Environment[8];
		int num=e.GenerateAllMoves(vect);
		
		double *valores;
		valores=new double[8];
		
		for(int i=0; i< num; i++){
			double val;
			
			if (vect[i].RevisarTablero()==0)
				val=alphabeta(vect[i], false,((jugador_%2)+1),depth+1, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
			else if (vect[i].RevisarTablero()==jugador_)
				val=masinf;
			else
				val=menosinf;

			if (depth==0)
				valores[i]=val;
			
            	
            	


			best=max(best, val);
			alpha=max(alpha,best);
			if (beta<=alpha)
				
				break;
			
		}
		if (depth==0){
			
			bool encontrado=false;
			for (int j=0; j< num &&!encontrado; j++){
				if (valores[j]==best){
					
					accion = static_cast< Environment::ActionType > (vect[j].Last_Action(jugador_));
					encontrado=true;
				}

			}

			delete [] valores;
			delete [] vect;
		}
		return best;

	}

	else{
		double best=masinf;
		Environment *vect;
		vect=new Environment[8];
		int num=e.GenerateAllMoves(vect);
		//cout << "pepito"<<endl;
		for(int i=0; i< num; i++){
			double val;
			
			if (vect[i].RevisarTablero()==0)
				val=alphabeta(vect[i], true, ((jugador_%2)+1), depth+1,PROFUNDIDAD_ALFABETA, accion, alpha, beta);
			else if(vect[i].RevisarTablero()==jugador_)
				val=menosinf;
			else val=masinf;

			best=min(best, val);
			beta=min(beta, best);
			if (beta<=alpha)
				break;
		}	

		delete [] vect;
		return best;
	}
}

// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta
    alpha=menosinf;
    beta=masinf;
    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    /*cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
         	
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
            
            int ntres=0; 
            int ndos=0;
         	heuristicaEnlinea(jugador_, ntres,ndos, actual_);
         	cout << endl;
            cout << "ntres"<<ntres<<endl; 
            cout << "ndos"<<ndos<<endl;
         }
	*/

    //--------------------- COMENTAR Hasta aqui
    
    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);
    
    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
    else { 
         	
         	valor=alphabeta(actual_, true, jugador_, 0 , PROFUNDIDAD_ALFABETA,accion,  alpha, beta);
    }
    
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    return accion;
}




