#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

pid_t pidarr[10];
int pos = 0;

struct task {
    struct task *next;
    char *process_arg;
    time_t start;
    time_t end;
};

//void add_to_list(struct task** head_ptr, char *process_arg){
//    struct task *node;
//    node = malloc(sizeof(struct task));
//    node->process_arg = process_arg;
//    node->next = *head_ptr;
//    *head_ptr = node;
//}

void push(struct task * head, char * process_arg){
    struct task * current = head;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = malloc(sizeof(struct task));
    current->next->process_arg = process_arg;
    current->next->next = NULL;
}

void excecuter(char *process_arg, struct task * head_ptr){
    push(head_ptr, process_arg);
    int pid = fork();
    pidarr[pos++] = pid;
    char * a = process_arg;
    if(pid == 0){

        char * argv_list[] = {a ,(char*)0};
        int val = execv((const char*)a ,argv_list);
        if(val == -1){
            perror("Invalid process");
            exit(2);
        }
        exit(0);
    }
}

void checker(struct task *head) {
//    while(head != NULL) {
//        printf("%s\n", head->process_arg);
//        head = head->next;
//    }
    for(int i = 0; i < pos; i++){
        head = head->next;
        printf("%s\n", head->process_arg);
        int status;
        if((waitpid(pidarr[i], &status, 0) > 0)){
            if(WIFEXITED(status) && !WEXITSTATUS(status)){
                printf("exited rc = %d\n", status);

            }else{
                printf("exited rc = 2\n");
            }
        }else{
            printf("Waitpid Problem");
        }

    }
}


int main(int argc, char **argv) {
    int counter = 0;
    struct task *head = malloc(sizeof(struct task));

    char *arr[10];
    char *base = malloc(sizeof(char)*20);
    base = "/bin/";
    int k=0;
    char *a = malloc(sizeof(char)*10);
    for(int i = 1; i < argc; i++){
        char *arg = argv[i];
        if(strcmp(arg, ".") != 0){
            strcat(a, argv[i]);
            strcat(a," ");
        }else{
            arr[k] = malloc(sizeof(char)*10);
            strcpy(arr[k++],a);
            counter++;
            strcpy(a,"");
        }
    }
    arr[k] = malloc(sizeof(char)*10);
    strcpy(arr[k++],a);
    counter++;

    for (int i = 0; i < counter; i++) {
        char *tmp = malloc(sizeof(char)*30);
        strcpy(tmp,"/bin/");

        strcat(tmp, arr[i]);
        tmp[strlen(tmp)-1] = '\0';
        excecuter(tmp, head);
    }

    checker(head);

    return 0;
}
