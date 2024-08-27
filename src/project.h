#ifndef _PROJECT__H_
#define _PROJECT__H_

typedef struct {
    char *name;
    unsigned int gold;
    unsigned int silver;
    unsigned int bronze;
} Country;

void addNation(Country** countries, unsigned int *numCountries, char* name);
void addMedals(Country** countries, unsigned int *numCountries, char* name, int gold, int silver, int bronze);
void printDatabase(Country* countries, unsigned int numCountries);
void saveToFile(Country* countries, unsigned int numCountries, const char* filename);
void loadFromFile(Country** countries, unsigned int *numCountries, const char *filename);
void quitProgram(Country** countries, unsigned int *numCountries);

#endif //! _PROJECT__H_


