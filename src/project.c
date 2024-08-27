#include "project.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void addNation(Country** countries, unsigned int* numCountries, char* name) {
    for (unsigned int i = 0; i < *numCountries; i++) {
        if(strcmp(name, (*countries)[i].name) == 0) {
            printf("Nation \"%s\" already in the database\n", name);
            return;
        }
    }

    // reallocate memory for new country
    *countries = (Country*)realloc(*countries, (*numCountries + 1) *sizeof(Country));

    // allocate memory for name of country
    (*countries)[*numCountries].name = (char*)malloc(strlen(name) + 1);

    //initialize details for a country
    strcpy((*countries)[*numCountries].name, name);
    (*countries)[*numCountries].gold = 0;
    (*countries)[*numCountries].silver = 0;
    (*countries)[*numCountries].bronze = 0;
    (*numCountries)++;
    printf("SUCCESS\n");
}

void addMedals(Country** countries, unsigned int* numCountries, char* name, int gold, int silver, int bronze) {
    int index = -1;
    for (unsigned int i = 0; i < *numCountries; i++) {
        if (strcmp(name, (*countries)[i].name) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Nation \"%s\" is not in the database\n", name);
        return;
    }

    int num1 = (*countries)[index].gold + gold;
    int num2 = (*countries)[index].silver + silver;
    int num3 = (*countries)[index].bronze + bronze;

    //handle corner case where medals become minus
    if (num1 < 0) {
        (*countries)[index].gold = 0;
    }
    else {
        (*countries)[index].gold += gold;
    }
    if (num2 < 0) {
        (*countries)[index].silver = 0;
    }
    else {
        (*countries)[index].silver += silver;
    }
    if (num3 < 0) {
        (*countries)[index].bronze = 0;
    }
    else {
        (*countries)[index].bronze += bronze;
    }
    printf("SUCCESS\n");
}

int compareCountries(const void *a, const void *b) {
    const Country *countryA = (const Country *)a;
    const Country *countryB = (const Country *)b;

    if (countryA->gold != countryB->gold) {
        return countryB->gold - countryA->gold;
    }
    if (countryA->silver != countryB->silver) {
        return countryB->silver - countryA->silver;
    }

    return countryB->bronze - countryA->bronze;
}



void printDatabase(Country* countries, unsigned int numCountries) {
    // using qsort to sort countries by medals
    qsort(countries, numCountries, sizeof(Country), compareCountries);

    for (unsigned int i = 0; i < numCountries; i++) {
        printf("%s %d %d %d\n", countries[i].name, countries[i].gold, countries[i].silver, countries[i].bronze);
    }
    printf("SUCCESS\n");
}

void saveToFile(Country* countries, unsigned int numCountries, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return;        
    }
    for (unsigned int i = 0; i < numCountries; i++) {
        if (fprintf(file, "%s %d %d %d\n", countries[i].name, countries[i].gold, countries[i].silver, countries[i].bronze) < 0) {
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("SUCCESS\n");
}

void loadFromFile(Country** countries, unsigned int *numCountries, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    Country* newCountries = NULL;
    size_t count = 0;
    char line[1000];

    while (fgets(line, 1000, file) != NULL) {
        newCountries = realloc(newCountries, (count + 1) * sizeof(Country));
        if (newCountries == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            return;
        }

        size_t nameLength = strcspn(line, " "); 

        newCountries[count].name = malloc((nameLength + 1) * sizeof(char)); 
        if (newCountries[count].name == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            free(newCountries);
            return;
        }

        strncpy(newCountries[count].name, line, nameLength);
        newCountries[count].name[nameLength] = '\0'; 

        // handle error case for taking in medals
        if (sscanf(line + nameLength, "%d %d %d", &newCountries[count].gold, &newCountries[count].silver, &newCountries[count].bronze) != 3) {
            printf("Error reading from file\n");
            fclose(file);
            free(newCountries[count].name); 
            free(newCountries);
            return;
        }
        count++;
    }

    // free memory for the old countries
    for (unsigned int i =0; i < *numCountries; i++) {
        free((*countries)[i].name);
    }
    free(*countries);

    *numCountries = count;
    // allocate memory in countries for newCountries
    *countries = malloc(count * sizeof(Country));
    if (*countries == NULL) {
        printf("Memory allocation failed\n");
        free(newCountries);
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        // allocate memory for name in new countries
        (*countries)[i].name = malloc(strlen(newCountries[i].name) + 1); 
        if ((*countries)[i].name == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            for (size_t j = 0; j <= i; ++j) free((*countries)[j].name);
            free(*countries);
            free(newCountries[i].name);
            free(newCountries);
            return;
        }
        // copy details from newCountries to countries
        strcpy((*countries)[i].name, newCountries[i].name);
        (*countries)[i].gold = newCountries[i].gold;
        (*countries)[i].silver = newCountries[i].silver;
        (*countries)[i].bronze = newCountries[i].bronze;
        free(newCountries[i].name); 
    }
    free(newCountries);
    fclose(file);
    printf("SUCCESS\n");
}


void quitProgram(Country** countries, unsigned int *numCountries) {
    for (unsigned int i = 0; i < *numCountries; i ++) {
        free((*countries)[i].name); //free name for countries
    }
    free(*countries);   //free countries
    printf("SUCCESS\n");
    exit(0);
}

int main() {
    Country* countries = NULL;
    unsigned int numCountries = 0;

    char command;
    char name[100];
    char input[1000]; 
    signed int gold, silver, bronze;
    char filename[100];

       while (1) {
        fgets(input, sizeof(input), stdin);

        sscanf(input, " %c", &command);

        switch (command) {
            case 'A': {
                int result = sscanf(input, " %c %s", &command, name);
                if (result != 2) {
                    printf("Invalid command format. 'A' command should be followed by exactly one argument.\n");
                    break;
                }
                addNation(&countries, &numCountries, name);
                break;
            }
            case 'M': {
                int result = sscanf(input, " %c %s %d %d %d", &command, name, &gold, &silver, &bronze);
                if (result != 5) {
                    printf("Invalid command format. 'M' command should be followed by exactly four arguments.\n");
                    break;
                }
                addMedals(&countries, &numCountries, name, gold, silver, bronze);
                break;
            }
            case 'L':
                printDatabase(countries, numCountries);
                break;
            case 'W': {
                int result = sscanf(input, " %c %s", &command, filename);
                if (result != 2) {
                    printf("Invalid command format. 'W' command should be followed by exactly one argument.\n");
                    break;
                }
                saveToFile(countries, numCountries, filename);
                break;
            }
            case 'O': {
                int result = sscanf(input, " %c %s", &command, filename);
                if (result != 2) {
                    printf("Invalid command format. 'O' command should be followed by exactly one argument.\n");
                    break;
                }
                loadFromFile(&countries, &numCountries, filename);
                break;
            }
            case 'Q':
                quitProgram(&countries, &numCountries);
                return 0; 
            default:
                printf("Invalid command\n");
                break;
        }
    }
    return 0; 
}
