#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SAMPLES 12U
#define EXIT_INVALID_INPUT 2

static int parse_samples(int argc, char **argv, int *values, size_t capacity, size_t *out_count){
    size_t count = 0U;
    
    if(argv == NULL || values == NULL || out_count == NULL){
        return 0;
    }
    
    *out_count = 0U;
    
    if(argc < 2 || (size_t)(argc - 1) > capacity){
        return 0;
    }
    
    for(size_t i = 1U; i < (size_t)argc; i ++){
        char *end = NULL;
        long parsed;
        
        errno = 0;
        parsed = strtol(argv[i], &end, 10);
        
        if(errno == ERANGE || end == argv[i] || *end != '\0' || parsed < INT_MIN || parsed > INT_MAX){
            return 0;
        }
        
        values[count] = (int)parsed;
        count++;
    }
    
    if(count == 0U){
        return 0;
    }
    
    *out_count = count;
    return 1;
}

static int summarize_samples(const int *values, size_t count, int *out_minimum, int *out_maximum, long long *out_total){
    int minimum;    
    int maximum;
    long long total = 0;
    
    if(values == NULL || count == 0 || out_minimum == NULL || out_maximum == NULL || out_total == NULL){
        return 0;
    }
    
    minimum = values[0];
    maximum = values[0];
    
    for(size_t i = 0U; i < count; i++){
        const int current = values[i];
        
        total += current;
        
        if(current < minimum){
            minimum = current;
        }
        if(current > maximum){
            maximum = current;
        }
    }
    
    *out_minimum = minimum;
    *out_maximum = maximum;
    *out_total = total;
    return 1;
}

static double mean_of(long long total, size_t count){
    return (double)total / (double)count;
}

static void print_summary(size_t count, int minimum, int maximum, double mean){
    printf("OK count=%zu min=%d max=%d mean=%.2f\n", count, minimum, maximum, mean);
}

int main(int argc, char **argv){
    int samples[MAX_SAMPLES]; 
    size_t samples_count = 0U;
    int minimum = 0;
    int maximum = 0;
    long long total = 0;
    
    if(!parse_samples(argc, argv, samples, MAX_SAMPLES, &samples_count) || !summarize_samples(samples, samples_count, &minimum, &maximum, &total)){
        fputs("ERROR invalid input\n", stderr);
        return EXIT_INVALID_INPUT;
    }
    
    print_summary(samples_count, minimum, maximum, mean_of(total, samples_count));
    return EXIT_SUCCESS;
}