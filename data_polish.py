import pandas as pd
import numpy as np

df = pd.read_excel('../Dataset.xlsx')

def aggregate(df):
    # Calcula os IDs para agrupamento
    id = np.array([])
    for i in range(0, df.shape[0]):
        id_calc = df['Supply Site Code'][i] + str(df['SKU'][i]) + df['Location Code'][i] + df['Location Type'][i]
        id = np.append(id, id_calc)
    df['ID'] = id

    # Verifica se existem valores iguais após a ordenação
    df.sort_values(['ID'], inplace=True)
    for i in range(0, df.shape[0] - 1):
        if df['ID'][i] == df['ID'][i+1]:
            print('O próximo é igual nesse índice:' + str(i))

    # Agrupa valores iguais de ID
    agg_func = {
                'Supply Site Code'   : 'first',
                'SKU'                : 'first',
                'Location Code'      : 'first',
                'Location Type'      : 'first',
                'MinDOC (Hl)'        : 'sum',
                'Reorder Point (Hl)' : 'sum',
                'MaxDOC (Hl)'        : 'sum',
                'Closing Stock'      : 'sum',
                'Current CS/MIN'     : 'first',
                'Current CS/ROP'     : 'first',
                'Current CS/MAX'     : 'first',
                'Distributor Orders' : 'sum',
                'Available to Deploy': 'sum',
                'Scenario'           : 'first'
               }
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
    supply_sites = np.array([])
    for i in range(0, len(df)):
        if not np.isin(df['Supply Site Code'][i], supply_sites):
            supply_sites = np.append(df['Supply Site Code'][i], supply_sites)
    print(supply_sites)


df = aggregate(df)
df = clear(df)

df.to_csv('../clearData.csv', index=False)
df.to_excel('../clearData.xlsx', index=False)

