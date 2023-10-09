
Data lerDataValida(Data data) {

  do {
    limparTela();
    printf("Digite a Data de termino da Tarefa neste formato dd/mm/aaaa: \n");

    if(scanf("%d/%d/%d", data.dia, data.mes, data.ano) != 3) {
      printf("Formato de data invalido, tente novamente!\n");
      continue;
    }

    if(*dia < 1 || data.dia > MAX_DIA) {
      printf("Dia invalido, deve ser entre 1 e %d\n", MAX_DIA);
      continue;  
    }

    if(*mes < 1 || data.mes > MAX_MES) {
      printf("Mes invalido, deve ser entre 1 e %d\n", MAX_MES);
      continue;
    }

    return data; // data válida

  } while(1);

  
}