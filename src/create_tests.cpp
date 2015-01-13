/*
 * Reads a input file in FASTA format and creates tests in /tests/ folder 
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const char usage[] = "Create test files from FASTA file\n"
                     "./create_tests <path_to_fasta_file>";

char buffer[256];
char filename[256];

int main(int argc, char** argv) {
    if (argc != 2) {
        puts(usage);
        exit(1);
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output = NULL;

    int test_id = 0;

    while (fgets(buffer, sizeof buffer, input)) {
        if (*buffer == '>') {
            if (output) {
                fclose(output);
            } 
            memset(filename, 0, sizeof filename);
            sprintf(filename, "../tests/test.%d.in", test_id);
            ++ test_id;

            output = fopen(filename, "w");
        } else {
            if (output) {
                buffer[strlen(buffer) - 1] = 0;
                fprintf(output, "%s", buffer);
            }
        }

        memset(buffer, 0, sizeof buffer);
    }

    if (output) {        
        fclose(output);
    }
    fclose(input);
    return 0;
}
