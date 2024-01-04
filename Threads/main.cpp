#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
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
const float CENTERINGFACTOR = 1.5;
const float TURNFACTOR = 5; 

const float d_ca = 20;
const float d_sep = 10;

std::vector<Boid> boids(num_boids);
std::vector<bool> posUpdated(num_boids, false);
std::condition_variable updateCV;
bool allPositionsUpdated = false;
std::mutex saveMutex_;

bool allTrue(const std::vector<bool>& vec) {
    for (bool value : vec) {
        if (!value) {
            return false;
        }
    }
    return true;
}

void simulateBoidBehaviors(int id, int time_step){
    if (time_step == 0){
        // Generazione dei boid
        boids[id] = Boid();
    }
    else{
        boids[id].cohesion(boids, CENTERINGFACTOR, d_ca);
        boids[id].alignment(boids, ALIGNFACTOR, d_ca);
        boids[id].separation(boids, AVOIDFACTOR, d_sep);
        boids[id].limitSpeed(MINSPEED, MAXSPEED);
        boids[id].pos_update();
        boids[id].handleScreenBorders(LEFTMARGIN, RIGHTMARGIN, BOTTOMMARGIN, TOPMARGIN, TURNFACTOR);
        boids[id].pos_update();
    }

    // Impostare la variabile posUpdated a true quando la posizione è stata aggiornata
    std::unique_lock<std::mutex> mlock(saveMutex_);
    posUpdated[id] = true;

    if (allTrue(posUpdated)){
        // Impostare la variabile di controllo e notificare
        allPositionsUpdated = true;
        updateCV.notify_one();
    }
    mlock.unlock();
}

void saveBoidPositions(std::ofstream& fileOutput) {
    std::unique_lock<std::mutex> mlock(saveMutex_);

    while (!allPositionsUpdated) {
        updateCV.wait(mlock);
    }
    
    // Stampa la posizione di ogni boid
    for (int i = 0; i < num_boids; ++i) {
        fileOutput << boids[i].position().get_x() << " " << boids[i].position().get_y() << " ";
    }

    fileOutput << std::endl;

    // Resetta le variabili di controllo
    allPositionsUpdated = false;
    std::fill(posUpdated.begin(), posUpdated.end(), false);
}

int main()
{
    srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<std::thread> boidThreads;

    // Apri un file in modalità scrittura
    std::ofstream outputFile("coordinates.txt");

    // Scrivi le variabili nella prima riga del file
    outputFile << LEFTMARGIN << " " << RIGHTMARGIN << " " << BOTTOMMARGIN << " " << TOPMARGIN << std::endl;

    // Simulazione per 1000 secondi
    for (int time_step = 0; time_step < 1000; ++time_step) {  // 1000 passi di simulazione

        // Esecuzione delle funzioni di separation, alignment e cohesion
        for (int i = 0; i < num_boids; ++i) {
            boidThreads.push_back(std::thread(simulateBoidBehaviors, i, time_step));
        }

        // Terminate all threads
        for (auto& boid : boidThreads) {
            boid.join();
        }        

        std::thread saveThread(saveBoidPositions, std::ref(outputFile));

        // Terminate the save thread
        saveThread.join();

        // Pulisci il vettore delle thread
        boidThreads.clear();
    }

    // Chiudi il file
    outputFile.close();

    return 0;
}