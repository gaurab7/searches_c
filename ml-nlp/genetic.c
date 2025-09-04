#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
//very basic implementation of GA-->Maximize the num of 1s in a bin num


#define POP 50//num of organisms in each generation
#define CHROMLEN 8//num of genes in an organism-->no of bits here-->1 is gud 0 is bad
#define NUMGENS 100//max num of generations for a run
#define MUTRATE 0.1//03% chance of mutation-->randomly flip a gene/bit here
#define NUMCP 2//num of crossover points->crossover point is the point at which we mix the parents
//in single point we pretty much break the parents in two parts at the crossover point
//then we mix them(parAFirstpart+parBrest)
//in multi-point we still do the sem thing but broken segments are smaller
//risk of destroying a gud gene sequence is higher in multi point but speed is faster
//dont use too many-->at some point it just becomes random
#define ELITENUM 4

struct organism
{
  int chromosomes[CHROMLEN];
  int fitnessValue;
}pool[POP];


void initializePool() {
    srand(time(0)); // seed random generator
    for(int i=0; i<POP; i++){
        for(int j=0; j<CHROMLEN; j++){
            pool[i].chromosomes[j] = rand() % 2; // 0 or 1
        }
        pool[i].fitnessValue = 0; // initial fitness 0
    }
}

void printPool() {
    int col=0;
    for(int i=0; i<POP; i++){
        printf("Chromosome %2d: ", i);
        for(int j=0; j<CHROMLEN; j++){
            printf("%d", pool[i].chromosomes[j]);
        }
    col++;
    if(col == 5){      // new line only if 5 iterations have passed since last new line-->4 cols
        printf("\n");
        col = 0;
    } else {
        printf("\t\t"); 
    }
        
    }
}


int fitness(struct organism pool[POP]){
    for(int i=0;i<POP;i++){
        pool[i].fitnessValue=0;//initailly 0
        for(int j=0;j<CHROMLEN;j++){
            if(pool[i].chromosomes[j] == 1)
            {
                pool[i].fitnessValue += 1;//incr if 1
            }
        }
    }
}

struct organism elites[ELITENUM];//elitism to preserve few best ones from previous gen-->5%approx
int eliteIndices[ELITENUM];

int preserveElites(struct organism pool[POP], struct organism elites[4]){
      for(int e = 0; e < ELITENUM+1; e++) {
        int bestIndex = -1;
        int bestFit = -1;

        for(int i = 0; i < POP; i++) {
            if(pool[i].fitnessValue > bestFit) {
                bestFit = pool[i].fitnessValue;
                bestIndex = i;//remeber elites position
            }
        }

        elites[e] = pool[bestIndex];
        eliteIndices[e] = bestIndex; //for tournamertselect
        pool[bestIndex].fitnessValue = -1; // mark as used so not picked again in the for loop above
    }
}


int isElite(int idx) {
    for(int e = 0; e < ELITENUM+1; e++) {
        if(idx == eliteIndices[e]) return 1;
    }
    return 0;
}


int select(struct organism pool[POP]) {
    int bestIndex;
    do {
        bestIndex = rand() % POP;
    } while(isElite(bestIndex));
    //non elite candidate
    int bestFit = pool[bestIndex].fitnessValue;

    //take parents from the rest avoiding elitse
    for(int i = 0; i < POP; i++){
        int idx;
        do {
            idx = rand() % POP;
        } while(isElite(idx));
        if(pool[idx].fitnessValue > bestFit){
            bestIndex = idx;
            bestFit = pool[idx].fitnessValue;
        }
    }
    return bestIndex;
}

// 2-point crossover
void crossover(int parent1[CHROMLEN], int parent2[CHROMLEN], int child1[CHROMLEN], int child2[CHROMLEN]) {
    int point1 = rand() % (CHROMLEN - 1);//random point from 0-7
    int point2 = rand() % (CHROMLEN - 1);
    if(point1 > point2){
        int temp = point1;
        point1 = point2;
        point2 = temp;
    }
    for(int i = 0; i < CHROMLEN; i++){
        if(i >= point1 && i < point2){
            child1[i] = parent2[i];
            child2[i] = parent1[i];
        } else {
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }
    }
}

void nextGeneration(struct organism pool[POP], struct organism elites[4]) {
    struct organism nextGen[POP];//next generation intialize
    //evaluate fitness
    fitness(pool);
    //preserve elites
    preserveElites(pool, elites);
    for(int e = 0; e < ELITENUM+1; e++)
        nextGen[e] = elites[e];//elites to nextgen

    //fill the rest using tournament + crossover
    int idx = ELITENUM+1;
    while(idx < POP){
        int p1 = select(pool);
        int p2 = select(pool);

        int child1[CHROMLEN], child2[CHROMLEN];
        crossover(pool[p1].chromosomes, pool[p2].chromosomes, child1, child2);

        // copy children to nextGen
        //from point 5.i.e next to elites
        for(int j = 0; j < CHROMLEN; j++){
            nextGen[idx].chromosomes[j] = child1[j];
        }
        idx++;
    }

    //copy nextGen back to pool
    for(int i = 0; i < POP; i++){
        pool[i] = nextGen[i];
    }
}


//mutating the whole pop after new gen is made
//mutation chance is very low--0.03-->3%
void mutate(struct organism pool[POP]) {
    for(int i = ELITENUM+1; i < POP; i++){ // start from 5 to skip the 4 elites
        for(int j = 0; j < CHROMLEN; j++){
            double r = (double)rand() / RAND_MAX; // random number [0,1)
            if(r < MUTRATE){
                pool[i].chromosomes[j] = 1 - pool[i].chromosomes[j]; // flip 0↔1
            }
        }
    }
}

int isAllIdeal(struct organism pool[POP]) {
    for(int i = 0; i < POP; i++) {
        for(int j = 0; j < CHROMLEN; j++) {
            if(pool[i].chromosomes[j] != 1) {
                return 0; // found a non-ideal chromosome
            }
        }
    }
    return 1; // all chromosomes are ideal
}

int isOneIdeal(struct organism pool[POP]) {
    for(int i = 0; i < POP; i++) {
        for(int j = 0; j < CHROMLEN; j++) {
            if(pool[i].chromosomes[j] == 1) {
                return 1; // found an ideal chromosome
            }
        }
    }
    return 0; //no ideal chromosome
}

int main(){
    int oneIdeal, allIdeal;
    initializePool();
    printf("The data pool before implementing Genetic Algorithm to Maximize no. of 1s\n");
    printPool();
    int genCount=0;
    for(int g=0;g<NUMGENS;g++){
        nextGeneration(pool, elites);
        genCount++;
        if(isAllIdeal(pool)){ 
            allIdeal = genCount;//mark at which gen the result has all candidates ideal
            //we break after finding the best possible solution so the final result wil have no 0s as mutate will not be executed if we find the best solution
            break; 
        }    
        if(isOneIdeal(pool)){
            oneIdeal = genCount;
        }
        mutate(pool);
    }
    printf("\n\nData pool after implementing Genetic Algorithm with Mutation Rate %2f:\n\n",MUTRATE);
    printPool();
    
    printf("\n\nIt took %d Generations to converge to all ideal candidate result (Mutation Rate %2f)\n\n", allIdeal, MUTRATE);
    printf("It took %d Generations to converge to a result with one ideal candidate (Mutation Rate %2f)\n\n", oneIdeal, MUTRATE);
    return 0;
}