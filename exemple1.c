// Deux taches threads créées par un processus main(void)
// Les deux tâches s'éxécutent de manière concurrentes
// Les taches sont 'join' au processus père

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
    
    //CREATION EFFECTIVE DE LA TACHE 1
    // thread	: tache1	: Pointeur de type pthread contenant l'identificateur de la tâche qui vient d'être créée
    // attr	: NULL		: Variable de type pthread_attr_t, correspond au conteneur qui créer les propriétés de la tache (ordonnance, priorité, tache joignable/déjoinable)
    // start_routine : fonc	: fonction qui va être exécutée
    // arg	: (void*)1	: pointeur qui correspond au valeurs mis en paramètres de fonc
    pthread_create(&tache1, NULL, fonc, (void*) 1); 
    pthread_create(&tache2, NULL, fonc, (void*) 2); 
  
    // ATTENDRE LA FIN DE LA TACHE
    // thread1	: tache1	: Pointeur vers la tache que main doit attendre
    // thread_retun : NULL	: Eventuelle valeure de sortie de la tache1
    pthread_join(tache1, NULL); //la fonction principale main(void), doit attendre la fin de l'exécution de la tâche tache1 
    pthread_join(tache2, NULL); 
    return 0; 
}
