#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definindo as estruturas;


typedef struct{
    int identificador;
    char *nome; // ponteiro para alocar dinamicamente
    char *especialidade;
}Medico;


typedef struct{
    int identificador;
    char *identidade, *nome, *endereco, *sexo, *telefone; 
}Paciente;

typedef struct{
    int numero, identificador_medico, identificador_paciente, horario, duracao;
    char *data; // a ideia e deixar a data no formato "20 de janeiro de 2025"

}Consulta;

// funcoes para struct medico

void inserir_Medico(Medico **medico,int *pos_medico,int *capacidade_medico){

    int num;
    printf("Deseja inserir quantos medicos:\n");
    scanf("%d",&num);
    getchar();

    *capacidade_medico = (*pos_medico)+num;
    *medico=(Medico*)realloc(*medico,(*capacidade_medico)*sizeof(Medico));
    printf("Debug variaveis : capacidade_medico = %d, pos_medico = %d, num = %d\n",*capacidade_medico,*pos_medico,num);

    if(*medico == NULL){
        printf("Falha ao alocar memoria, linha 51\n");
        exit(1);
    }

    for(int i = *pos_medico;i < *capacidade_medico;i++){ 
        (*medico)[i].especialidade = (char*)malloc(50*sizeof(char));
        (*medico)[i].nome          = (char*)malloc(50*sizeof(char));
  
        printf("Digite o identificador do medico: (int)\n");
        scanf("%d",&(*medico)[i].identificador);
        getchar();

        printf("Digite o nome do medico:\n");
        fgets((*medico)[i].nome,50,stdin);
        (*medico)[i].nome[strcspn((*medico)[i].nome,"\n")]='\0';

        printf("Digite a especialidade do medico:\n");
        fgets((*medico)[i].especialidade,50,stdin);
        (*medico)[i].especialidade[strcspn((*medico)[i].especialidade,"\n")]='\0';
        
        printf("\n");
    }

    *pos_medico += num;
}

void imprimir_Medicos(Medico *medico, int pos_medico){
    
    printf("Medicos: \n\n");
    for(int i=0;i<(pos_medico);i++){
        printf("    Medico %d\n",i+1);
        printf("        Nome: %s\n",medico[i].nome);
        printf("        Especialidade: %s\n",medico[i].especialidade);
        printf("        Identificador: %d\n\n",medico[i].identificador);
    }
}

// funcoes para struct paciente

void inserir_Paciente(Paciente **paciente, int *pos_paciente, int *capacidade_paciente){
 
    int num;
    printf("Deseja inserir quantos pacientes:\n");
    scanf("%d",&num);
    getchar();
    *capacidade_paciente = *pos_paciente + num;

    *paciente=(Paciente*)realloc(*paciente,(*capacidade_paciente)*sizeof(Paciente));

    for(int i = *pos_paciente;i < *capacidade_paciente; i++){

        (*paciente)[i].nome       = (char*)malloc(50*sizeof(char));
        (*paciente)[i].endereco   = (char*)malloc(100*sizeof(char));
        (*paciente)[i].identidade = (char*)malloc(15*sizeof(char));
        (*paciente)[i].sexo       = (char*)malloc(15*sizeof(char));
        (*paciente)[i].telefone   = (char*)malloc(20*sizeof(char));


        printf("Digite o nome do paciente:\n");
        fgets((*paciente)[i].nome,50,stdin);
        (*paciente)[i].nome[strcspn((*paciente)[i].nome,"\n")]='\0';

        printf("Digite a identidade do paciente: (xx.xxx.xxx) \n");
        fgets((*paciente)[i].identidade,15,stdin);
        (*paciente)[i].identidade[strcspn((*paciente)[i].identidade,"\n")]='\0';

        printf("Digite o sexo do paciente:\n");
        fgets((*paciente)[i].sexo,15,stdin);
        (*paciente)[i].sexo[strcspn((*paciente)[i].sexo,"\n")]='\0';

        printf("Digite o telefone do paciente: [ (xx) xxxx-xxxx ]\n");
        fgets((*paciente)[i].telefone,20,stdin);
        (*paciente)[i].telefone[strcspn((*paciente)[i].telefone,"\n")]='\0';

        printf("Digite o endereco do paciente: (Estado, Cidade, Rua)\n");
        fgets((*paciente)[i].endereco,100,stdin);
        (*paciente)[i].endereco[strcspn((*paciente)[i].endereco,"\n")]='\0';

        printf("Digite o identificador do paciente: (int)\n");
        scanf("%d",&(*paciente)[i].identificador);
        getchar();

        printf("\n");
    }
    *pos_paciente += num;

}

void imprimir_paciente(Paciente *paciente, int pos_paciente){
    
    printf("Pacientes: \n\n");
    for(int i=0;i<(pos_paciente);i++){
        printf("    Paciente %d\n",i+1);
        printf("        Nome: %s\n",paciente[i].nome);
        printf("        Identidade: %s\n",paciente[i].identidade);
        printf("        Sexo: %s\n",paciente[i].sexo);
        printf("        Telefone: %s\n",paciente[i].telefone);
        printf("        Endereco: %s\n",paciente[i].endereco);
        printf("        Identificador: %d\n\n",paciente[i].identificador);
    }
    printf("\n");
}

// funcoes arquivo

void salvar_arquivo(int pos_medico,int pos_paciente,Medico *medico,Paciente *paciente){

FILE *arq = fopen("Hospital.bin","wb");
if(arq == NULL){
    printf("Falha ao abrir o arquivo\n");
    exit(1);
}
fwrite(&pos_medico,sizeof(int),1,arq);
for(int i = 0; i< pos_medico; i++){
        fwrite(medico[i].especialidade,sizeof(char),50,arq);
        fwrite(medico[i].nome,sizeof(char),50,arq);
        fwrite(&medico[i].identificador,sizeof(int),1,arq);
    }

fwrite(&pos_paciente,sizeof(int),1,arq);
for(int i = 0; i < pos_paciente; i++){
        fwrite(paciente[i].nome,sizeof(char),50,arq);
        fwrite(paciente[i].endereco,sizeof(char),100,arq);
        fwrite(paciente[i].identidade,sizeof(char),15,arq);
        fwrite(paciente[i].sexo,sizeof(char),15,arq);
        fwrite(paciente[i].telefone,sizeof(char),20,arq);
        fwrite(&paciente[i].identificador,sizeof(int),1,arq);
}

fclose(arq);
printf("\n - Dados salvos com sucesso! -\n\n");
}

void ler_arquivo(int *pos_medico,int *pos_paciente,Medico **medico,Paciente **paciente){

FILE *arq = fopen("Hospital.bin","rb");
if(arq == NULL){
    printf("Falha ao abrir o arquivo\n");
    exit(1);    
}

//aloca dinamicamente

fread(pos_medico,sizeof(int),1,arq);
*medico=(Medico*)realloc(*medico,(*pos_medico)*sizeof(Medico));
if(*medico == NULL){
    printf("Falha ao alocar memoria, linha 189\n");
    exit(1);
}
for(int i = 0;i < *pos_medico;i++){ 
    (*medico)[i].especialidade = (char*)malloc(50*sizeof(char));
    (*medico)[i].nome          = (char*)malloc(50*sizeof(char));
}

for(int i = 0; i< *pos_medico; i++){
        fread((*medico)[i].especialidade,sizeof(char),50,arq);
        fread((*medico)[i].nome,sizeof(char),50,arq);
        fread(&(*medico)[i].identificador,sizeof(int),1,arq);
}

fread(pos_paciente,sizeof(int),1,arq);
*paciente=(Paciente*)realloc(*paciente,(*pos_paciente)*sizeof(Paciente));
if(*paciente == NULL){
    printf("Falha ao alocar memoria, linha 178\n");
    exit(1);
}

for(int i = 0;i < *pos_paciente; i++){

    (*paciente)[i].nome       = (char*)malloc(50*sizeof(char));
    (*paciente)[i].endereco   = (char*)malloc(100*sizeof(char));
    (*paciente)[i].identidade = (char*)malloc(15*sizeof(char));
    (*paciente)[i].sexo       = (char*)malloc(15*sizeof(char));
    (*paciente)[i].telefone   = (char*)malloc(20*sizeof(char));

    fread((*paciente)[i].nome,sizeof(char),50,arq);
    fread((*paciente)[i].endereco,sizeof(char),100,arq);
    fread((*paciente)[i].identidade,sizeof(char),15,arq);
    fread((*paciente)[i].sexo,sizeof(char),15,arq);
    fread((*paciente)[i].telefone,sizeof(char),20,arq);
    fread(&(*paciente)[i].identificador,sizeof(int),1,arq);
}
printf("\n - Leitura de dados concluida -\n\n");
fclose(arq);

}

int main(){
    
    //variaveis de controle
    int opcao=1, opcao_aux;
    
    //variaveis p/ medicos
    int pos_medico=0,capacidade_medico=0;
    Medico *medico = NULL;

    // variaveis p/ pacientes
    int pos_paciente=0, capacidade_paciente=0;
    Paciente *paciente = NULL;

    printf("\nSeja bem-vindo(a) ao hospital.\n");

    while(opcao != 0){
        printf("Escolha uma acao:\n\n    (1) (Medicos - Inserir, Imprimir)\n    (2) (Pacientes - Inserir, Imprimir)\n    (9) (Arquivo - Salvar, Carregar)\n    (0) (Sair)\n");
        scanf("%d",&opcao);

        if(opcao == 0){
            printf("Saindo...\n");
            break;
        }

        //sub menu medicos
        else if(opcao == 1){
            printf("        (1) Inserir medicos\n        (2) Imprimir medicos\n");
            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
                inserir_Medico(&medico,&pos_medico,&capacidade_medico);
            
            if(opcao_aux == 2)
                imprimir_Medicos(medico,pos_medico);
        }
        
        //sub menu pacientes
        else if(opcao == 2){
            printf("        (1) Inserir pacientes\n        (2) Imprimir pacientes\n");
            scanf("%d",&opcao_aux);

            if(opcao_aux == 1){
                inserir_Paciente(&paciente,&pos_paciente,&capacidade_paciente);
            }

            if(opcao_aux == 2){
                imprimir_paciente(paciente,pos_paciente);
            }
        }

        else if(opcao == 9){
            printf("        (1) Salvar dados no arquivo\n        (2) Carregar dados do arquivo\n");
            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
            salvar_arquivo(pos_medico,pos_paciente,medico,paciente);

            if(opcao_aux == 2)
            ler_arquivo(&pos_medico,&pos_paciente,&medico,&paciente);
        }
    }

// liberar a memoria alocada
    for (int i = 0; i < pos_medico; i++) {
        free(medico[i].nome);
        free(medico[i].especialidade);
    }
    free(medico);

    for (int i = 0; i < pos_paciente; i++) {
        free(paciente[i].nome);
        free(paciente[i].endereco);
        free(paciente[i].identidade);
        free(paciente[i].telefone);
        free(paciente[i].sexo);
    }
    free(paciente);


return 0;  
}