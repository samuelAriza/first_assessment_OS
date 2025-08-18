#include "../include/benchmark.h"
#include "../include/generador.h"
#include "../include/queries_class.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

static const char* argval(int argc, char** argv, const char* key){
    size_t len = std::strlen(key);
    for(int i=1;i<argc;i++){ if(std::strncmp(argv[i], key, len)==0) return argv[i]+len; }
    return nullptr;
}

int main(int argc, char** argv){
    const char* func = argval(argc, argv, "--func=");
    const char* mode = argval(argc, argv, "--mode="); // ptr|val
    const char* narg = argval(argc, argv, "--n=");
    if(!func || !mode || !narg){
        std::fprintf(stderr, "Usage: %s --func=<name> --mode=ptr|val --n=<size>\n", argv[0]);
        return 2;
    }

    size_t n = (size_t)std::strtoull(narg, nullptr, 10);
    std::vector<Persona> persons = generarColeccion((int)n);
    if(persons.empty()){
        std::fprintf(stderr, "generarColeccion failed for n=%zu\n", n);
        return 1;
    }

    size_t rss_before = memory_rss_kb();
    size_t heap_before = memory_heap_kb();
    double wall_start = now_ms();
    double cpu_start = cpu_now_ms();

    if(std::strcmp(func, "findOldest")==0){
        if(std::strcmp(mode, "ptr")==0) (void)findOldest_ptr(persons.data(), persons.size());
        else (void)findOldest_val(persons.data(), persons.size());
    } else if(std::strcmp(func, "findOldestByCity")==0){
        size_t c=0; if(std::strcmp(mode, "ptr")==0){ const Persona** r = findOldestByCity_ptr(persons.data(), persons.size(), &c); delete[] r;} else { Persona* r = findOldestByCity_val(persons.data(), persons.size(), &c); delete[] r;}
    } else if(std::strcmp(func, "findRichest")==0){
        if(std::strcmp(mode, "ptr")==0) (void)findRichest_ptr(persons.data(), persons.size()); else (void)findRichest_val(persons.data(), persons.size());
    } else if(std::strcmp(func, "findRichestByCity")==0){
        size_t c=0; if(std::strcmp(mode, "ptr")==0){ const Persona** r = findRichestByCity_ptr(persons.data(), persons.size(), &c); delete[] r;} else { Persona* r = findRichestByCity_val(persons.data(), persons.size(), &c); delete[] r;}
    } else if(std::strcmp(func, "findRichestByGroup")==0){
        if(std::strcmp(mode, "ptr")==0) (void)findRichestByGroup_ptr(persons.data(), persons.size(), 'A'); else (void)findRichestByGroup_val(persons.data(), persons.size(), 'A');
    } else if(std::strcmp(func, "listTaxGroup")==0){
        size_t c=0; if(std::strcmp(mode, "ptr")==0){ const Persona** r = listTaxGroup_ptr(persons.data(), persons.size(), 'A', &c); delete[] r;} else { Persona* r = listTaxGroup_val(persons.data(), persons.size(), 'A', &c); delete[] r;}
    } else if(std::strcmp(func, "countTaxGroup")==0){
        if(std::strcmp(mode, "ptr")==0) (void)countTaxGroup_ptr(persons.data(), persons.size(), 'A'); else (void)countTaxGroup_val(persons.data(), persons.size(), 'A');
    } else if(std::strcmp(func, "cityWithHighestAvgHeritage")==0){
        if(std::strcmp(mode, "ptr")==0){ const char* s = cityWithHighestAvgHeritage_ptr(persons.data(), persons.size()); delete[] s;} else { const char* s = cityWithHighestAvgHeritage_val(persons.data(), persons.size()); delete[] s;}
    } else if(std::strcmp(func, "percentageOlderThanByGroup")==0){
        if(std::strcmp(mode, "ptr")==0) (void)percentageOlderThanByGroup_ptr(persons.data(), persons.size(), 65, 'A'); else (void)percentageOlderThanByGroup_val(persons.data(), persons.size(), 65, 'A');
    } else if(std::strcmp(func, "netWealthByCity")==0){
        size_t c=0; if(std::strcmp(mode, "ptr")==0){ double* r = netWealthByCity_ptr(persons.data(), persons.size(), &c); delete[] r;} else { double* r = netWealthByCity_val(persons.data(), persons.size(), &c); delete[] r;}
    } else if(std::strcmp(func, "validateTaxGroup")==0){
        if(std::strcmp(mode, "ptr")==0) (void)validateTaxGroup_ptr(&persons[0]); else (void)validateTaxGroup_val(persons[0]);
    } else {
        std::fprintf(stderr, "Unknown func: %s\n", func);
        return 2;
    }

    double wall_end = now_ms();
    double cpu_end = cpu_now_ms();
    size_t rss_after = memory_rss_kb();
    size_t heap_after = memory_heap_kb();

    std::printf("%s,%s,%zu,%.3f,%.3f,%zu,%zu\n",
           std::strcmp(mode,"ptr")==0?"C++ (ptr)":"C++ (val)", func, n,
           wall_end - wall_start, cpu_end - cpu_start,
           (heap_after>heap_before)?heap_after-heap_before:0,
           (rss_after>rss_before)?rss_after-rss_before:0);
    return 0;
}


