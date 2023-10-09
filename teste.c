    if (dataInicio.ano > dataTermino.ano)
    {
        return 1;
    }
    else if (dataInicio.ano != dataTermino.ano)
    {
        return 0;
    }
    else if (dataInicio.mes > dataTermino.mes)
    {
        return 1;
    }
    else if (dataInicio.mes == dataTermino.mes && dataInicio.dia > dataTermino.dia)
    {
        return 1;
    }
    else
        return 0;



// 1 atrasada, 0 em dia