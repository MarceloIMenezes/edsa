import pandas as pd
import numpy as np

print('Deixe o nome do dataset original como \'Data.xlsx\'')
path = input('Digite o diretório onde se encontra o dataset: ')
df = pd.read_excel(path + '/Data.xlsx')

id_columns = ('Supply Site Code', 'SKU', 'Location Code', 'Location Type')
agg_columns_func = ('first','first','first','first','sum','sum','sum','sum','sum','first','first','first','sum','first')

def aggregate(df, id_columns, agg_columns_func):
    # Monta funções de agrupamento
    agg_func = {}
    for i in range(0, len(df.columns)):
        agg_func[df.columns[i]] = agg_columns_func[i]

    # Calcula os IDs para agrupamento
    id = np.array([])
    for i in range(0, df.shape[0]):
        id_calc = ''
        for j in range(0, len(id_columns)):
            if df.dtypes[id_columns[j]] == object:
                id_calc += df[id_columns[j]][i]
            else:
                id_calc += str(df[id_columns[j]][i])
        id = np.append(id, id_calc)
    df['ID'] = id

    # Verifica se existem valores iguais após a ordenação
    df.sort_values(['ID'], inplace=True)
    for i in range(0, df.shape[0] - 1):
        if df['ID'][i] == df['ID'][i+1]:
            print('O próximo é igual nesse índice:' + str(i))

    # Agrupa valores iguais de ID 
    df = df.groupby(df['ID']).aggregate(agg_func)

    df.reset_index(drop=True, inplace=True)

    return df

def clear(df): 
    contaCenarios0 = 0
    contaMinMaxDOC = 0
    contaMaxDOC0   = 0

    # Apaga colunas que não usaremos
    df.drop(['Current CS/MIN','Current CS/ROP','Current CS/MAX'], axis=1, inplace=True)

    # Limpeza dos dados
    for i in range(0, len(df)):            
        if df['MinDOC (Hl)'][i] > df['MaxDOC (Hl)'][i]:
            contaMinMaxDOC = contaMinMaxDOC + 1
            df.drop([i], inplace=True)    
        elif df['MaxDOC (Hl)'][i] == 0:
            contaMaxDOC0 = contaMaxDOC0 + 1
            df.drop([i], inplace=True)    
        elif df['Scenario'][i] == 0:
            contaCenarios0 = contaCenarios0 + 1
            df.drop([i], inplace=True)   

    df.reset_index(drop=True, inplace=True)     

    print('Cenários 0 eliminados: ' + str(contaCenarios0))
    print('MinMaxDoc  eliminados: ' + str(contaMinMaxDOC))
    print('MaxDoc 0   eliminados: ' + str(contaMaxDOC0))

    return df

def supply_site_count(df):
    # Contagem de todos os Supply Sites 
    supply_sites = np.array([])
    for i in range(0, len(df)):
        if not np.isin(df['Supply Site Code'][i], supply_sites):
            supply_sites = np.append(df['Supply Site Code'][i], supply_sites)
    print(supply_sites)

df = aggregate(df, id_columns, agg_columns_func)
df = clear(df)

# df.to_csv('clearData.csv', index=False)
# df.to_excel('clearData.xlsx', index=False)

# Separa e salva em quatro arquivos cada cenário
for i in range(1, 5):
    df_aux = df[df['Scenario'] == i]
    df_aux = df_aux.drop(['Scenario'], axis=1)
    df_aux.to_csv(path + '/clearDataScenario'+str(i)+'.csv', index=False)
    # df_aux.to_excel('clearDataScenario'+str(i)+'.xlsx', index=False)
