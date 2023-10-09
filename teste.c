do {
  limparTela();
  printf("Digite a Data de termino da Tarefa neste formato dd/mm/aaaa: \n"); 
  
  if(scanf("%d/%d/%d", &dia, &mes, &ano) != 3) {
    printf("Formato de data invalido, tente novamente!\n");
    continue;
  }

  if(dia < 1 || dia > MAX_DIA) {
    printf("Dia invalido, deve ser entre 1 e %d\n", MAX_DIA);
    continue;  
  }

  if(mes < 1 || mes > MAX_MES) {
    printf("Mes invalido, deve ser entre 1 e %d\n", MAX_MES);
    continue;
  }

  // data validada com sucesso
  break;

} while(1);