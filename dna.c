//Rory Harrington
//R00233458
#include "dna.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//implemenataion file 
Base createNewBase(char nucleotide){//create new base with the given data
    Base base;
    base.nucleotide= nucleotide;
    return base;
}

DNASequence* createDNASequence(){//create a new DNA sequence with the default values 
 DNASequence* sequence = (DNASequence*)malloc(sizeof(DNASequence));
    if (sequence) {//set the sequence properties 
        sequence->headNode = NULL;
        sequence->tailNode = NULL;
        sequence->sequenceAge = 0;
        sequence->maxlifespan = rand() % 43 + 8;
        sequence->probabiltyGrowth = 0.25;
        sequence->probabiltyDeletion = 0.25;
        sequence->probabiltyMutation = 0.0;
    }
    return sequence;
}

//add the base to the DNA sequence 
void addBase(DNASequence* sequence,char nucleotide){
    Node *newNode = (Node *) malloc (sizeof (Node));

  switch (nucleotide)
    {
    case 'A':
    case 'T':
    case 'C':
    case 'G':
      newNode->base = createNewBase (nucleotide);
      break;
    default:
      // Invalid DNA base nucleotide
      free (newNode);
      return;
    }

  newNode->previousNode = sequence->tailNode;
  newNode->nextNode = NULL;

  if (sequence->tailNode)
    {
      sequence->tailNode->nextNode = newNode;
    }
  else
    {
      sequence->headNode = newNode;
    }

  sequence->tailNode = newNode;
}

void insertNewBase(DNASequence* sequence,char nucleotide, int basePosition){// insert new base in the position
   if (basePosition < 0 || basePosition > sequence->sequenceAge + 1) {
        printf("Invalid position for insertion.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->base = createNewBase(nucleotide);

    if (basePosition == 0) {
        newNode->previousNode = NULL;
        newNode->nextNode = sequence->headNode;

        if (sequence->headNode != NULL) {
            sequence->headNode->previousNode = newNode;
        }
        sequence->headNode = newNode;
    } else {
        Node* current = sequence->headNode;
        for (int i = 0; i < basePosition - 1; i++) {
            current = current->nextNode;
        }

        newNode->previousNode = current;
        newNode->nextNode = current->nextNode;

        if (current->nextNode != NULL) {
            current->nextNode->previousNode = newNode;
        }
        current->nextNode = newNode;
    }
}

void deleteBase(DNASequence* sequence, int basePosition){// deletion of a  base in the position
   if (basePosition < 0 || basePosition >= sequence->sequenceAge) {
        return; //return without deleting, f the clause is true 
    }

    Node* current = sequence->headNode;
    for (int i = 0; i < basePosition; i++) {
        current = current->nextNode;
    }

    if (current->previousNode != NULL) {
        current->previousNode->nextNode = current->nextNode;
    } else {
        sequence->headNode = current->nextNode;
    }

    if (current->nextNode != NULL) {
        current->nextNode->previousNode = current->previousNode;
    } else {
        sequence->tailNode = current->previousNode;
    }

    free(current);
}


int searchPattern(DNASequence* sequence, const char* pattern) {// search for a pattern in the DNA sequence
    Node* current = sequence->headNode;
    int position = 0;
    int patternIndex = 0;
    
    while (current != NULL) {
        if (current->base.nucleotide == pattern[patternIndex]) {
            patternIndex++;
            if (pattern[patternIndex] == '\0') {
                return position - patternIndex + 1;
            }
        } else {
            patternIndex = 0;
        }
        
        current = current->nextNode;
        position++;
    }
    
    return -1; // Pattern not found
}


void specialModifier(DNASequence* sequence) {//apply the modified behavours in the system based on patterns
    int pos = searchPattern(sequence, "AAA");//checks for the pateren AAA
    if (pos != -1) {
        sequence->maxlifespan += pos + 1;
    }

    pos = searchPattern(sequence, "CCC");//checks for the pateren CCC
    if (pos != -1) {// Decrease the maximum lifespan of the sequence by the position of the pattern + 1
        // Ensure the minimum lifespan is 1
        sequence->maxlifespan -= pos + 1;
        if (sequence->maxlifespan < 1) {
            sequence->maxlifespan = 1;
        }
    }

    pos = searchPattern(sequence, "GGG");//checks for the pateren GGG
    if (pos != -1) {
        int deleteCount = 0;
        Node* current = sequence->headNode;
        while (current != NULL) {
            if (deleteCount % 2 == 1) {
                Node* next = current->nextNode;
                deleteBase(sequence, deleteCount);
                current = next;
            } else {
                current = current->nextNode;
            }
            deleteCount++;
        }
    }

    pos = searchPattern(sequence, "TTT");//checks for the pateren TTT
    if (pos != -1) {
        Node* current = sequence->headNode;
        while (current != NULL) {
            addBase(sequence, current->base.nucleotide);
            current = current->nextNode;
        }
    }
}



void printDNASequence(DNASequence* sequence){//prints the DNA sequence 
     Node* current = sequence->headNode;
    int age = 0;
    while (current != NULL && age < sequence->sequenceAge) {
        printf("%c", current->base.nucleotide);
        current = current->nextNode;
        age++;
    }
    printf("\n");
}
void simulateDNALifecycle(DNASequence* sequence) {//simulate the dna sequence 
    srand(time(NULL));
    while (sequence->sequenceAge < sequence->maxlifespan) {
        printf("DNA Age: %d | Probability of Mutation: %.2f\n", sequence->sequenceAge, sequence->probabiltyMutation);
        printDNASequence(sequence);

        if (sequence->sequenceAge >= 5) {
            sequence->probabiltyMutation = 0.1 + 0.01 * (sequence->sequenceAge - 5);
        }

        specialModifier(sequence);

        double growthProb = (double)rand() / RAND_MAX;
        if (growthProb <= sequence->probabiltyGrowth) {
            char newBase = "ACGT"[rand() % 4];
            addBase(sequence, newBase);
        }

        double deletionProb = (double)rand() / RAND_MAX;
        if (deletionProb <= sequence->probabiltyDeletion && sequence->sequenceAge > 0) {
            int deletePos = rand() % sequence->sequenceAge;
            deleteBase(sequence, deletePos);
        }

        double mutationProb = (double)rand() / RAND_MAX;
        if (mutationProb <= sequence->probabiltyMutation) {
            int mutatePos = rand() % sequence->sequenceAge;
            Node* current = sequence->headNode;
            for (int i = 0; i < mutatePos; i++) {
                current = current->nextNode;
            }
            current->base.nucleotide = "ACGT"[rand() % 4];
        }

        sequence->sequenceAge++;
    }

    printf("DNA sequence has reached the end of its lifespan.\n");
}

void clearDNASequence(DNASequence* sequence) {//another function to clear memory 
    Node* current = sequence->headNode;
    while (current != NULL) {
        Node* next = current->nextNode;
        free(current);
        current = next;
    }
    free(sequence);
}
