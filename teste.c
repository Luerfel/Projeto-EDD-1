        Tarefa tarefa1,tarefa2,tarefa3,tarefa4;
 tarefa1.codigo = 1;
  strcpy(tarefa1.tarefa, "Implementar login");
  strcpy(tarefa1.projeto, "Sistema de vendas");
  tarefa1.dataInicio.dia = 1;
  tarefa1.dataInicio.mes = 10;
  tarefa1.dataInicio.ano = 2023;
  tarefa1.dataTermino.dia = 15; 
  tarefa1.dataTermino.mes = 10;
  tarefa1.dataTermino.ano = 2023;
  tarefa1.status = 1;


  // Tarefa 3
  tarefa3.codigo = 3; 
  strcpy(tarefa3.tarefa, "Implementar carrinho de compras");
  strcpy(tarefa3.projeto, "Loja online");
  tarefa3.dataInicio.dia = 1;
  tarefa3.dataInicio.mes = 11;
  tarefa3.dataInicio.ano = 2023;
  tarefa3.dataTermino.dia = 15;
  tarefa3.dataTermino.mes = 11;
  tarefa3.dataTermino.ano = 2023;
  tarefa3.status = 1;

  tarefa2.codigo = 4;
  strcpy(tarefa2.tarefa, "Cdsfsdfsfsdutos");
  strcpy(tarefa2.projeto, "Sistema d32423423423e vendas");
  tarefa2.dataInicio.dia = 15;
  tarefa2.dataInicio.mes = 10;
  tarefa2.dataInicio.ano = 2023;
  tarefa2.dataTermino.dia = 30;
  tarefa2.dataTermino.mes = 10;
  tarefa2.dataTermino.ano = 2024;
  tarefa2.status = 0;

listaConcluida=inserirLista(listaConcluida,tarefa1);
listaConcluida=inserirLista(listaConcluida,tarefa2);
listaConcluida=inserirLista(listaConcluida,tarefa3);
listaConcluida=inserirLista(listaConcluida,tarefa4);