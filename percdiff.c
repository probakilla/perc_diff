#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>

typedef struct {
    double ref;
    double test;
} values;

values* new_values(double ref, double test) {
    values* ret = (values*) malloc(sizeof(values));
    ret->ref = ref;
    ret->test = test;
    return ret;
}

values* ask_user_input(void) {
    double ref, test;
    printf("Please select a reference value: \n");
    scanf("%lf", &ref);
    printf("Please select a test value: \n");
    scanf("%lf", &test);
    return new_values(ref, test);
}

regex_t get_regex(void) {
    regex_t regex;
    int reti = regcomp(&regex, "^.*[0-9],.*[0-9]$", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }
    return regex;
}

values* convert_user_input(char* user_input) {
    char* token = strtok(user_input, ",");
    values* vals = (values*) malloc(sizeof(values));
    vals->ref = atof(token);
    token = strtok(NULL, ",");
    vals->test = atof(token);
    return vals;    
}

values* validate_input(char* user_input) {
    regex_t regex = get_regex();
    int reti = regexec(&regex, user_input, 0, NULL, 0);
    values* vals = NULL;
    if (!reti) {
        vals = convert_user_input(user_input);
    } else if (reti == REG_NOMATCH) {
        char* error_msg =  "\033[31mERROR\033[0m Parameter arn't correct\n";
        char* msg = "Expected format: 123,456\nActual arguments: %s\n";
        fprintf(stderr, error_msg);
        fprintf(stderr, msg, user_input);
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "Regex match failed\n");
        exit(EXIT_FAILURE);
    }
    return vals;
}

double get_difference(values* vals) {
    double diff = ((vals->test - vals->ref) / vals->ref) * 100;
    return diff;
}

char* ftos(double value) {
    char* arr = (char*) malloc(sizeof(double));
    sprintf(arr, "%.2lf", value);
    return arr;
}

char* prepend_plus(double result) {
    char* str_res = ftos(result);
    printf("%s\n", str_res);
    size_t len = strlen(str_res);
    char* formatted_res = (char*) malloc(len + 2);
    formatted_res[0] = '+';
    strcpy(formatted_res + 1, str_res);
    formatted_res[len + 1] = '\0';
    free(str_res);
    return formatted_res;
}

char* append_percent(char* string) {
    size_t len = strlen(string);
    char* formatted_res = (char*) malloc(len + 2);
    strcpy(formatted_res, string);
    formatted_res[len] = '%';
    formatted_res[len + 1] = '\0';
    free(string);
    return formatted_res;
}

char* format_result(double result) {
    char* str_result = NULL;
    if (result >= 0) {
        str_result = prepend_plus(result);
    } else {
        str_result = ftos(result);
    }
    return append_percent(str_result);
}

char* check_input(char* input) {
    values* vals = NULL;
    if (input[0] != '\0') {
        vals = validate_input(input);
    } else {
        vals = ask_user_input();
    }
    double res = get_difference(vals);
    free(vals);
    char* test = format_result(res);
    return test;
}
