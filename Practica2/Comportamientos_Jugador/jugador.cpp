#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <chrono>
#include <thread>

// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;
	// Estoy en el nivel 1

	if (sensores.nivel != 4){
		if (sensores.mensajeF != -1){
			fil = sensores.mensajeF;
			col = sensores.mensajeC;
			

			actual.fila = fil;
			actual.columna = col;
			actual.orientacion = brujula;

			destino.fila = sensores.destinoF;
			destino.columna = sensores.destinoC;

		}

		bool hay_plan = pathFinding (sensores.nivel, actual, destino, plan);
		if (contador_plan!=plan.size()){
			contador_aux=0;
			contador_plan=plan.size();
				
		}
		if (hay_plan  && contador_aux<plan.size()){
			list<Action> plan_aux=plan;
			for (int i=0; i < contador_aux; i++){
				plan_aux.pop_front();
			}

			
			accion=plan_aux.front();
			switch(accion){
				case actTURN_R:brujula=(brujula+1)%4;
				break;
				case actTURN_L:brujula=(brujula+3)%4;
				break;
			}
			contador_aux++;
			cout << "Contador: "<<contador_aux<<endl;
			cout <<"Longitud del plann: "<<plan.size()<<endl<<endl;
			
		}
	}
	else {
		// Estoy en el nivel 2
		//Action  sigAccion;

		if (sensores.terreno[0]=='K' and amarillo==false){
			accion=actIDLE;
			cout << "Hola1"<<endl;
			fil=sensores.mensajeF;
			col=sensores.mensajeC;

			actual.fila = fil;
			actual.columna = col;
			actual.orientacion = brujula;

			destino.fila = sensores.destinoF;
			destino.columna = sensores.destinoC;
			cout << "Hola2 "<<fil<< " "<<col<< endl;
			switch (brujula){

				case 0:

		          mapaResultado[fil][col] = sensores.terreno[0];
		          mapaResultado[fil-1][col-1] = sensores.terreno[1];
		          mapaResultado[fil-1][col] =sensores.terreno[2];
		          mapaResultado[fil-1][col+1] = sensores.terreno[3];
		          mapaResultado[fil-2][col-2] = sensores.terreno[4];
		          mapaResultado[fil-2][col-1] = sensores.terreno[5];
		          mapaResultado[fil-2][col] = sensores.terreno[6];
		          mapaResultado[fil-2][col+1] = sensores.terreno[7];
		          mapaResultado[fil-2][col+2] = sensores.terreno[8];
		          mapaResultado[fil-3][col-3] = sensores.terreno[9];
		          mapaResultado[fil-3][col-2] = sensores.terreno[10];
		          mapaResultado[fil-3][col-1] = sensores.terreno[11];
		          mapaResultado[fil-3][col] = sensores.terreno[12];
		          mapaResultado[fil-3][col+1] = sensores.terreno[13];
		          mapaResultado[fil-3][col+2] = sensores.terreno[14];
		          mapaResultado[fil-3][col+3] = sensores.terreno[15];
		          break;

		        case 1:
		        	mapaResultado[fil][col] =sensores.terreno[0];
			          mapaResultado[fil-1][col+1] = sensores.terreno[1];
			          mapaResultado[fil][col+1] = sensores.terreno[2];
			          mapaResultado[fil+1][col+1] = sensores.terreno[3];
			          mapaResultado[fil-2][col+2] = sensores.terreno[4];
			          mapaResultado[fil-1][col+2] = sensores.terreno[5];
			          mapaResultado[fil][col+2] = sensores.terreno[6];
			          mapaResultado[fil+1][col+2] = sensores.terreno[7];
			          mapaResultado[fil+2][col+2] = sensores.terreno[8];
			          mapaResultado[fil-3][col+3] = sensores.terreno[9];
			          mapaResultado[fil-2][col+3] = sensores.terreno[10];
			          mapaResultado[fil-1][col+3] = sensores.terreno[11];
			          mapaResultado[fil][col+3] = sensores.terreno[12];
			          mapaResultado[fil+1][col+3] = sensores.terreno[13];
			          mapaResultado[fil+2][col+3] = sensores.terreno[14];
			          mapaResultado[fil+3][col+3] = sensores.terreno[15];
			     break;

			     case 2:
			     	mapaResultado[fil][col] = sensores.terreno[0];
		              mapaResultado[fil+1][col+1] = sensores.terreno[1];
		              mapaResultado[fil+1][col] = sensores.terreno[2];
		              mapaResultado[fil+1][col-1] = sensores.terreno[3];
		              mapaResultado[fil+2][col+2] = sensores.terreno[4];
		              mapaResultado[fil+2][col+1] = sensores.terreno[5];
		              mapaResultado[fil+2][col] = sensores.terreno[6];
		              mapaResultado[fil+2][col-1] = sensores.terreno[7];
		              mapaResultado[fil+2][col-2] = sensores.terreno[8];
		              mapaResultado[fil+3][col+3] = sensores.terreno[9];
		              mapaResultado[fil+3][col+2] = sensores.terreno[10];
		              mapaResultado[fil+3][col+1] = sensores.terreno[11];
		              mapaResultado[fil+3][col] = sensores.terreno[12];
		              mapaResultado[fil+3][col-1] = sensores.terreno[13];
		              mapaResultado[fil+3][col-2] = sensores.terreno[14];
		              mapaResultado[fil+3][col-3] = sensores.terreno[15];
		          break;

		          case 3:
			        mapaResultado[fil][col] = sensores.terreno[0];
	                mapaResultado[fil+1][col-1] = sensores.terreno[1];
	                mapaResultado[fil][col-1] = sensores.terreno[2];
	                mapaResultado[fil-1][col-1] = sensores.terreno[3];
	                mapaResultado[fil+2][col-2] = sensores.terreno[4];
	                mapaResultado[fil+1][col-2] = sensores.terreno[5];
	                mapaResultado[fil][col-2] = sensores.terreno[6];
	                mapaResultado[fil-1][col-2] = sensores.terreno[7];
	                mapaResultado[fil-2][col-2] = sensores.terreno[8];
	                mapaResultado[fil+3][col-3] = sensores.terreno[9];
	                mapaResultado[fil+2][col-3] = sensores.terreno[10];
	                mapaResultado[fil+1][col-3] = sensores.terreno[11];
	                mapaResultado[fil][col-3] = sensores.terreno[12];
	                mapaResultado[fil-1][col-3] = sensores.terreno[13];
	                mapaResultado[fil-2][col-3] = sensores.terreno[14];
	                mapaResultado[fil-3][col-3] = sensores.terreno[15];
	              break;
					}
				amarillo=true;
			
			}
		else if ((sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or sensores.terreno[2]=='D' or sensores.superficie[2]=='a')and amarillo==false){
			accion=actTURN_R;
			brujula=(brujula+1)%4;
		}
		else if (sensores.terreno[0]!='K' and amarillo==false){
			accion=actFORWARD;
		}
		
		else {

				/*fil=sensores.mensajeF;
			col=sensores.mensajeC;

			actual.fila = fil;
			actual.columna = col;
			actual.orientacion = brujula;

			destino.fila = sensores.destinoF;
			destino.columna = sensores.destinoC;*/


				switch (brujula){

				case 0:

		          mapaResultado[fil][col] = sensores.terreno[0];
		          mapaResultado[fil-1][col-1] = sensores.terreno[1];
		          mapaResultado[fil-1][col] =sensores.terreno[2];
		          mapaResultado[fil-1][col+1] = sensores.terreno[3];
		          mapaResultado[fil-2][col-2] = sensores.terreno[4];
		          mapaResultado[fil-2][col-1] = sensores.terreno[5];
		          mapaResultado[fil-2][col] = sensores.terreno[6];
		          mapaResultado[fil-2][col+1] = sensores.terreno[7];
		          mapaResultado[fil-2][col+2] = sensores.terreno[8];
		          mapaResultado[fil-3][col-3] = sensores.terreno[9];
		          mapaResultado[fil-3][col-2] = sensores.terreno[10];
		          mapaResultado[fil-3][col-1] = sensores.terreno[11];
		          mapaResultado[fil-3][col] = sensores.terreno[12];
		          mapaResultado[fil-3][col+1] = sensores.terreno[13];
		          mapaResultado[fil-3][col+2] = sensores.terreno[14];
		          mapaResultado[fil-3][col+3] = sensores.terreno[15];
		          break;

		        case 1:
		        	mapaResultado[fil][col] =sensores.terreno[0];
			          mapaResultado[fil-1][col+1] = sensores.terreno[1];
			          mapaResultado[fil][col+1] = sensores.terreno[2];
			          mapaResultado[fil+1][col+1] = sensores.terreno[3];
			          mapaResultado[fil-2][col+2] = sensores.terreno[4];
			          mapaResultado[fil-1][col+2] = sensores.terreno[5];
			          mapaResultado[fil][col+2] = sensores.terreno[6];
			          mapaResultado[fil+1][col+2] = sensores.terreno[7];
			          mapaResultado[fil+2][col+2] = sensores.terreno[8];
			          mapaResultado[fil-3][col+3] = sensores.terreno[9];
			          mapaResultado[fil-2][col+3] = sensores.terreno[10];
			          mapaResultado[fil-1][col+3] = sensores.terreno[11];
			          mapaResultado[fil][col+3] = sensores.terreno[12];
			          mapaResultado[fil+1][col+3] = sensores.terreno[13];
			          mapaResultado[fil+2][col+3] = sensores.terreno[14];
			          mapaResultado[fil+3][col+3] = sensores.terreno[15];
			     break;

			     case 2:
			     	mapaResultado[fil][col] = sensores.terreno[0];
		              mapaResultado[fil+1][col+1] = sensores.terreno[1];
		              mapaResultado[fil+1][col] = sensores.terreno[2];
		              mapaResultado[fil+1][col-1] = sensores.terreno[3];
		              mapaResultado[fil+2][col+2] = sensores.terreno[4];
		              mapaResultado[fil+2][col+1] = sensores.terreno[5];
		              mapaResultado[fil+2][col] = sensores.terreno[6];
		              mapaResultado[fil+2][col-1] = sensores.terreno[7];
		              mapaResultado[fil+2][col-2] = sensores.terreno[8];
		              mapaResultado[fil+3][col+3] = sensores.terreno[9];
		              mapaResultado[fil+3][col+2] = sensores.terreno[10];
		              mapaResultado[fil+3][col+1] = sensores.terreno[11];
		              mapaResultado[fil+3][col] = sensores.terreno[12];
		              mapaResultado[fil+3][col-1] = sensores.terreno[13];
		              mapaResultado[fil+3][col-2] = sensores.terreno[14];
		              mapaResultado[fil+3][col-3] = sensores.terreno[15];
		          break;

		          case 3:
			        mapaResultado[fil][col] = sensores.terreno[0];
	                mapaResultado[fil+1][col-1] = sensores.terreno[1];
	                mapaResultado[fil][col-1] = sensores.terreno[2];
	                mapaResultado[fil-1][col-1] = sensores.terreno[3];
	                mapaResultado[fil+2][col-2] = sensores.terreno[4];
	                mapaResultado[fil+1][col-2] = sensores.terreno[5];
	                mapaResultado[fil][col-2] = sensores.terreno[6];
	                mapaResultado[fil-1][col-2] = sensores.terreno[7];
	                mapaResultado[fil-2][col-2] = sensores.terreno[8];
	                mapaResultado[fil+3][col-3] = sensores.terreno[9];
	                mapaResultado[fil+2][col-3] = sensores.terreno[10];
	                mapaResultado[fil+1][col-3] = sensores.terreno[11];
	                mapaResultado[fil][col-3] = sensores.terreno[12];
	                mapaResultado[fil-1][col-3] = sensores.terreno[13];
	                mapaResultado[fil-2][col-3] = sensores.terreno[14];
	                mapaResultado[fil-3][col-3] = sensores.terreno[15];
	              break;
					}

				if (actual.fila==destino.fila and actual.columna==destino.columna){
						destino.fila=sensores.destinoF;
						destino.columna=sensores.destinoC;
					}

				bool hay_plan=pathFinding(3, actual, destino, plan);
				cout << "LLega"<<endl;
				if (contador_plan!=plan.size()){
					contador_aux=0;
					contador_plan=plan.size();
				}
				if (hay_plan  && contador_aux<plan.size()){
					list<Action> plan_aux=plan;
					for (int i=0; i < contador_aux; i++){
						plan_aux.pop_front();
					}

					
					accion=plan_aux.front();
					switch(accion){
						
						case actTURN_R:brujula=(brujula+1)%4;
						break;
						case actTURN_L:brujula=(brujula+3)%4;
						break;
						case actFORWARD: 
						if (sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or 
							sensores.terreno[2]=='D' or sensores.superficie[2]=='a'){
							accion=actTURN_R;
							brujula=(brujula+1)%4;
						}
						else{
							if (brujula==0){
								fil--;
							}
							else if (brujula==1){
								col++;
							}
							else if (brujula==2){
								fil++;
							}
							else
								col--;
						}
					}
					actual.fila=fil;
					actual.columna=col;
					actual.orientacion=brujula;


					
					contador_aux++;
					cout << "Contador: "<<contador_aux<<endl;
					cout <<"Longitud del plann: "<<plan.size()<<endl<<endl;

					
					
				}
			}
		}
		

			

	



  return accion;
}


// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen, destino, plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
				  return pathFinding_CosteMinimo(origen, destino, plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
						// Incluir aqui la llamada al algoritmo de búsqueda usado en el nivel 2
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M' or casilla =='D')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}



struct nodo{
  estado st;
  list<Action> secuencia;
};

struct costo{
  nodo n;
  int cost;
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};




// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados, los que ya ha explorado
	stack<nodo> pila;											// Lista de Abiertos

  	nodo current;
	current.st = origen;  
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);  //Te lo mete en los nodos que ya han sido visitados

nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	int longitud_plan=plan.size();
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados, los que ya ha explorado
	stack<nodo> pila;											// Lista de Abiertos

  
	
	list<list<nodo>> ll;
	list<list<nodo>>::iterator itr;
	
	bool encontrado=false;

	nodo nodo_aux;
	
	nodo_aux.st = origen;  
	nodo_aux.secuencia.empty();


	list<nodo> listaprimero;
	listaprimero.push_back(nodo_aux);
	ll.push_front(listaprimero);
	
	itr=ll.begin();
	
	
	list<nodo> lista_aux;

	generados.insert(nodo_aux.st);
	while (!encontrado){
		
		list<nodo>::iterator it;
		list<nodo> aux;

		list<nodo>tl=(*itr);
		for (it=tl.begin(); it!=tl.end(); it++){
			//cout << "columna "<<(*it).st.columna<<endl;
			aux.push_back(*it);
		}
		
	
		list<nodo>::iterator itaux;
		for (itaux=aux.begin(); itaux!=aux.end() && encontrado==false; itaux++){


			nodo hijoForward = *itaux;
			if (!HayObstaculoDelante(hijoForward.st)){
				if (generados.find(hijoForward.st) == generados.end()){
					hijoForward.secuencia.push_back(actFORWARD);
					lista_aux.push_back(hijoForward);
				}

			}

			generados.insert(hijoForward.st);

			if (hijoForward.st.fila==destino.fila and hijoForward.st.columna == destino.columna){
				encontrado=true;
				plan=hijoForward.secuencia;
				
		
			}

			nodo hijoTurnR = *itaux;
			
			hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
			if (generados.find(hijoTurnR.st) == generados.end()){
				hijoTurnR.secuencia.push_back(actTURN_R);
				lista_aux.push_back(hijoTurnR);

			}


			
			generados.insert(hijoTurnR.st);

			if (hijoTurnR.st.fila==destino.fila and hijoTurnR.st.columna == destino.columna){
				encontrado=true;
				plan=hijoTurnR.secuencia;
				
			}


			// Generar descendiente de girar a la izquierda
			nodo hijoTurnL = *itaux;
			
			hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
			if (generados.find(hijoTurnL.st) == generados.end()){
				hijoTurnL.secuencia.push_back(actTURN_L);
				lista_aux.push_back(hijoTurnL);

			}



			generados.insert(hijoTurnL.st);

			if (hijoTurnL.st.fila==destino.fila and hijoTurnL.st.columna == destino.columna){
				encontrado=true;
				plan=hijoTurnR.secuencia;
				
			}
			
			
			

			// Generar descendiente de avanzar
			

			

		}
		
		ll.push_back(lista_aux);
		itr++;
		lista_aux.clear();
	}
	cout <<"Hay plan"<<endl;
	cout << "Longitud del plan: "<<plan.size();

	PintaPlan(plan);
	VisualizaPlan(origen,plan);
	return true;
}


int ComportamientoJugador::costeEstado(estado n){
	int a_devolver=0;
	
	char a = mapaResultado[n.fila][n.columna];
	
	switch (a){
		//Agua
		case 'A': a_devolver = 10; break;
		//Arboles o bosque
		case 'B': a_devolver = 5; break;
		//Suelo
		case 'T': a_devolver = 2; break;

		default: a_devolver=1; break;
	}
	
	return a_devolver;
}




/*return a_devolver;
void ComportamientoJugador::pathFinding_CosteMinimo_recursivo(estado origen,  estado destino, list<Action> &plan, list<costo> l, int longitud_maximo, set <estado, ComparaEstados> generados, map <int, int> costes){
	list<costo> lista_aux;
	list<costo>::iterator itaux;
	for (itaux=l.begin(); itaux!=l.end(); itaux++){

	costo hijoForward = *itaux;
	//int longitud1=longitud;
	//cout << "longitud1: "<<longitud1<<endl;
	hijoForward.cost+=costeEstado(hijoForward.n.st);
	//cout << "longitud: "<<hijoForward.cost<<endl;
	//cout << "longitud_maximo: "<<longitud_maximo<<endl;
	cout << "Fila nodo: "<< hijoForward.n.st.fila << " columna: "<<hijoForward.n.st.columna<<" orientacion "<<hijoForward.n.st.orientacion<<endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			if (!HayObstaculoDelante(hijoForward.n.st)){
				if (generados.find(hijoForward.n.st) == generados.end()){
						cout << "Hola2"<<endl;
						hijoForward.n.secuencia.push_back(actFORWARD);
						generados.insert(hijoForward.n.st);
						int valor_aux=hijoForward.n.st.fila+100*hijoForward.n.st.columna+10000*hijoForward.n.st.orientacion;
						costes.insert ( std::pair<int,int>(valor_aux,hijoForward.cost) );
						if (hijoForward.n.st.fila==destino.fila and hijoForward.n.st.columna == destino.columna){
							if (hijoForward.cost<longitud_maximo){
								//cout << "longitud: "<<hijoForward.cost<<endl;
								plan=hijoForward.n.secuencia;
								longitud_maximo=hijoForward.cost;
								
							}
						}

						if (hijoForward.cost<longitud_maximo){
							
							pathFinding_CosteMinimo_recursivo(origen, destino, plan, hijoForward, longitud, longitud_maximo, generados, costes);
							lista_aux.push_back(hijoForward);
						}
					}
				else{

						hijoForward.n.secuencia.push_back(actFORWARD);
						hijoForward.cost+=costeEstado(hijoForward.n.st);
						int valor_aux=hijoForward.n.st.fila+100*hijoForward.n.st.columna+10000*hijoForward.n.st.orientacion;
						if (costes[valor_aux]>hijoForward.cost){
							costes.erase(valor_aux);
							costes.insert ( std::pair<int,int>(valor_aux,hijoForward.cost) );
							if (hijoForward.n.st.fila==destino.fila and hijoForward.n.st.columna == destino.columna){
								if (hijoForward.cost<longitud_maximo){
									plan=hijoForward.n.secuencia;
									longitud_maximo=hijoForward.cost;
								}
							}
							if (hijoForward.cost<longitud_maximo)
								pathFinding_CosteMinimo_recursivo(origen, destino, plan, hijoForward, longitud1, longitud_maximo,generados, costes);
								lista_aux.push_back(hijoForward);
						}
				}


				

			}

			//int longitud2=longitud;
			costo hijoTurnR = *itaux;
			
			hijoTurnR.n.st.orientacion = (hijoTurnR.n.st.orientacion+1)%4;
			hijoTurnR.cost+=1;
			if (generados.find(hijoTurnR.n.st) == generados.end()){
				cout <<"Hola3"<<endl;
					hijoTurnR.n.secuencia.push_back(actTURN_R);
					generados.insert(hijoTurnR.n.st);
					int valor_aux=hijoTurnR.n.st.fila+100*hijoTurnR.n.st.columna+10000*hijoTurnR.n.st.orientacion;
					costes.insert ( std::pair<int,int>(valor_aux,hijoTurnR.cost) );
					if (hijoTurnR.cost<longitud_maximo)
						pathFinding_CosteMinimo_recursivo(origen, destino, plan, hijoTurnR, longitud2, longitud_maximo, generados, costes);
						lista_aux.push_back(hijoTurnR);
				
			}
			else {
				hijoTurnR.n.secuencia.push_back(actTURN_R);
				int valor_aux=hijoTurnR.n.st.fila+100*hijoTurnR.n.st.columna+10000*hijoTurnR.n.st.orientacion;
						if (costes[valor_aux]>hijoTurnR.cost){
							costes.erase(valor_aux);
							costes.insert ( std::pair<int,int>(valor_aux,hijoTurnR.cost) );

							if (hijoTurnR.cost<longitud_maximo)
								pathFinding_CosteMinimo_recursivo(origen, destino, plan, hijoTurnR, longitud2, longitud_maximo, generados, costes);
								lista_aux.push_back(hijoTurnR);
						}
			}

			


			
			costo hijoTurnL = *itaux;
			
			hijoTurnL.n.st.orientacion = (hijoTurnL.n.st.orientacion+3)%4;
			hijoTurnL.cost+=1;
			if (generados.find(hijoTurnL.n.st) == generados.end()){
				cout << "Hola4"<<endl;
					hijoTurnL.n.secuencia.push_back(actTURN_L);
					generados.insert(hijoTurnL.n.st);
					int valor_aux=hijoTurnL.n.st.fila+100*hijoTurnL.n.st.columna+10000*hijoTurnL.n.st.orientacion;
					costes.insert ( std::pair<int,int>(valor_aux,hijoTurnL.cost) );
					if (hijoTurnL.cost<longitud_maximo)
						pathFinding_CosteMinimo_recursivo(origen, destino, plan, hijoTurnL, longitud3, longitud_maximo, generados, costes);
						lista_aux.push_back(hijoTurnL);
			}
			else {
				hijoTurnL.n.secuencia.push_back(actTURN_L);
				int valor_aux=hijoTurnL.n.st.fila+100*hijoTurnL.n.st.columna+10000*hijoTurnL.n.st.orientacion;
						if (costes[valor_aux]>hijoTurnL.cost){
							costes.erase(valor_aux);
							costes.insert ( std::pair<int,int>(valor_aux,hijoTurnL.cost) );

							if (hijoTurnL.cost<longitud_maximo)
								pathFinding_CosteMinimo_recursivo(origen, destino, plan, hijoTurnL, longitud3, longitud_maximo, generados, costes);
								lista_aux.push_back(hijoTurnL);
						}
			}
		}
		if (!lista_aux.empty())	
			pathFinding_CosteMinimo_recursivo(origen, destino, plan, lista_aux, longitud_maximo, generados, costes);

			
}
*/


bool ComportamientoJugador::pathFinding_CosteMinimo(const estado &origen, const estado &destino, list<Action> &plan){
	

	plan.clear(); 
	set<estado, ComparaEstados> generados;
	int aux=0;
	list<costo> l;
	l.clear();
	

	

	
	//generados.insert(origen);
	nodo nodo_aux;
	nodo_aux.st=origen;
	nodo_aux.secuencia.empty();
	costo c;
	c.cost=0;
	c.n=nodo_aux;
	l.push_back(c);

	generados.insert(origen);
	costo current=c;
	int minimo_coste=10000;
	int contador=0;
	int contador_minimo;
	generados.insert(nodo_aux.st);
	

	while (!(current.n.st.fila==destino.fila and current.n.st.columna==destino.columna)){
		
		
		generados.insert(current.n.st);
		costo hijoTurnR=current;
		hijoTurnR.n.st.orientacion = (hijoTurnR.n.st.orientacion+1)%4;
		hijoTurnR.cost+=1;
		hijoTurnR.n.secuencia.push_back(actTURN_R);
		
		if (generados.find(hijoTurnR.n.st)==generados.end()){
			l.push_back(hijoTurnR);
			//generados.insert(hijoTurnR.n.st);
		}

		costo hijoTurnL=current;
		hijoTurnL.n.st.orientacion=(hijoTurnL.n.st.orientacion+3)%4;
		hijoTurnL.cost+=1;
		hijoTurnL.n.secuencia.push_back(actTURN_L);
		if (generados.find(hijoTurnL.n.st)==generados.end()){
			l.push_back(hijoTurnL);
			//generados.insert(hijoTurnL.n.st);
		}


		
		costo hijoForward = current;
		
		hijoForward.cost+=costeEstado(hijoForward.n.st);
		if (!HayObstaculoDelante(hijoForward.n.st)){
			hijoForward.n.secuencia.push_back(actFORWARD);
			if (generados.find(hijoForward.n.st)==generados.end()){
				l.push_back(hijoForward);
				//generados.insert(hijoForward.n.st);
			}
		}


		minimo_coste=1000;
		contador=0;
		std::list<costo>::iterator it;
		std::list<costo>::iterator it2;
		for (it=l.begin();it!=l.end(); ++it){
			if ((*it).cost<minimo_coste){
				minimo_coste=(*it).cost;
				it2=it;
				//contador_minimo=contador;
			}
			//contador++;
		}

		/*it=l.begin();
		for (int i=0; i<contador_minimo; i++)
			++it;*/
		/*cout << (*it).n.st.fila << " "<<(*it).n.st.columna << " "<<(*it).n.st.orientacion<<endl;
		cout << " costo: "<<(*it).cost<<endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));*/
		current=*it2;
		
		l.erase(it2);


	}
	plan=current.n.secuencia;
	cout <<"Hay plan"<<endl;
	cout << "Longitud del plan: "<<plan.size();
	cout << "Coste del plan "<<current.cost;
	PintaPlan(plan);
	VisualizaPlan(origen,plan);
	return true;
}




// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
