//Rory Harrington
//R00233458
#ifndef DNA_H
#define DNA_H
//header file 
typedef struct{// Define the Base struct representing a DNA nucleotide
    char nucleotide;
}Base;

typedef struct Node{//Node struct for the DNA sequence linked list
    Base base; 
    double probabiltyGrowth;
    double probabiltyDeletion;
    double probabiltyMutation;
    struct Node* previousNode;
    struct Node* nextNode;
}Node;


typedef struct{//DNA Sequence struct to hold DNA sequence information
    double probabiltyGrowth;
    double probabiltyMutation;
    double probabiltyDeletion;
    int sequenceAge;
    int maxlifespan;
    Node* headNode;
    Node* tailNode;
}DNASequence;
// functions to implement
Base createNewBase(char nucleotide);
DNASequence* createDNASequence();
void addBase(DNASequence* sequence,char nucleotide);
void insertNewBase(DNASequence* sequence,char nucleotide, int basePosition);
void deleteBase(DNASequence* sequence, int basePosition);
void specialModifer(DNASequence* sequence);
void printDNASequence(DNASequence* sequence);
void simulateDNALifecycle(DNASequence* sequence);
int searchPattern(DNASequence* sequence, const char* pattern);
void clearDNASequence(DNASequence* sequence);
#endif