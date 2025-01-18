#include <stdio.h>
#include <stdlib.h>

typedef struct NODO{
    int dato;
    struct NODO *next;
}nodo;

nodo* CreaNodo(int valore){
    nodo* temp = malloc(sizeof(nodo));
    if(temp == NULL){
        printf("ERRORE. Allocazione fallita.");
        return NULL;
    }
    
    temp->dato = valore;
    temp->next = NULL;
    
    return temp;
}

nodo* CreaLista(int numElementi){
    nodo *head = NULL, *tail, *temp;
    int i = 1;
    head = CreaNodo(i*10);
    tail = head;
    
    for(i++; i<=numElementi; i++){
        tail->next = CreaNodo(i*10);
        if(tail->next == NULL){
            printf("ERRORE. Allocazione del nodo numero %d fallita.\n",i);
            return NULL;
        }
        tail = tail->next;
    }
    
    return head;
}

void StampaLista(nodo *head){
    nodo *nodoCorrente = head;
    int cont=1;

    while(nodoCorrente != NULL){
        printf("Nodo %d:\n"
        "\tDato: %d\n"
        "\tProssimo nodo: %p\n",cont, nodoCorrente->dato, nodoCorrente->next);
        cont++;
        nodoCorrente = nodoCorrente->next;
    }
}

nodo* CercaNodoValore(nodo *head, int valore){
    if(head->dato == valore){
        return head;
    }
    
    nodo *nodoPrecedente = head;
    while(nodoPrecedente != NULL){
        if(nodoPrecedente->next->dato == valore){
            return nodoPrecedente;
        }
        nodoPrecedente = nodoPrecedente->next;
    }

    printf("Il dato ricercato non è contenuto nella lista.\n");
    return NULL;
}

nodo* CercaNodoPosizione(nodo *head, int posizione){
    if(posizione == 1){
        return head;
    }
    
    nodo *nodoPrecedente = head;
    int indice = 1;
    while(nodoPrecedente != NULL){
        if(posizione-1 == indice){
            return nodoPrecedente;
        }
        indice++;
        nodoPrecedente = nodoPrecedente->next;
    }

    printf("Nella lista non è presente un nodo alla posizione numero %d", posizione);
    return NULL;
}

void EliminaNodoValore(nodo **head, int valore){
    nodo *nodoPrecedente = CercaNodoValore(*head, valore);
    if(nodoPrecedente == *head){
        nodo *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    else{
        if(nodoPrecedente->next->next == NULL){
            free(nodoPrecedente->next);
            nodoPrecedente->next = NULL;
        }
        else{
            nodo *temp = nodoPrecedente->next->next;
            free(nodoPrecedente->next);
            nodoPrecedente->next = temp;
        }
    }
}

void EliminaNodoPosizione(nodo **head, int posizione){
    nodo *nodoPrecedente = CercaNodoPosizione(*head, posizione);
    if(nodoPrecedente == *head){
        nodo *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    else{
        if(nodoPrecedente->next->next == NULL){
            free(nodoPrecedente->next);
            nodoPrecedente->next = NULL;
        }
        else{
            nodo *temp = nodoPrecedente->next->next;
            free(nodoPrecedente->next);
            nodoPrecedente->next = temp;
        }
    }
}

void InserisciNodo(nodo **head, int posizione, int valore){
    nodo *nodoPrecedente = CercaNodoPosizione(*head, posizione);
    if(nodoPrecedente == *head){
        nodo *temp = *head;
        *head = CreaNodo(valore);
        (*head)->next = temp;
    }
    else if(nodoPrecedente->next == NULL){
        nodoPrecedente->next = CreaNodo(valore);
    }
    else{
        nodo *temp = nodoPrecedente->next;
        nodoPrecedente->next = CreaNodo(valore);
        nodoPrecedente->next->next = temp;
    }
}

int main(){

    nodo *head;
    int numNodi = 5;
    
    head = CreaLista(numNodi);
    
    printf("La lista è formata dai seguenti nodi:\n");
    StampaLista(head);
    getchar();

    EliminaNodoValore(&head, 40);
    printf("\n\nLa lista modificata è formata dai seguenti nodi:\n");
    StampaLista(head);
    getchar();

    InserisciNodo(&head, 4, 40);
    printf("La lista è formata dai seguenti nodi:\n");
    StampaLista(head);
    getchar();

    EliminaNodoPosizione(&head, 3);
    printf("La lista è formata dai seguenti nodi:\n");
    StampaLista(head);
    getchar();

    InserisciNodo(&head, 3, 30);
    printf("La lista è formata dai seguenti nodi:\n");
    StampaLista(head);
    getchar();

    InserisciNodo(&head, 1, 100);
    InserisciNodo(&head, 6, 200);
    printf("La lista è formata dai seguenti nodi:\n");
    StampaLista(head);
    getchar();

    return 0;
}