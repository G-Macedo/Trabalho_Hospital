#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definindo as estruturas

typedef struct{
    int identificador;
    char *nome; // Ponteiro para alocar dinamicamente
    char *especialidade;
}Medico;


typedef struct{
    int identificador;
    char *identidade, *nome, *endereco, *sexo, *telefone; 
}Paciente;

typedef struct {
    int numero;
    int identificador_medico;
    int identificador_paciente;
    char *data;     // Formato: "20 de janeiro de 2025"
    char *horario;  // Formato: "HH:MM"
    char *duracao;  // Formato: "HH:MM"
} Consulta;

// Funcões p/ Struct Médico

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

void alterar_Medico(Medico *medico, int pos_medico){
    int id;
    printf("Digite o identificador do medico que deseja alterar:\n");
    scanf("%d",&id);
    getchar();

    for(int i = 0; i < pos_medico; i++){
        if(medico[i].identificador == id){
            printf("Digite o novo nome do medico:\n");
            fgets(medico[i].nome,50,stdin);
            medico[i].nome[strcspn(medico[i].nome,"\n")]='\0';

            printf("Digite a nova especialidade do medico:\n");
            fgets(medico[i].especialidade,50,stdin);
            medico[i].especialidade[strcspn(medico[i].especialidade,"\n")]='\0';
            printf("\n - Medico alterado com sucesso! -\n\n");
            return;
        }
    }
    printf("Medico nao encontrado\n");
}

void pesquisar_Medico(Medico *medico, int pos_medico){
    int id;
    printf("Digite o identificador do medico que deseja pesquisar:\n");
    scanf("%d",&id);
    getchar();

    for(int i = 0; i < pos_medico; i++){
        if(medico[i].identificador == id){
            printf("    Medico %d\n",i+1);
            printf("        Nome: %s\n",medico[i].nome);
            printf("        Especialidade: %s\n",medico[i].especialidade);
            printf("        Identificador: %d\n\n",medico[i].identificador);
            return;
        }
    }
    printf("Medico nao encontrado\n");
}

void excluir_Medico(Medico **medico, int *pos_medico, Consulta **consulta, int *pos_consulta) {
    int id;
    printf("Digite o identificador do medico que deseja excluir:\n");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < *pos_medico; i++) {
        if ((*medico)[i].identificador == id) {
            // Excluir as consultas associadas a este médico
            for (int j = 0; j < *pos_consulta; j++) {
                if ((*consulta)[j].identificador_medico == id) {
                    // Remover consulta associada ao médico
                    free((*consulta)[j].data);
                    for (int k = j; k < *pos_consulta - 1; k++) {
                        (*consulta)[k] = (*consulta)[k + 1];
                    }
                    *consulta = (Consulta*)realloc(*consulta, (*pos_consulta - 1) * sizeof(Consulta));
                    *pos_consulta -= 1;
                    j--; // Reavaliar a posição após o deslocamento
                }
            }
            
            // Excluir os dados do médico
            free((*medico)[i].nome);
            free((*medico)[i].especialidade);
            for (int j = i; j < *pos_medico - 1; j++) {
                (*medico)[j] = (*medico)[j + 1];
            }
            *medico = (Medico*)realloc(*medico, (*pos_medico - 1) * sizeof(Medico));
            *pos_medico -= 1;
            printf("\n - Medico excluido com sucesso! -\n\n");
            return;
        }
    }
    printf("Medico nao encontrado\n");
}

// Funções p/ Struct Paciente

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

void alterar_Paciente(Paciente *paciente, int pos_paciente){
    int id;
    printf("Digite o identificador do paciente que deseja alterar:\n");
    scanf("%d",&id);
    getchar();

    for(int i = 0; i < pos_paciente; i++){
        if(paciente[i].identificador == id){
            printf("Digite o novo nome do paciente:\n");
            fgets(paciente[i].nome,50,stdin);
            paciente[i].nome[strcspn(paciente[i].nome,"\n")]='\0';

            printf("Digite a nova identidade do paciente:\n");
            fgets(paciente[i].identidade,15,stdin);
            paciente[i].identidade[strcspn(paciente[i].identidade,"\n")]='\0';

            printf("Digite o novo sexo do paciente:\n");
            fgets(paciente[i].sexo,15,stdin);
            paciente[i].sexo[strcspn(paciente[i].sexo,"\n")]='\0';

            printf("Digite o novo telefone do paciente:\n");
            fgets(paciente[i].telefone,20,stdin);
            paciente[i].telefone[strcspn(paciente[i].telefone,"\n")]='\0';

            printf("Digite o novo endereco do paciente:\n");
            fgets(paciente[i].endereco,100,stdin);
            paciente[i].endereco[strcspn(paciente[i].endereco,"\n")]='\0';

            printf("\n - Paciente alterado com sucesso! -\n\n");
            return;
        }
    }
    printf("Paciente nao encontrado\n");
}

void pesquisar_Paciente(Paciente *paciente, int pos_paciente){
    int id;
    printf("Digite o identificador do paciente que deseja pesquisar:\n");
    scanf("%d",&id);
    getchar();

    for(int i = 0; i < pos_paciente; i++){
        if(paciente[i].identificador == id){
            printf("    Paciente %d\n",i+1);
            printf("        Nome: %s\n",paciente[i].nome);
            printf("        Identidade: %s\n",paciente[i].identidade);
            printf("        Sexo: %s\n",paciente[i].sexo);
            printf("        Telefone: %s\n",paciente[i].telefone);
            printf("        Endereco: %s\n",paciente[i].endereco);
            printf("        Identificador: %d\n\n",paciente[i].identificador);
            return;
        }
    }
    printf("Paciente nao encontrado\n");
}

void excluir_Paciente(Paciente **paciente, int *pos_paciente, Consulta **consulta, int *pos_consulta) {
    int id;
    printf("Digite o identificador do paciente que deseja excluir:\n");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < *pos_paciente; i++) {
        if ((*paciente)[i].identificador == id) {
            // Excluir as consultas associadas a este paciente
            for (int j = 0; j < *pos_consulta; j++) {
                if ((*consulta)[j].identificador_paciente == id) {
                    // Remover consulta associada ao paciente
                    free((*consulta)[j].data);
                    for (int k = j; k < *pos_consulta - 1; k++) {
                        (*consulta)[k] = (*consulta)[k + 1];
                    }
                    *consulta = (Consulta*)realloc(*consulta, (*pos_consulta - 1) * sizeof(Consulta));
                    *pos_consulta -= 1;
                    j--; // Reavaliar a posição após o deslocamento
                }
            }
            
            // Excluir os dados do paciente
            free((*paciente)[i].nome);
            free((*paciente)[i].endereco);
            free((*paciente)[i].identidade);
            free((*paciente)[i].telefone);
            free((*paciente)[i].sexo);
            for (int j = i; j < *pos_paciente - 1; j++) {
                (*paciente)[j] = (*paciente)[j + 1];
            }
            *paciente = (Paciente*)realloc(*paciente, (*pos_paciente - 1) * sizeof(Paciente));
            *pos_paciente -= 1;
            printf("\n - Paciente excluido com sucesso! -\n\n");
            return;
        }
    }
    printf("Paciente nao encontrado\n");
}

// Funções p/ Struct Consulta

void inserir_Consulta(Consulta **consulta, int *pos_consulta, int *capacidade_consulta){
    int num;
    printf("Deseja inserir quantas consultas:\n");
    scanf("%d", &num);
    getchar();
    *capacidade_consulta = *pos_consulta + num;

    *consulta = (Consulta*)realloc(*consulta, (*capacidade_consulta) * sizeof(Consulta));

    for(int i = *pos_consulta; i < *capacidade_consulta; i++){
        (*consulta)[i].data = (char*)malloc(50 * sizeof(char));
        (*consulta)[i].horario = (char*)malloc(50 * sizeof(char)); // formato HH:MM 
        (*consulta)[i].duracao = (char*)malloc(50 * sizeof(char)); // formato HH:MM 

        printf("Digite o numero da consulta:\n");
        scanf("%d", &(*consulta)[i].numero);
        getchar();

        printf("Digite o identificador do medico:\n");
        scanf("%d", &(*consulta)[i].identificador_medico);
        getchar();

        printf("Digite o identificador do paciente:\n");
        scanf("%d", &(*consulta)[i].identificador_paciente);
        getchar();

        printf("Digite o horario da consulta (HH:MM):\n");
        fgets((*consulta)[i].horario, 50, stdin);
        (*consulta)[i].horario[strcspn((*consulta)[i].horario, "\n")] = '\0';

        printf("Digite a duracao da consulta (HH:MM):\n");
        fgets((*consulta)[i].duracao, 50, stdin);
        (*consulta)[i].duracao[strcspn((*consulta)[i].duracao, "\n")] = '\0';

        printf("Digite a data da consulta:\n");
        fgets((*consulta)[i].data, 50, stdin);
        (*consulta)[i].data[strcspn((*consulta)[i].data, "\n")] = '\0';

        printf("\n");
    }
    *pos_consulta += num;
}

void imprimir_Consulta(Consulta *consulta, int pos_consulta){
    
    printf("Consultas: \n\n");
    for(int i=0;i<(pos_consulta);i++){
        printf("    Consulta %d\n",i+1);
        printf("        Numero: %d\n",consulta[i].numero);
        printf("        Identificador do medico: %d\n",consulta[i].identificador_medico);
        printf("        Identificador do paciente: %d\n",consulta[i].identificador_paciente);
        printf("        Horario: %s\n",consulta[i].horario);
        printf("        Duracao: %s\n",consulta[i].duracao);
        printf("        Data: %s\n",consulta[i].data);
    }
}

void alterar_Consulta(Consulta *consulta, int pos_consulta){
    int id;
    printf("Digite o numero da consulta que deseja alterar:\n");
    scanf("%d",&id);
    getchar();

    for(int i = 0; i < pos_consulta; i++){
        if(consulta[i].numero == id){
            printf("Digite o novo numero da consulta:\n");
            scanf("%d",&consulta[i].numero);
            getchar();

            printf("Digite o novo identificador do medico:\n");
            scanf("%d",&consulta[i].identificador_medico);
            getchar();

            printf("Digite o novo identificador do paciente:\n");
            scanf("%d",&consulta[i].identificador_paciente);
            getchar();

            printf("Digite o novo horario da consulta:\n");
            fgets(consulta[i].horario, 50, stdin);
            consulta[i].horario[strcspn(consulta[i].horario,"\n")]='\0';

            printf("Digite a nova duracao da consulta:\n");
            fgets(consulta[i].duracao, 50, stdin);
            consulta[i].duracao[strcspn(consulta[i].duracao,"\n")]='\0';

            printf("Digite a nova data da consulta:\n");
            fgets(consulta[i].data, 50, stdin);
            consulta[i].data[strcspn(consulta[i].data,"\n")]='\0';

            printf("\n - Consulta alterada com sucesso! -\n\n");
            return;
        }
    }
    printf("Consulta nao encontrada\n");
}

void pesquisar_Consulta(Consulta *consulta, int pos_consulta){
    int id;
    printf("Digite o numero da consulta que deseja pesquisar:\n");
    scanf("%d",&id);
    getchar();

    for(int i = 0; i < pos_consulta; i++){
        if(consulta[i].numero == id){
            printf("    Consulta %d\n",i+1);
            printf("        Numero: %d\n",consulta[i].numero);
            printf("        Identificador do medico: %d\n",consulta[i].identificador_medico);
            printf("        Identificador do paciente: %d\n",consulta[i].identificador_paciente);
            printf("        Horario: %s\n",consulta[i].horario);
            printf("        Duracao: %s\n",consulta[i].duracao);
            printf("        Data: %s\n",consulta[i].data);
            return;
        }
    }
    printf("Consulta nao encontrada\n");
}

void excluir_Consulta (Consulta **consulta, int *pos_consulta){
    int id;
    printf("Digite o numero da consulta que deseja excluir:\n");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < *pos_consulta; i++){
        if((*consulta)[i].numero == id){
            free((*consulta)[i].data);
            free((*consulta)[i].horario);
            free((*consulta)[i].duracao);
            
            for(int j = i; j < *pos_consulta - 1; j++){
                (*consulta)[j] = (*consulta)[j + 1];
            }
            *consulta = (Consulta*)realloc(*consulta, (*pos_consulta - 1) * sizeof(Consulta));
            *pos_consulta -= 1;
            printf("\n - Consulta excluida com sucesso! -\n\n");
            return;
        }
    }
    printf("Consulta nao encontrada\n");
}

// Funções Relatórios

void consultas_Paciente(Consulta *consulta, int pos_consulta){
    int id;
    printf("Digite o identificador do paciente:\n");
    scanf("%d",&id);
    getchar();

    printf("Consultas do paciente:\n\n");
    for(int i = 0; i < pos_consulta; i++){
        if(consulta[i].identificador_paciente == id){
            printf("    Consulta %d\n",i+1);
            printf("        Numero: %d\n",consulta[i].numero);
            printf("        Identificador do medico: %d\n",consulta[i].identificador_medico);
            printf("        Identificador do paciente: %d\n",consulta[i].identificador_paciente);
            printf("        Horario: %s\n",consulta[i].horario);
            printf("        Duracao: %s\n",consulta[i].duracao);
            printf("        Data: %s\n\n",consulta[i].data);
        }
    }
}

void consultas_Medico(Consulta *consulta, int pos_consulta){
    int id;
    printf("Digite o identificador do medico:\n");
    scanf("%d",&id);
    getchar();

    printf("Consultas do medico:\n\n");
    for(int i = 0; i < pos_consulta; i++){
        if(consulta[i].identificador_medico == id){
            printf("    Consulta %d\n",i+1);
            printf("        Numero: %d\n",consulta[i].numero);
            printf("        Identificador do medico: %d\n",consulta[i].identificador_medico);
            printf("        Identificador do paciente: %d\n",consulta[i].identificador_paciente);
            printf("        Horario: %s\n",consulta[i].horario);
            printf("        Duracao: %s\n",consulta[i].duracao);
            printf("        Data: %s\n\n",consulta[i].data);
        }
    }
}

void lista_Medicos(Medico *medico, int pos_medico){
    char especialidade[50];

    while (getchar() != '\n'); // Limpar buffer antes de usar o fgets

    printf("Digite a especialidade:\n");
    fgets(especialidade,50,stdin);
    especialidade[strcspn(especialidade,"\n")]='\0';

    printf("Medicos da especialidade %s:\n\n",especialidade);
    for(int i = 0; i < pos_medico; i++){
        if(strcmp(medico[i].especialidade,especialidade) == 0){
            printf("    Medico %d\n",i+1);
            printf("        Nome: %s\n",medico[i].nome);
            printf("        Especialidade: %s\n",medico[i].especialidade);
            printf("        Identificador: %d\n\n",medico[i].identificador);
        }
    }
}

// Funções Arquivo

void salvar_arquivo(int pos_medico, int pos_paciente, int pos_consulta, Medico *medico, Paciente *paciente, Consulta *consulta) {

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

    fwrite(&pos_consulta,sizeof(int),1,arq);
    for(int i = 0; i < pos_consulta; i++){
        fwrite(consulta[i].data,sizeof(char),50,arq);
        fwrite(consulta[i].duracao,sizeof(char),50,arq);
        fwrite(consulta[i].horario,sizeof(char),50,arq);
        fwrite(&consulta[i].identificador_medico,sizeof(int),1,arq);
        fwrite(&consulta[i].identificador_paciente,sizeof(int),1,arq);
        fwrite(&consulta[i].numero,sizeof(int),1,arq);
    }

    fclose(arq);
    printf("\n - Dados salvos com sucesso! -\n\n");
}

void ler_arquivo(int *pos_medico, int *pos_paciente, int *pos_consulta, Consulta **consulta, Medico **medico, Paciente **paciente) {

    FILE *arq = fopen("Hospital.bin","rb");
    if(arq == NULL){
        printf("Falha ao abrir o arquivo\n");
        exit(1);    
    }

    // Aloca dinamicamente
    fread(pos_medico,sizeof(int),1,arq);
    *medico=(Medico*)realloc(*medico,(*pos_medico)*sizeof(Medico));
    if(*medico == NULL){
        printf("Falha ao alocar memoria, linha 189\n");
        exit(1);
    }

    for(int i = 0;i < *pos_medico;i++){ 
        (*medico)[i].especialidade = (char*)malloc(50*sizeof(char));
        (*medico)[i].nome          = (char*)malloc(50*sizeof(char));

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
    
    

    fread(pos_consulta,sizeof(int),1,arq);
    *consulta=(Consulta*)realloc(*consulta,(*pos_consulta)*sizeof(Consulta));
    if(*consulta == NULL){
        printf("erro ao alocar memoria\n");
        exit(1);
    }
    for(int i = 0; i < *pos_consulta; i++){
        (*consulta)[i].data    = (char*)malloc(50*sizeof(char));
        (*consulta)[i].duracao = (char*)malloc(50*sizeof(char));
        (*consulta)[i].horario = (char*)malloc(50*sizeof(char));

        fread((*consulta)[i].data,sizeof(char),50,arq);
        fread((*consulta)[i].duracao,sizeof(char),50,arq);
        fread((*consulta)[i].horario,sizeof(char),50,arq);
        fread(&(*consulta)[i].identificador_medico,sizeof(int),1,arq);
        fread(&(*consulta)[i].identificador_paciente,sizeof(int),1,arq);
        fread(&(*consulta)[i].numero,sizeof(int),1,arq);
    }

    printf("\n - Leitura de dados concluida -\n\n");
    fclose(arq);
}

int main() {

    // Váriaveis de Controle
    int opcao=1, opcao_aux;
    
    // Váriaveis p/ Médicos
    int pos_medico=0, capacidade_medico=0;
    Medico *medico = NULL;

    // Váriaveis p/ Pacientes
    int pos_paciente=0, capacidade_paciente=0;
    Paciente *paciente = NULL;
    
    // Váriaveis p/ Consultas
    int pos_consulta=0, capacidade_consulta=0;
    Consulta *consulta = NULL;

    printf("\nSeja bem-vindo(a) ao hospital.\n");

    while(opcao != 0){
        printf("Escolha uma acao:\n\n");
        printf("    (1) (Medicos - Inserir, Imprimir, Alterar, Pesquisar, Excluir)\n");
        printf("    (2) (Pacientes - Inserir, Imprimir, Alterar, Pesquisar, Exlcuir)\n");
        printf("    (3) (Consultas - Inserir, Imprimir, Alterar, Pesquisar, Excluir)\n");
        printf("    (4) (Relatorios)\n");
        printf("    (9) (Arquivo - Salvar, Carregar)\n");
        printf("    (0) (Sair)\n");
        scanf("%d",&opcao);

        if(opcao == 0){
            printf("Saindo...\n");
            break;
        }

        // Submenu Médicos
        else if(opcao == 1){
            printf("        (1) Inserir medicos\n");
            printf("        (2) Imprimir medicos\n");
            printf("        (3) Alterar medicos\n");
            printf("        (4) Pesquisar medicos\n");
            printf("        (5) Excluir medicos\n");

            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
                inserir_Medico(&medico, &pos_medico, &capacidade_medico);
            
            if(opcao_aux == 2)
                imprimir_Medicos(medico, pos_medico);

            if(opcao_aux == 3)
                alterar_Medico(medico, pos_medico);
            
            if(opcao_aux == 4)
                pesquisar_Medico(medico, pos_medico);

            if(opcao_aux == 5)
                excluir_Medico(&medico, &pos_medico, &consulta, &pos_consulta);
        }
        
        // Submenu Pacientes
        else if(opcao == 2){
            printf("        (1) Inserir pacientes\n");
            printf("        (2) Imprimir pacientes\n");
            printf("        (3) Alterar pacientes\n");
            printf("        (4) Pesquisar pacientes\n");
            printf("        (5) Excluir pacientes\n");

            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
                inserir_Paciente(&paciente, &pos_paciente, &capacidade_paciente);
            
            if(opcao_aux == 2)
                imprimir_paciente(paciente, pos_paciente);
            
            if(opcao_aux == 3)
                alterar_Paciente(paciente, pos_paciente);
            
            if(opcao_aux == 4)
                pesquisar_Paciente(paciente, pos_paciente);
            
            if(opcao_aux == 5)
                excluir_Paciente(&paciente, &pos_paciente, &consulta, &pos_consulta);
            
        }

        //Submenu Relatórios
        else if(opcao == 4){
            printf("        (1) Consultas por paciente\n");
            printf("        (2) Consultas por medico\n");
            printf("        (3) Lista de medicos por especialidade\n");
            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
                consultas_Paciente(consulta, pos_consulta);
            
            if(opcao_aux == 2)
                consultas_Medico(consulta, pos_consulta); 
            
            if(opcao_aux == 3)
                lista_Medicos(medico, pos_medico);
                
        }

        // Submenu Consultas
        else if(opcao == 3){
            printf("        (1) Inserir consultas\n");
            printf("        (2) Imprimir consultas\n");
            printf("        (3) Alterar consultas\n");
            printf("        (4) Pesquisar consultas\n");
            printf("        (5) Excluir consultas\n");

            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
                inserir_Consulta(&consulta, &pos_consulta, &capacidade_consulta);
            
            if(opcao_aux == 2)
                imprimir_Consulta(consulta, pos_consulta);

            if(opcao_aux == 3)
                alterar_Consulta(consulta, pos_consulta);

            if(opcao_aux == 4)
                pesquisar_Consulta(consulta, pos_consulta);

            if(opcao_aux == 5)
                excluir_Consulta(&consulta, &pos_consulta);
        }
        
        // Submenu Arquivo
        else if(opcao == 9){
            printf("        (1) Salvar dados no arquivo\n        (2) Carregar dados do arquivo\n");
            scanf("%d",&opcao_aux);

            if(opcao_aux == 1)
                salvar_arquivo(pos_medico, pos_paciente, pos_consulta, medico, paciente, consulta);

            if(opcao_aux == 2)
                ler_arquivo(&pos_medico, &pos_paciente, &pos_consulta, &consulta, &medico, &paciente);
        }
    }

    // Liberar a memória alocada
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

    for(int i = 0; i < pos_consulta; i++){
        free(consulta[i].data);
        free(consulta[i].duracao);
        free(consulta[i].horario);
    }
    free(consulta);

    return 0;  
}