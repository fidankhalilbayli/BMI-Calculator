#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct person{
    int personID;
    double height;
    double weight;
    double BMI;
};

void read_from_text_file(struct person* read_list, int N);

struct person* sort_M(struct person* read_list,double Treshold, int M,int N);
void write_into_text_file(struct person*read_list_M, int M,double treshold);


void read_from_text_file(struct person* read_list, int N){
    FILE* text_file = fopen("./height_weight.txt", "r");
    int a,b, c;
    int number = 0;
    char* person_id1;
    char* height1;
    char* weight1;
    fscanf(text_file, "%s %s %s", &person_id1, &height1, &weight1);
    while(N--){
        fscanf(text_file, "%d %d %d", &a, &b, &c);
        struct person Person;
        Person.personID = a;
        Person.height =  (double)b;
        Person.weight = (double) c;
        double bmi =  (double)c / (((double)b/100)*((double)b/100));
        Person.BMI = bmi;
        read_list[number] = Person;
        number++;
        if(feof(text_file)){
            break;
        }
    }
    fclose(text_file);
}


struct person* sort_M(struct person* read_list,double Treshold, int M,int N){
    struct person* read_list_M = (struct person*) malloc(M * sizeof(struct person));
    int i,j,a,b;
    for(a = 0; a < N; a++){
        for(b = 1; b < N - a; b++){
            if(fabs(read_list[b-1].BMI - Treshold) <= fabs(read_list[b].BMI - Treshold)){
                struct person hold;
                hold = read_list[b-1];
                read_list[b-1] = read_list[b];
                read_list[b] = hold;
            }
        }
    }

    for(i = 0; i < M; i++){
        read_list_M[i] = read_list[i];
    }
 
    for(i = 0; i < M; i++){
        for(j = 1; j < M - i; j++){
            if(fabs(read_list_M[j-1].BMI - Treshold) <= fabs(read_list_M[j].BMI - Treshold)){
                struct person hold;
                hold = read_list_M[j-1];
                read_list_M[j-1] = read_list_M[j];
                read_list_M[j] = hold;
            }
        }
    }  
    return read_list_M;
}

void write_into_text_file(struct person*read_list_M, int M,double treshold){
    FILE* text_file = fopen("output.txt", "w");
    int i;
    fprintf(text_file, "\nPerson_id  Height(cm)  Weight(kg)  BMI   |BMI-Threshold| \n");
    for(i = 0; i < M; i++){
 fprintf(text_file, "%9d  %10.0f  %10.0f  %5.2f           %5.2f\n",read_list_M[i].personID,read_list_M[i].height,read_list_M[i].weight,read_list_M[i].BMI,
 fabs(read_list_M[i].BMI-treshold));
    }
}

int main(int argc, char** argv){
    if(argc == 4){
        int n;
        int m;
        double treshold;
        sscanf(argv[1], "%d", &n);
        sscanf(argv[2], "%d", &m);
        sscanf(argv[3], "%lf", &treshold);
        
        struct person* list = (struct person*) malloc(n * sizeof(struct person));
        struct person* M;
        read_from_text_file(list, n);
        
        M = sort_M(list,treshold,m,n);
        write_into_text_file(M, m,treshold);
        free(list);
        free(M);
}
else{
        printf("Please try again");}
    return 0;
};
