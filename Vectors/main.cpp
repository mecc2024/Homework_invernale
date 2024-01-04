#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "Boid.h"

const int num_boids {50};
const float MINSPEED = 0.0;
const float MAXSPEED = 5;

const float LEFTMARGIN = 0.0;
const float RIGHTMARGIN = 500.0;
const float BOTTOMMARGIN = 0.0;
const float TOPMARGIN = 500.0;

const float AVOIDFACTOR = 0.5;
const float ALIGNFACTOR = 1;
const float CENTERINGFACTOR = 1.1;
const float TURNFACTOR = 5; 

const float d_ca = 20;
const float d_sep = 10;

int main()
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    
    std::vector<Boid> boids;
    
    // Generazione dei boid
    for (int i = 0; i < num_boids; ++i) {
        boids.push_back(Boid());
    }

    // Apri un file in modalità scrittura
    std::ofstream outputFile("coordinates.txt");

    // Scrivi le variabili nella prima riga del file
    outputFile << LEFTMARGIN << " " << RIGHTMARGIN << " " << BOTTOMMARGIN << " " << TOPMARGIN << std::endl;

    // Simulazione per 100 secondi
    for (int time_step = 0; time_step < 1000; ++time_step) {  // 100 passi di simulazione

        // Stampa la posizione di ogni boid
        for (int i = 0; i < num_boids; ++i) {
            outputFile << boids[i].position().get_x() << " " << boids[i].position().get_y() << " ";
        }

        outputFile << std::endl;

        // Esecuzione delle funzioni di separation, alignment e cohesion
        for (int i = 0; i < num_boids; ++i) {
            
            boids[i].handleScreenBorders(LEFTMARGIN, RIGHTMARGIN, BOTTOMMARGIN, TOPMARGIN, TURNFACTOR);
            boids[i].cohesion(boids, CENTERINGFACTOR, d_ca);
            boids[i].alignment(boids, ALIGNFACTOR, d_ca);
            boids[i].separation(boids, AVOIDFACTOR, d_sep);
            boids[i].handleScreenBorders(LEFTMARGIN, RIGHTMARGIN, BOTTOMMARGIN, TOPMARGIN, TURNFACTOR);
            boids[i].limitSpeed(MINSPEED, MAXSPEED);
            boids[i].pos_update();
        }
    }

    // Chiudi il file
    outputFile.close();

    return 0;
}



