// nicholas Jackson netID naj 273
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cachelab.h"

int s, E, b, t = 0;
char h = 0, v = 0;



void printUsage()
{
    printf("Usage: [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h         help flag\n");
    printf("  -v         verbose flag.\n");
    printf("  -s <num>   set index bits.\n");
    printf("  -E <num>   lines in selected set.\n");
    printf("  -b <num>   block offset in bits.\n");
    printf("  -t <file>  file containing traces\n");
    exit(0);
}

int evicts = 0, hits = 0, misses = 0;
char trace_file[100];
struct lines{
    unsigned long long line_label;int time;char availability;
};
struct lines *cache;
void InputVal(int argc, char *argv[]){
    int optc = 0;
    while((optc = getopt(argc, argv, "s:E:b:t:hv")) != -1){
        switch (optc) {
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strncpy(trace_file, optarg, 100);
                break;
            case 'v':
                v = 1;
                break;
            case 'h':
                printUsage();
                break;
            default:
                break;
        }
    }
}


void RunSim(unsigned long long address)
{
	int LRU = ++t, empty;
   
    int Cindex = E * ((address>>b)&((1<<s) - 1));
    
    for (int i = 0; i < E; i++)
    {
       
        if (cache[Cindex + i].availability)
        {
            
            if (cache[Cindex + i].line_label == (address>>b))
            {
                cache[Cindex + i].time = t;
                hits++;
                
                return;
            }
           
            if (cache[Cindex + i].time < LRU)
            {
                LRU = cache[Cindex + i].time;
                empty = i;
            }
        }
       
        else
        {
            empty = i;
            LRU = t;
            break;
        }
    }
    misses++;
    
    if (LRU != t){
        evicts ++;
        
    }
    cache[Cindex + empty].line_label = (address>>b);
    cache[Cindex + empty].availability = 1;
    cache[Cindex + empty].time = t;
    
}



int main(int argc, char *argv[])
{
    FILE *file;
    char tracebuf[100];
    unsigned long long address;
    InputVal(argc, argv);
    file = fopen(trace_file, "r");
    cache = (struct lines*)malloc(sizeof(struct lines) * E * (1<<s));
    memset(cache, 0, sizeof(struct lines) * E * (1<<s));
    while (fgets(tracebuf, 100, file) != NULL) {
       
        sscanf(tracebuf + 2, "%llx", &address);
        switch (tracebuf[1]) {
        	case '\0':
        		break;
            case 'L':
                RunSim(address);
                break;
            case 'S':
                RunSim(address);
                break;
            case 'M':
                RunSim(address);
                RunSim(address);
                break;
            default:
                break;
        }

        if (s == 0 || E == 0 || b == 0 || trace_file == NULL) 
    	{
            printf("%s: Missing required command line argument\n", argv[0]);
            printUsage(argv);
            exit(1);
        }
     
    }
   
    printSummary(hits, misses, evicts);

    fclose(file);
    free(cache);
    return 0;
}

