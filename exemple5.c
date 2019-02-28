// Mutex et variable condition
// Une tache peut s'endormir en fonction de la valeur de la variable partagé
// Cette tache ne se réveillera que si la variable respecte une certaine condition
// Elle ne se réveillera que lorsqu'une autre tache accédera à la donnée et rendre la condition vraie
//On associe dans ce cas une certaine condition au MUTEX

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 


typedef struct {   //déclaration du type de la donnée partagée 
    float taille; 
    float poids; 
} type_donneePartagee; 


pthread_mutex_t verrou; //déclaration du verrou 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; //initialisation de la variable condition 

type_donneePartagee donneePartagee; //déclaration de la donnée partagée 

void* tache1(void *arg){ // déclaration du corps de la tâche qui lit la donnée partagée. On considère qu'elle s'exécute indéfiniment 
 type_donneePartagee ma_donneePartagee; 
 int i=0; 
 while(i<10){ 
    pthread_mutex_lock(&verrou); // La tache1 devient propriétaire du mutex 
    pthread_cond_wait(&cond, &verrou); //la tache1 s'endorre à cet endroit ci. Elle libère le verrou tant qu'elle est endormis. Elle ne se réveillera que lorsque la condition cond sera rendu VRAI dans la tache2 
    ma_donneePartagee = donneePartagee; 
    pthread_mutex_unlock(&verrou); // La tache1 relache le mutex 
    printf("La tache %s vient de lire la donnee partagee\n", (char*) arg); 
    //utilisation de ma_donneePartagee 
    sleep(1); 
    i++; 
 } 
} 

void* tache2(void *arg){ // déclaration du corps de la tâche qui modifie la donnée partagée. On considère qu'elle s'exécute indéfiniment 
 int i=0; 
 while(i<10){ 
    pthread_mutex_lock(&verrou); 
    donneePartagee.taille = 100 + rand()%101; //choisir une taille au hasard entre 100 et 200cm. // Dans un programme réel, les données à modifier peuvent provenir de capteurs et nécessitent un code un peu plus complexe 
    donneePartagee.poids = 10 + rand()%101; 
    if(donneePartagee.taille >= 120 && donneePartagee.poids >= 60){ 
       pthread_cond_signal(&cond); // Si donneePartage respecte les conditions, alors la condition pThread deviendra vraie et réveillera la tache1. Cette fonction rend la variable pthread_cond_t cond vrai. Si on désire réveiller plusieurs tâches sur la même condition cond on peux utiliser la fonction pthread_cond_broadcast(cond) 
    } 
    pthread_mutex_unlock(&verrou); 
    printf("La tache %s vient de modifier la donnee partagee\n", (char*) arg); 
    sleep(1); 
    i++; 
 } 
} 

int main(void) 
{ 
    srand(200); 
    pthread_t th1, th2; 
    pthread_mutex_init(&verrou, NULL); 

    //initialisation de la donnée partagée 
    donneePartagee.taille = 100 + rand()%101; 
    donneePartagee.poids = 10 + rand()%101; 

    pthread_create(&th1, NULL, tache1, "1"); 
    pthread_create(&th2, NULL, tache2, "2"); 

    pthread_join(th1, NULL); 
    pthread_join(th2, NULL); 
    return 0; 
} 
