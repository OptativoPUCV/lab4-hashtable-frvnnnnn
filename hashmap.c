#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}
void insertMap(HashMap *map, char *key, void *value) {
      int pos = hash(key, map->capacity);
      while (map->buckets[pos] != NULL) {
          pos = (pos + 1) % map->capacity;  
      }
      if (map->buckets[pos] == NULL) {
          map->buckets[pos] = malloc(sizeof(Pair));
          if (map->buckets[pos] == NULL) {
              
              return;
          }
      }
      map->buckets[pos]->key = key;  
      map->buckets[pos]->value = value;
      map->size++;
      map->current++;  
  }
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *aux = (HashMap *)malloc(sizeof(HashMap));
  aux->capacity = capacity;
  aux->size = 0;
  aux->current = -1;
  aux->buckets = (Pair **)calloc(capacity,              sizeof(Pair *));
  return aux;
    return NULL;
}

void eraseMap(HashMap * map,  char * key) {    
  long pos = hash(key, map->capacity);
      long aux = pos;
      do {
          if (map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) == 0) {
              map->buckets[pos]->key=NULL;
              map->size--;
            return;
          }
          pos = (pos + 1) % map->capacity;
      } while (pos != aux && map->buckets[pos] != NULL);
      return;
  }



Pair * searchMap(HashMap * map, char * key) {   
    long pos = hash(key, map->capacity);
    long aux = pos;
    do {
        if (map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) == 0) {
            map->current = pos;
            return map->buckets[pos];
        }
        pos = (pos + 1) % map->capacity;
    } while (pos != aux && map->buckets[pos] != NULL);
    return NULL;
}

Pair * firstMap(HashMap * map) {
  if(map == NULL || map->size==0){return NULL;}
    for (int i = 0; i < map->capacity; i++) {
        Pair *pair = map->buckets[i];
        if (pair != NULL) {
            return pair;
        }
    }
    return NULL;
}

Pair *nextMap(HashMap *map) {
    if (map == NULL || map->size == 0) {
        return NULL;}
    Pair *currentPair = map->buckets[map->current];
    for (int i = map->current + 1; i < map->capacity; i++) {
        Pair *pair = map->buckets[i];
        if (pair != NULL) {
            map->current = i;
            return pair;
        }
    }
    return NULL; 
}
