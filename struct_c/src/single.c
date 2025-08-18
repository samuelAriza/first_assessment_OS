#include "../include/benchmark.h"
#include "../include/generator.h"
#include "../include/queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* argval(int argc, char** argv, const char* key){
    size_t len = strlen(key);
    for(int i=1;i<argc;i++){ if(strncmp(argv[i], key, len)==0) return argv[i]+len; }
    return NULL;
}

int main(int argc, char** argv){
    const char* func = argval(argc, argv, "--func=");
    const char* mode = argval(argc, argv, "--mode="); // ptr|val
    const char* narg = argval(argc, argv, "--n=");
    if(!func || !mode || !narg){
        fprintf(stderr, "Usage: %s --func=<name> --mode=ptr|val --n=<size>\n", argv[0]);
        return 2;
    }

    size_t n = (size_t)strtoull(narg, NULL, 10);
    Person* persons = generatePersons(n);
    if(!persons){
        fprintf(stderr, "generatePersons failed for n=%zu\n", n);
        return 1;
    }

    size_t rss_before = memory_rss_kb();
    size_t heap_before = memory_heap_kb();
    double wall_start = now_ms();
    double cpu_start = cpu_now_ms();

    // Dispatch
    if(strcmp(func, "findOldest")==0){
        if(strcmp(mode, "ptr")==0) (void)findOldest_ptr(persons, n);
        else (void)findOldest_val(persons, n);
    } else if(strcmp(func, "findOldestByCity")==0){
        size_t c=0; if(strcmp(mode, "ptr")==0){ const Person** r = findOldestByCity_ptr(persons, n, &c); free((void*)r);} else { Person* r = findOldestByCity_val(persons, n, &c); free(r);}    
    } else if(strcmp(func, "findRichest")==0){
        if(strcmp(mode, "ptr")==0) (void)findRichest_ptr(persons, n); else (void)findRichest_val(persons, n);
    } else if(strcmp(func, "findRichestByCity")==0){
        size_t c=0; if(strcmp(mode, "ptr")==0){ const Person** r = findRichestByCity_ptr(persons, n, &c); free((void*)r);} else { Person* r = findRichestByCity_val(persons, n, &c); free(r);}    
    } else if(strcmp(func, "findRichestByGroup")==0){
        if(strcmp(mode, "ptr")==0) (void)findRichestByGroup_ptr(persons, n, 'A'); else (void)findRichestByGroup_val(persons, n, 'A');
    } else if(strcmp(func, "listByGroup")==0){
        size_t c=0; if(strcmp(mode, "ptr")==0){ const Person** r = listByGroup_ptr(persons, n, 'A', &c); free((void*)r);} else { Person* r = listByGroup_val(persons, n, 'A', &c); free(r);}    
    } else if(strcmp(func, "countByGroup")==0){
        if(strcmp(mode, "ptr")==0) (void)countByGroup_ptr(persons, n, 'A'); else (void)countByGroup_val(persons, n, 'A');
    } else if(strcmp(func, "cityWithHighestAvgHeritage")==0){
        if(strcmp(mode, "ptr")==0){ const char* s = cityWithHighestAvgHeritage_ptr(persons, n); free((void*)s);} else { const char* s = cityWithHighestAvgHeritage_val(persons, n); free((void*)s);}    
    } else if(strcmp(func, "percentageOlderThanByGroup")==0){
        if(strcmp(mode, "ptr")==0) (void)percentageOlderThanByGroup_ptr(persons, n, 65, 'A'); else (void)percentageOlderThanByGroup_val(persons, n, 65, 'A');
    } else if(strcmp(func, "netWealthByCity")==0){
        size_t c=0; if(strcmp(mode, "ptr")==0){ double* r = netWealthByCity_ptr(persons, n, &c); free(r);} else { double* r = netWealthByCity_val(persons, n, &c); free(r);}    
    } else if(strcmp(func, "validateTaxGroup")==0){
        if(strcmp(mode, "ptr")==0) (void)validateTaxGroup_ptr(&persons[0]); else (void)validateTaxGroup_val(persons[0]);
    } else {
        fprintf(stderr, "Unknown func: %s\n", func);
        free(persons);
        return 2;
    }

    double wall_end = now_ms();
    double cpu_end = cpu_now_ms();
    size_t rss_after = memory_rss_kb();
    size_t heap_after = memory_heap_kb();

    // CSV header-compatible with export_csv
    printf("%s,%s,%zu,%.3f,%.3f,%zu,%zu\n",
           strcmp(mode,"ptr")==0?"C (ptr)":"C (val)", func, n,
           wall_end - wall_start, cpu_end - cpu_start,
           (heap_after>heap_before)?heap_after-heap_before:0,
           (rss_after>rss_before)?rss_after-rss_before:0);

    free(persons);
    return 0;
}


