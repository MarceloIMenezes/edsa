import pandas as pd
import numpy as np

df = pd.read_excel('Dataset.xlsx')

###########################################################################
# Jeito chique que não deu certo
# cenario0 = df.index[df['Scenario'] == 0]
# print(cenario0)
# df.drop(cenario0, inplace=True)
###########################################################################

###########################################################################
# supply_sites = []
# supply_sites = np.array(supply_sites)

# contaCenarios0 = 0
# contaMinMaxDOC = 0
# contaMaxDOC0 = 0

# # Limpeza dos dados
# for i in range(0, len(df)):
#     if not np.isin(df['Supply Site Code'][i], supply_sites):
#         supply_sites = np.append(df['Supply Site Code'][i], supply_sites)  
        
#     if df['MinDOC (Hl)'][i] > df['MaxDOC (Hl)'][i]:
#         contaMinMaxDOC = contaMinMaxDOC + 1
#         df.drop([i], inplace=True)    
#     elif df['MaxDOC (Hl)'][i] == 0:
#         contaMaxDOC0 = contaMaxDOC0 + 1
#         df.drop([i], inplace=True)    
#     elif df['Scenario'][i] == 0:
#         contaCenarios0 = contaCenarios0 + 1
#         df.drop([i], inplace=True)        

# print('Cenários 0 eliminados: ' + str(contaCenarios0))
# print('MinMaxDoc  eliminados: ' + str(contaMinMaxDOC))
# print('MaxDoc 0   eliminados: ' + str(contaMaxDOC0))
###########################################################################

df.to_excel('clearData.xlsx', index=False)


# print(supply_sites)