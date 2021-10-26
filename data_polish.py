import pandas as pd
import numpy as np

df = pd.read_excel('Dataset.xlsx')

# Apaga colunas que não usaremos
df.drop(['Current CS/MIN','Current CS/ROP','Current CS/MAX'], axis=1, inplace=True)

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

# # Agrupa valores iguais de ID
# agg_func = {
#             'Supply Site Code': 'first', 
#             'SKU': 'first', 
#             'Location Code': 'first',
#             'Location Type': 'first',
#             'MinDOC (Hl)': 'sum',
#             'Reorder Point (Hl)': 'sum',
#             'MaxDOC (Hl)': 'sum',
#             'Closing Stock': 'sum',  
#             'Distributor Orders': 'sum',
#             'Available to Deploy': 'sum',
#             'Scenario': 'first'
#            }
# df = df.groupby(df['ID']).aggregate(agg_func)


# Limpeza comentada pois só será utilizada após merge de iguais
supply_sites = []
supply_sites = np.array(supply_sites)

contaCenarios0 = 0
contaMinMaxDOC = 0
contaMaxDOC0 = 0

# Limpeza dos dados
for i in range(0, len(df)):
    if not np.isin(df['Supply Site Code'][i], supply_sites):
        supply_sites = np.append(df['Supply Site Code'][i], supply_sites)  
        
    if df['MinDOC (Hl)'][i] > df['MaxDOC (Hl)'][i]:
        contaMinMaxDOC = contaMinMaxDOC + 1
        df.drop([i], inplace=True)    
    elif df['MaxDOC (Hl)'][i] == 0:
        contaMaxDOC0 = contaMaxDOC0 + 1
        df.drop([i], inplace=True)    
    elif df['Scenario'][i] == 0:
        contaCenarios0 = contaCenarios0 + 1
        df.drop([i], inplace=True)        

print('Cenários 0 eliminados: ' + str(contaCenarios0))
print('MinMaxDoc  eliminados: ' + str(contaMinMaxDOC))
print('MaxDoc 0   eliminados: ' + str(contaMaxDOC0))

print(supply_sites)

df.to_csv('clearData.csv', index=False)
df.to_excel('clearData.xlsx', index=False)

