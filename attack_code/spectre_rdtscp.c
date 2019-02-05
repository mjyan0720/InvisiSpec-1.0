#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h> /* for rdtscp and clflush */

/********************************************************************
Victim code.
********************************************************************/
unsigned int array1_size = 16;
uint8_t unused1[64];
uint8_t array1[640] = {};

uint8_t temp;

void victim_function(size_t x) {
  if (x < array1_size) {
    temp &= array1[x];
  }
}

/********************************************************************
Analysis code
********************************************************************/

size_t malicious_x = 128;//index to array1
#define CACHE_HIT_THRESHOLD (80) /* assume cache hit if time <= threshold */

/* Report best guess in value[0] and runner-up in value[1] */
void testSpec(size_t fetch_index) {
  int tries, i, j, k, mix_i, junk = 0;
  register uint64_t time1, time2;
  volatile uint8_t * addr;

  for (tries = 20; tries > 0; tries--) {

    _mm_clflush( & array1_size); //make branch resolved sloowly
    _mm_clflush( array1+malicious_x ); //flush out-of-boundary address
    _mm_clflush( array1+fetch_index ); //flush within-boundary address

    for (volatile int z = 0; z < 1000; z++) {} /* Delay (can also mfence) */
   
    /*fetch one element in the array*/
    victim_function(fetch_index);
    
      
      for (volatile int z = 0; z < 1000; z++) {} /* Delay (can also mfence) */
      
      time1 = __rdtscp( &junk ); 
      time1 = __rdtscp( &junk ); 
      
      addr = array1 + malicious_x;
      junk = * addr; // MEMORY ACCESS TO TIME  
      
      time2 = __rdtscp( &junk ) - time1; // READ TIMER & COMPUTE ELAPSED TIME  
      time2 = __rdtscp( &junk ) - time1; // READ TIMER & COMPUTE ELAPSED TIME  
      
      
      printf("time = %ld\n", time2);
    }
}



int main(int argc, const char * * argv) {

    printf("malicious_x = %p... ", (void * ) malicious_x);
    
    printf("fetch 0th element, \nno misprediction, \nsuppose to see miss + no squash\n");
    testSpec(0);
    
    printf("fetch malicious_x, \nmispredict with speculative load, \nsuppose to see hit + squash\n");
    testSpec(malicious_x);
    
    printf("fetch malicious_x * 2, \nmispredict with speculative load different address, \nsuppose to see miss + squash\n");
    testSpec(malicious_x*2);
    return (0);
}
