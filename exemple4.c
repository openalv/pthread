//Partage de données entre tâches
// Sémaphore d'exclusion partagée : mutex (verrou associé à une donnée partagée)

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 

typedef struct {   // déclaration du type de la donnée partagée 
    float taille; 
    float poids; 
} type_donneePartagee; 

pthread_mutex_t verrou; //déclaration du verrou 
type_donneePartagee donneePartagee; //déclaration de la donnée partagée 

void* tache1(void *arg){ // déclaration du corps de la tâche qui lit la donnée partagée. On considère qu'elle s'exécute indéfiniment 
 type_donneePartagee ma_donneePartagee; 
 int i=0; 
 while(i<10){ 
    pthread_mutex_lock(&verrou);// Prise du verrou par la tache1 
    ma_donneePartagee = donneePartagee; 
    pthread_mutex_unlock(&verrou); //Libération du verrou
    printf("La tache %s vient de lire la donnee partagee\n", (char*) arg); 
    //utilisation de ma_donneePartagee 
    sleep(1); 
    i++; 
 } 
} 
 
void* tache2(void *arg){ // déclaration du corps de la tâche qui modifie la donnée partagée. On considère qu'elle s'exécute indéfiniment 
 int i=0; 
 while(i<10){ 
    pthread_mutex_lock(&verrou); // Prise du verrou par la tache2 
    donneePartagee.taille = 100 + rand()%101; //choisir une taille au hasard entre 100 et 200cm. // Dans un programme réel, les données à modifier peuvent provenir de capteurs et nécessitent un code un peu plus complexe 
    donneePartagee.poids = 10 + rand()%101; 
    pthread_mutex_unlock(&verrou); // Libération du verrou 
    printf("La tache %s vient de modifier la donnee partagee\n", (char*) arg); 
    sleep(1); 
    i++; 
 } 
} 

int main(void) 
{ 
    srand(200); 
    pthread_t th1, th2; 
    pthread_mutex_init(&verrou, NULL); // Initialisation du verrou 

    //initialisation de la donnée partagée 
    donneePartagee.taille = 100 + rand()%101; 
    donneePartagee.poids = 10 + rand()%101; 

    pthread_create(&th1, NULL, tache1, "1"); 
    pthread_create(&th2, NULL, tache2, "2"); 

    pthread_join(th1, NULL); 
    pthread_join(th2, NULL); 
    return 0; 
} 
