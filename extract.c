#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *data;
    size_t size;
} IrisSpecies;

typedef struct {
    IrisSpecies setosa;
    IrisSpecies versicolor;
    IrisSpecies virginica;
} IrisData;

void print_error_message(int code) {
    switch (code) {
        case 1:
            fprintf(stderr, "Erreur : problème de paramètre.\n");
            break;
        case 2:
            fprintf(stderr, "Erreur : problème de lecture du fichier.\n");
            break;
        default:
            fprintf(stderr, "Erreur inconnue.\n");
    }
}

IrisSpecies read_iris_species(FILE *file, size_t count) {
    IrisSpecies species;
    species.data = malloc(count * sizeof(float));
    if (species.data == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    species.size = count;

    size_t i;
    for (i = 0; i < count; ++i) {
        fread(&species.data[i], sizeof(float), 1, file);
    }

    return species;
}

float calculate_average(IrisSpecies species) {
    float sum = 0.0;
    size_t i;
    for (i = 0; i < species.size; ++i) {
        sum += species.data[i];
    }
    return sum / species.size;
}

float find_min(IrisSpecies species) {
    float min = species.data[0];
    size_t i;
    for (i = 1; i < species.size; ++i) {
        if (species.data[i] < min) {
            min = species.data[i];
        }
    }
    return min;
}

float find_max(IrisSpecies species) {
    float max = species.data[0];
    size_t i;
    for (i = 1; i < species.size; ++i) {
        if (species.data[i] > max) {
            max = species.data[i];
        }
    }
    return max;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_error_message(1);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        print_error_message(2);
        return 2;
    }

    IrisData irisData;
    irisData.setosa = read_iris_species(file, 50);
    irisData.versicolor = read_iris_species(file, 50);
    irisData.virginica = read_iris_species(file, 50);

    fclose(file);

    printf("Setosa - Moyenne : %.2f, Min : %.2f, Max : %.2f\n",
           calculate_average(irisData.setosa),
           find_min(irisData.setosa),
           find_max(irisData.setosa));

    printf("Versicolor - Moyenne : %.2f, Min : %.2f, Max : %.2f\n",
           calculate_average(irisData.versicolor),
           find_min(irisData.versicolor),
           find_max(irisData.versicolor));

    printf("Virginica - Moyenne : %.2f, Min : %.2f, Max : %.2f\n",
           calculate_average(irisData.virginica),
           find_min(irisData.virginica),
           find_max(irisData.virginica));

    // Libérer la mémoire allouée
    free(irisData.setosa.data);
    free(irisData.versicolor.data);
    free(irisData.virginica.data);

    return 0;
}
