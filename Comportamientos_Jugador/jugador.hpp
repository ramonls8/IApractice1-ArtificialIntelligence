#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
  int fil, col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      
      ResetState(size);
      last_action = actIDLE;

      // Crea el mapa auxiliar con suficientes casillas para no salirse
      // nunca de él, aunque no sepamos nuestra posición en el mapa
      unsigned int auxSize = size*2-1;
      vector<unsigned char> aux(auxSize, '?');
      for (unsigned int i=0; i<auxSize; i++)
        mapaAuxiliar.push_back(aux);
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
    // Variables de estado
    state st;
    Action last_action;
    bool wellLocated = false;
    vector<vector<unsigned char>> mapaAuxiliar;


    // Devuelve el estado a los valores por defecto
    bool ResetState(unsigned int size);

    // Devuelve si el sensor funciona y puede conocer la posición
    bool SensorIsWorking(const Sensores &sensores);

    // Informa de la posición actual
    void ShowInfo(const Sensores &sensores);

    // Actualiza state tras la última acción
    void UpdateState(const Sensores &sensores);


};

#endif
