// Program to generate a permutation randomly.

#include <stdio.h>
#include <stdlib.h> /*includes random number generation*/
#include <time.h>

#define SYMBOLS 5
#define POP_SIZE 1000
#define X_BIAS 0.5    // variation bias for uniform crossover
#define MUT_RATE 0.25 // Mutation Rate
#define GENERATIONS 200
//int permutation(int original_list[]);

struct individual
{
    int house[SYMBOLS];
    int drink[SYMBOLS];
    int car[SYMBOLS];
    int animal[SYMBOLS];
    int nationality[SYMBOLS];
    float fitness;
};

int *permutation(int *original_list, int *new_list);
void constraints(struct individual offspring);
void print_indiv(struct individual offspring, int index);

int main(void)
{
    int *newer_list;
    int new_list[SYMBOLS];
    int original_list[SYMBOLS];
    int len = SYMBOLS;
    int i;
    int j;
    int k;
    int gen;
    int randomnumber;
    int random_parent1_index;
    int random_parent2_index;
    int random_parent3_index;
    int mom;
    int dad;
    float best_fitness;
    float avg_fitness;
    int best_offspring;
    struct individual parent[POP_SIZE];
    struct individual offspring[POP_SIZE];
    struct individual pseudoparent[POP_SIZE];

    srand(time(NULL));

    printf("\nNumber    House     Drink        Nationality    Car         Animal\n");
    printf("--------------------------------------------------------------------\n");
    printf("   1      Red       Cocoa        Norwegian      Oldmobile   Dogs\n");
    printf("   2      Green     Eggnog       Englishman     Ford        Snails\n");
    printf("   3      Ivory     Milk         Ukranian       Chevrolet   Fox\n");
    printf("   4      Yellow    Water        Japanese       Mercedes    Horse\n");
    printf("   3      Blue      Orangejuice  Spaniard       Volkswagen  Zebra\n\n");

    for (j = 0; j < POP_SIZE; j++)
    {
        printf("Permutation for Parent %d \n", j);
        //////////
        for (i = 0; i < len; i++)
        {
            original_list[i] = i + 1;
        }

        newer_list = permutation(original_list, new_list);

        for (i = 0; i < len; i++)
        {
            parent[j].house[i] = newer_list[i];
            printf("%d ", parent[j].house[i]);
        }
        printf(" House \n");
        //Initialize original_list to 12345
        for (i = 0; i < len; i++)
        {
            original_list[i] = i + 1;
        }

        //////////
        newer_list = permutation(original_list, new_list);

        for (i = 0; i < len; i++)
        {
            parent[j].drink[i] = newer_list[i];
            printf("%d ", parent[j].drink[i]);
        }
        printf(" Drinks \n");

        //Initialize original_list to 12345
        for (i = 0; i < len; i++)
        {
            original_list[i] = i + 1;
        }

        //////////
        newer_list = permutation(original_list, new_list);

        for (i = 0; i < len; i++)
        {
            parent[j].nationality[i] = newer_list[i];
            printf("%d ", parent[j].nationality[i]);
        }
        printf(" Nationality \n");
        //Initialize original_list to 12345
        for (i = 0; i < len; i++)
        {
            original_list[i] = i + 1;
        }

        //////////
        newer_list = permutation(original_list, new_list);

        for (i = 0; i < len; i++)
        {
            parent[j].car[i] = newer_list[i];
            printf("%d ", parent[j].car[i]);
        }
        printf(" Cars \n");
        //Initialize original_list to 12345
        for (i = 0; i < len; i++)
        {
            original_list[i] = i + 1;
        }

        //////////
        newer_list = permutation(original_list, new_list);

        for (i = 0; i < len; i++)
        {
            parent[j].animal[i] = newer_list[i];
            printf("%d ", parent[j].animal[i]);
        }
        printf(" Animal \n");

        parent[j].fitness = 0.0;

        //Constraints and fitness calculation. Check ppt

        for (i = 0; i < len; i++)
        {
            //Fixed Position

            //Constraint 8  Middle House drinks milk
            if (i == 2)
            {
                if (parent[j].drink[i] == 3)
                {
                    parent[j].fitness += 100.0;
                }
            }

            //Constraint 9  Norwegian lives in the first house on the left
            if (i == 0)
            {
                if (parent[j].nationality[i] == 1)
                {
                    parent[j].fitness += 100.0;
                }
            }

            //One Sided Constraint

            //Constraint 5  Green house on the right of Ivory ( Ivory -> Green)
            if (i < 4)
            {
                if (parent[j].house[i] == 3 && parent[j].house[i + 1] == 2)
                {
                    parent[j].fitness += 25.0;
                }
            }

            //Same Column Constraints

            //Constraint 1 Enlishman lives in Red House
            if (parent[j].nationality[i] == 2 && parent[j].house[i] == 1)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 2 Spaniard owns dog
            if (parent[j].nationality[i] == 5 && parent[j].animal[i] == 1)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 3 man in Green house drinks cocoa
            if (parent[j].house[i] == 2 && parent[j].drink[i] == 1)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 4 Ukranian drinks eggnog
            if (parent[j].nationality[i] == 3 && parent[j].drink[i] == 2)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 6 Man who owns Oldsmobile also wons snails
            if (parent[j].car[i] == 1 && parent[j].animal[i] == 2)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 7 Owner of Ford lives in Yellow House
            if (parent[j].car[i] == 2 && parent[j].house[i] == 4)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 12 Owner of Merc drinks Orange Juice
            if (parent[j].car[i] == 4 && parent[j].drink[i] == 5)
            {
                parent[j].fitness += 20.0;
            }

            //Constraint 13 Japanese drives Volkswagen
            if (parent[j].nationality[i] == 4 && parent[j].car[i] == 5)
            {
                parent[j].fitness += 20.0;
            }

            //Two-Sided Constraints

            //Constraint 10 Man who owns Chevrolet lives in the house next to the man who owns a fox

            if (parent[j].animal[0] == 3 && parent[j].car[1] == 3)
            {
                parent[j].fitness += 12.5;
            }

            if (parent[j].animal[4] == 3 && parent[j].car[3] == 3)
            {
                parent[j].fitness += 12.5;
            }

            if (i < 4 && i > 0)
            {
                if ((parent[j].animal[i] == 3 && parent[j].car[i - 1] == 3) || (parent[j].animal[i] == 3 && parent[j].car[i + 1] == 3))
                {
                    parent[j].fitness += 12.5;
                }
            }

            //Constraint 11 Ford owner stays next to where horse is kept

            if (i == 0)
            {
                if (parent[j].animal[i] == 4 && parent[j].car[i + 1] == 2)
                {
                    parent[j].fitness += 12.5;
                }
            }
            if (i == 4)
            {
                if (parent[j].animal[i] == 4 && parent[j].car[i - 1] == 2)
                {
                    parent[j].fitness += 12.5;
                }
            }
            if (i < 4 && i > 0)
            {
                if ((parent[j].animal[i] == 4 && parent[j].car[i - 1] == 2) || (parent[j].animal[i] == 4 && parent[j].car[i + 1] == 2))
                {
                    parent[j].fitness += 12.5;
                }
            }

            //Constraint 14 Norwegian lives next to blue house

            if (i == 0)
            {
                if (parent[j].house[i] == 5 && parent[j].nationality[i + 1] == 1)
                {
                    parent[j].fitness += 12.5;
                }
            }
            if (i == 4)
            {
                if (parent[j].house[i] == 5 && parent[j].nationality[i - 1] == 1)
                {
                    parent[j].fitness += 12.5;
                }
            }
            if (i < 4 && i > 0)
            {
                if ((parent[j].house[i] == 5 && parent[j].nationality[i - 1] == 1) || (parent[j].house[i] == 5 && parent[j].nationality[i + 1] == 1))
                {
                    parent[j].fitness += 12.5;
                }
            }
        }

        printf("Fitness for Parent %d is %6.2f \n", j, parent[j].fitness);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////Off spring Generation
    for (gen = 0; gen < GENERATIONS; gen++)
    {
        printf("=============================================================================== \n");
        printf("                                  Generation %d                                 \n", gen + 1);
        printf("=============================================================================== \n");

        for (j = 0; j < POP_SIZE; j++)
        {

            //For mom
            random_parent1_index = rand() % POP_SIZE;
            random_parent2_index = rand() % POP_SIZE;
            random_parent3_index = rand() % POP_SIZE;

            if (parent[random_parent1_index].fitness > parent[random_parent2_index].fitness)
            {
                mom = random_parent1_index;
            }
            else
            {
                mom = random_parent2_index;
            }

            if (parent[random_parent3_index].fitness > parent[mom].fitness)
            {
                mom = random_parent3_index;
            }
            printf("Tournament Selection Round %d for mom with individuals %d , %d , %d\n", j, random_parent1_index, random_parent2_index, random_parent3_index);
            printf("Mom selected with index %d\n", mom);
            //For dad
            random_parent1_index = rand() % POP_SIZE;
            random_parent2_index = rand() % POP_SIZE;
            random_parent3_index = rand() % POP_SIZE;

            if (parent[random_parent1_index].fitness > parent[random_parent2_index].fitness)
            {
                dad = random_parent1_index;
            }
            else
            {
                dad = random_parent2_index;
            }

            if (parent[random_parent3_index].fitness > parent[mom].fitness)
            {
                dad = random_parent3_index;
            }
            printf("Tournament Selection Round %d for dad with individuals %d , %d , %d\n", j, random_parent1_index, random_parent2_index, random_parent3_index);
            printf("Dad selected with index %d\n", dad);

            //Uniform Crossover

            //Nationality

            if ((float)rand() / RAND_MAX < X_BIAS)
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].nationality[i] = parent[mom].nationality[i];
                }
            }
            else
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].nationality[i] = parent[dad].nationality[i];
                }
            }

            //House

            if ((float)rand() / RAND_MAX < X_BIAS)
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].house[i] = parent[mom].house[i];
                }
            }
            else
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].house[i] = parent[dad].house[i];
                }
            }

            //Drink

            if ((float)rand() / RAND_MAX < X_BIAS)
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].drink[i] = parent[mom].drink[i];
                }
            }
            else
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].drink[i] = parent[dad].drink[i];
                }
            }

            //car

            if ((float)rand() / RAND_MAX < X_BIAS)
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].car[i] = parent[mom].car[i];
                }
            }
            else
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].car[i] = parent[dad].car[i];
                }
            }

            //Animal

            if ((float)rand() / RAND_MAX < X_BIAS)
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].animal[i] = parent[mom].animal[i];
                }
            }
            else
            {
                for (i = 0; i < len; i++)
                {
                    offspring[j].animal[i] = parent[dad].animal[i];
                }
            }

            //Mutation for rows of the offspring
            //change : mutate each row but first check condition for each row
            if ((float)rand() / RAND_MAX < MUT_RATE)
            {

                printf("Mutation happening in house");

                newer_list = permutation(offspring[j].house, new_list);
                for (i = 0; i < len; i++)
                {
                    offspring[j].house[i] = newer_list[i];
                }
            }

            if ((float)rand() / RAND_MAX < MUT_RATE)
            {

                printf("Mutation happening in drinks");
                newer_list = permutation(offspring[j].drink, new_list);
                for (i = 0; i < len; i++)
                {
                    offspring[j].drink[i] = newer_list[i];
                }
            }
            if ((float)rand() / RAND_MAX < MUT_RATE)
            {
                printf("Mutation happening in nationality");
                newer_list = permutation(offspring[j].nationality, new_list);
                for (i = 0; i < len; i++)
                {
                    offspring[j].nationality[i] = newer_list[i];
                }
            }
            if ((float)rand() / RAND_MAX < MUT_RATE)
            {
                printf("Mutation happening in car");
                newer_list = permutation(offspring[j].car, new_list);
                for (i = 0; i < len; i++)
                {
                    offspring[j].car[i] = newer_list[i];
                }
            }

            if ((float)rand() / RAND_MAX < MUT_RATE)
            {
                printf("Mutation happening in animal");
                newer_list = permutation(offspring[j].animal, new_list);
                for (i = 0; i < len; i++)
                {
                    offspring[j].animal[i] = newer_list[i];
                }
            }

            //Print Offspring

            print_indiv(offspring[j], j);

            //crossover complete

            ///////////////////////////////////////////////////////////////////compute best fitness off offspring
            offspring[j].fitness = 0.0;

            //Constraints and fitness calculation. Check ppt

            for (i = 0; i < len; i++)
            {
                //Fixed Position

                //Constraint 8  Middle House drinks milk
                if (i == 2)
                {
                    if (offspring[j].drink[i] == 3)
                    {
                        offspring[j].fitness += 100.0;
                    }
                }

                //Constraint 9  Norwegian lives in the first house on the left
                if (i == 0)
                {
                    if (offspring[j].nationality[i] == 1)
                    {
                        offspring[j].fitness += 100.0;
                    }
                }

                //One Sided Constraint

                //Constraint 5  Green house on the right of Ivory ( Ivory -> Green)
                if (i < 4)
                {
                    if (offspring[j].house[i] == 3 && offspring[j].house[i + 1] == 2)
                    {
                        offspring[j].fitness += 25.0;
                    }
                }

                //Same Column Constraints

                //Constraint 1 Enlishman lives in Red House
                if (offspring[j].nationality[i] == 2 && offspring[j].house[i] == 1)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 2 Spaniard owns dog
                if (offspring[j].nationality[i] == 5 && offspring[j].animal[i] == 1)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 3 man in Green house drinks cocoa
                if (offspring[j].house[i] == 2 && offspring[j].drink[i] == 1)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 4 Ukranian drinks eggnog
                if (offspring[j].nationality[i] == 3 && offspring[j].drink[i] == 2)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 6 Man who owns Oldsmobile also wons snails
                if (offspring[j].car[i] == 1 && offspring[j].animal[i] == 2)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 7 Owner of Ford lives in Yellow House
                if (offspring[j].car[i] == 2 && offspring[j].house[i] == 4)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 12 Owner of Merc drinks Orange Juice
                if (offspring[j].car[i] == 4 && offspring[j].drink[i] == 5)
                {
                    offspring[j].fitness += 20.0;
                }

                //Constraint 13 Japanese drives Volkswagen
                if (offspring[j].nationality[i] == 4 && offspring[j].car[i] == 5)
                {
                    offspring[j].fitness += 20.0;
                }

                //Two-Sided Constraints

                //Constraint 10 Man who owns Chevrolet lives in the house next to the man who owns a fox

                if (i == 0)
                {
                    if (offspring[j].animal[i] == 3 && offspring[j].car[i + 1] == 3)
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
                if (i == 4)
                {
                    if (offspring[j].animal[i] == 3 && offspring[j].car[i - 1] == 3)
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
                if (i < 4 && i > 0)
                {
                    if ((offspring[j].animal[i] == 3 && offspring[j].car[i - 1] == 3) || (offspring[j].animal[i] == 3 && offspring[j].car[i + 1] == 3))
                    {
                        offspring[j].fitness += 12.5;
                    }
                }

                //Constraint 11 Ford owner stays next to where horse is kept

                if (i == 0)
                {
                    if (offspring[j].animal[i] == 4 && offspring[j].car[i + 1] == 2)
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
                if (i == 4)
                {
                    if (offspring[j].animal[i] == 4 && offspring[j].car[i - 1] == 2)
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
                if (i < 4 && i > 0)
                {
                    if ((offspring[j].animal[i] == 4 && offspring[j].car[i - 1] == 2) || (offspring[j].animal[i] == 4 && offspring[j].car[i + 1] == 2))
                    {
                        offspring[j].fitness += 12.5;
                    }
                }

                //Constraint 14 Norwegian lives next to blue house

                if (i == 0)
                {
                    if (offspring[j].house[i] == 5 && offspring[j].nationality[i + 1] == 1)
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
                if (i == 4)
                {
                    if (offspring[j].house[i] == 5 && offspring[j].nationality[i - 1] == 1)
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
                if (i < 4 && i > 0)
                {
                    if ((offspring[j].house[i] == 5 && offspring[j].nationality[i - 1] == 1) || (offspring[j].house[i] == 5 && offspring[j].nationality[i + 1] == 1))
                    {
                        offspring[j].fitness += 12.5;
                    }
                }
            }

            printf("Fitness for Offspring %d is %6.2f \n", j, offspring[j].fitness);
        }
        printf(" \n");
        for (j = 0; j < POP_SIZE; j++)
        {
            if (j == 0)
            {
                best_fitness = offspring[j].fitness;
                best_offspring = j;
            }
            else
            {
                if (offspring[j].fitness > best_fitness)
                {
                    best_fitness = offspring[j].fitness;
                    best_offspring = j;
                }
            }

            //printf("Fitness of Offspring %d is %6.2f \n", j, offspring[j].fitness);
        }
        printf("\n");

        //if (best_fitness > 420)
        //{

        //    printf("HIGHEST achieved Fitness of generation %d is of  offspring %d with value of %6.2f \n", gen + 1, best_offspring, best_fitness);
        //    print_indiv(offspring[best_offspring], best_offspring);
        //    constraints(offspring[best_offspring]);
        //    //break;
        //}
        //else if (best_fitness < 100)
        //{
        //    printf("Fitness less than 100 of generation %d is of  offspring %d with value of %6.2f \n", gen + 1, best_offspring, best_fitness);
        //    print_indiv(offspring[best_offspring], best_offspring);
        //    constraints(offspring[best_offspring]);
        //    printf("Stop Program");
        //break;
        //}

        printf("BEST Fitness of generation %d is of offspring %d  with value of %6.2f \n", gen + 1, best_offspring, best_fitness);
        print_indiv(offspring[best_offspring], best_offspring);

        //assign offspring values as parent
        for (j = 0; j < POP_SIZE; j++)
        {
            for (i = 0; i < len; i++)
            {
                parent[j].house[i] = offspring[j].house[i];
                parent[j].drink[i] = offspring[j].drink[i];
                parent[j].nationality[i] = offspring[j].nationality[i];
                parent[j].car[i] = offspring[j].car[i];
                parent[j].animal[i] = offspring[j].animal[i];
            }
        }
    }
    return 0;
}

int *permutation(int *original_list, int *new_list)
{
    int number; //index for individuals+
    int i;
    int c;
    int len;
    int newsize;

    len = SYMBOLS;
    newsize = SYMBOLS;

    for (i = 0; i < len; i++)
    {
        number = rand() % newsize;

        new_list[i] = original_list[number];

        for (c = number; c < len - 1; c++)
        {
            original_list[c] = original_list[c + 1];
        }

        newsize--;
    }

    return new_list;
}

void constraints(struct individual offspring)
{
    int i;
    int len = SYMBOLS;
    for (i = 0; i < len; i++)
    {
        //Fixed Position

        //Constraint 8  Middle House drinks milk
        if (i == 2)
        {
            if (offspring.drink[i] == 3)
            {
                printf("Constraint 8  Middle House drinks milk  Satisfied \n");
            }
        }

        //Constraint 9  Norwegian lives in the first house on the left
        if (i == 0)
        {
            if (offspring.nationality[i] == 1)
            {
                printf("Constraint 9  Norwegian lives in the first house on the left  Satisfied \n");
            }
        }

        //One Sided Constraint

        //Constraint 5  Green house on the right of Ivory ( Ivory -> Green)
        if (i < 4)
        {
            if (offspring.house[i] == 3 && offspring.house[i + 1] == 2)
            {
                printf("Constraint 5  Green house on the right of Ivory  Satisfied \n");
            }
        }

        //Same Column Constraints

        //Constraint 1 Enlishman lives in Red House
        if (offspring.nationality[i] == 2 && offspring.house[i] == 1)
        {
            printf("Constraint 1 Enlishman lives in Red House  Satisfied \n");
        }

        //Constraint 2 Spaniard owns dog
        if (offspring.nationality[i] == 5 && offspring.animal[i] == 1)
        {
            printf("Constraint 2 Spaniard owns dog  Satisfied \n");
        }

        //Constraint 3 man in Green house drinks cocoa
        if (offspring.house[i] == 2 && offspring.drink[i] == 1)
        {
            printf("Constraint 3 man in Green house drinks cocoa  Satisfied \n");
        }

        //Constraint 4 Ukranian drinks eggnog
        if (offspring.nationality[i] == 3 && offspring.drink[i] == 2)
        {
            printf("Constraint 4 Ukranian drinks eggnog  Satisfied \n");
        }

        //Constraint 6 Man who owns Oldsmobile also wons snails
        if (offspring.car[i] == 1 && offspring.animal[i] == 2)
        {
            printf("Constraint 6 Man who owns Oldsmobile also wons snails  Satisfied \n");
        }

        //Constraint 7 Owner of Ford lives in Yellow House
        if (offspring.car[i] == 2 && offspring.house[i] == 4)
        {
            printf("Constraint 7 Owner of Ford lives in Yellow House  Satisfied \n");
        }

        //Constraint 12 Owner of Merc drinks Orange Juice
        if (offspring.car[i] == 4 && offspring.drink[i] == 5)
        {
            printf("Constraint 12 Owner of Merc drinks Orange Juice  Satisfied \n");
        }

        //Constraint 13 Japanese drives Volkswagen
        if (offspring.nationality[i] == 4 && offspring.car[i] == 5)
        {
            printf("Constraint 13 Japanese drives Volkswagen  Satisfied \n");
        }

        //Two-Sided Constraints

        //Constraint 10 Man who owns Chevrolet lives in the house next to the man who owns a fox

        if (i == 0)
        {
            if (offspring.animal[i] == 3 && offspring.car[i + 1] == 3)
            {
                printf("Constraint 10 Man who owns Chevrolet lives in the house next to the man who owns a fox  Satisfied \n");
            }
        }
        if (i == 4)
        {
            if (offspring.animal[i] == 3 && offspring.car[i - 1] == 3)
            {
                printf("Constraint 10 Man who owns Chevrolet lives in the house next to the man who owns a fox  Satisfied \n");
            }
        }
        if (i < 4 && i > 0)
        {
            if ((offspring.animal[i] == 3 && offspring.car[i - 1] == 3) || (offspring.animal[i] == 3 && offspring.car[i + 1] == 3))
            {
                printf("Constraint 10 Man who owns Chevrolet lives in the house next to the man who owns a fox  Satisfied \n");
            }
        }

        //Constraint 11 Ford owner stays next to where horse is kept

        if (i == 0)
        {
            if (offspring.animal[i] == 4 && offspring.car[i + 1] == 2)
            {
                printf("Constraint 11 Ford owner stays next to where horse is kept  Satisfied \n");
            }
        }
        if (i == 4)
        {
            if (offspring.animal[i] == 4 && offspring.car[i - 1] == 2)
            {
                printf("Constraint 11 Ford owner stays next to where horse is kept  Satisfied \n");
            }
        }
        if (i < 4 && i > 0)
        {
            if ((offspring.animal[i] == 4 && offspring.car[i - 1] == 2) || (offspring.animal[i] == 4 && offspring.car[i + 1] == 2))
            {
                printf("Constraint 11 Ford owner stays next to where horse is kept  Satisfied \n");
            }
        }

        //Constraint 14 Norwegian lives next to blue house

        if (i == 0)
        {
            if (offspring.house[i] == 5 && offspring.nationality[i + 1] == 1)
            {
                printf("Constraint 14 Norwegian lives next to blue house  Satisfied \n");
            }
        }
        if (i == 4)
        {
            if (offspring.house[i] == 5 && offspring.nationality[i - 1] == 1)
            {
                printf("Constraint 14 Norwegian lives next to blue house  Satisfied \n");
            }
        }
        if (i < 4 && i > 0)
        {
            if ((offspring.house[i] == 5 && offspring.nationality[i - 1] == 1) || (offspring.house[i] == 5 && offspring.nationality[i + 1] == 1))
            {
                printf("Constraint 14 Norwegian lives next to blue house  Satisfied \n");
            }
        }
    }
}

void print_indiv(struct individual offspring, int index)
{
    int i;
    int len = SYMBOLS;
    printf("\nOffspring %d \n \n", index);
    for (i = 0; i < len; i++)
    {
        printf("%d ", offspring.house[i]);
    }
    printf(" House \n");
    for (i = 0; i < len; i++)
    {
        printf("%d ", offspring.drink[i]);
    }
    printf(" Drink \n");
    for (i = 0; i < len; i++)
    {
        printf("%d ", offspring.nationality[i]);
    }
    printf(" Nationality \n");
    for (i = 0; i < len; i++)
    {
        printf("%d ", offspring.car[i]);
    }
    printf(" Car \n");
    for (i = 0; i < len; i++)
    {
        printf("%d ", offspring.animal[i]);
    }
    printf(" Animal \n");
}