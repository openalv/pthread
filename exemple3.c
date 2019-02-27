#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 

void* fonc(void* arg){ 
 int i; 
 for(i=0;i<7;i++){ 
    printf("Tache %d : %d\n", (int) arg, i); 
    sleep(1); //attendre 1 seconde 
 } 
} 

int main(void) 
{ 
    pthread_t tache1, tache2; //déclaration des deux tâches 

    sched_param param; //structure de données permettant d'affecter la priorité sur une tache créée

    // Fonction qui oblige le système d'exploitation à prendre en compte les différents paramètres d'ordonnancement que va acquérir la tache
    // PTHREAD_EXPLICIT_SCHED : la tâche à créer sera forcée d'utiliser les paramètres d'ordonnancement contenus dans sa propriété attr ;
    // PTHREAD_INHERIT_SCHED : la tâche à créer héritera des propriétés d'ordonnancement de son processus créateur. Quels que soient les paramètres d'ordonnancement spécifiés dans attr, elle les ignorera si cette option est utilisée
    pthread_attr_setinheritshed(attr, 

    //CREATION DE L'ATTRIBUT PERMETTANT DE DETACHER LES TACHES DU PROCESSUS main()
    //Ainsi main() n'attendra pas la fin d'éxecution des taches 1 et 2 pour se terminer
    pthread_attr_t attr; // déclaration de la variable contenant les propriétés de la tâche
    pthread_attr_init(&attr); //initialisation de attr aux valeurs par défaut. Obligatoire avant toute manipulation de attr
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // affectation de la propriété détachable à attr
    
    //CREATION EFFECTIVE DE LA TACHE 1
    // thread	: tache1	: Pointeur de type pthread contenant l'identificateur de la tâche qui vient d'être créée
    // attr	: NULL		: Variable de type pthread_attr_t, correspond au conteneur qui créer les propriétés de la tache (ordonnance, priorité, tache joignable/déjoinable)
    // start_routine : fonc	: fonction qui va être exécutée
    // arg	: (void*)1	: pointeur qui correspond au valeurs mis en paramètres de fonc
    pthread_create(&tache1, NULL, fonc, (void*) 1); 
    pthread_create(&tache2, NULL, fonc, (void*) 2); 
 

    pthread_attr_destroy(&attr); // détruire attr pour libérer la mémoire allouée
    
    return 0; 
}
