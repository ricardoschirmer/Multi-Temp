
import csv
import matplotlib.pyplot as plt

# Perguntar ao usuário qual experimento ele deseja visualizar
arquivo = input("Digite o nome do arquivo CSV que deseja visualizar (ex: 202305121521): ") + '.csv'

# Ler os dados do arquivo CSV
tempo = []
sensor_1 = []
sensor_2 = []
sensor_3 = []
sensor_4 = []
sensor_5 = []

with open(arquivo, 'r', newline='') as arquivo_csv:
    leitor = csv.reader(arquivo_csv)
    for linha in leitor:
        tempo.append(linha[0])
        sensor_1.append(float(linha[1]))
        sensor_2.append(float(linha[2]))
        sensor_3.append(float(linha[3]))
        sensor_4.append(float(linha[4]))
        sensor_5.append(float(linha[5]))  # 202305121751

# Criação da figura e do eixo
fig, ax = plt.subplots()

# Plotagem dos dados
ax.plot(tempo, sensor_1, label='Sensor 1')
ax.plot(tempo, sensor_2, label='Sensor 2')
ax.plot(tempo, sensor_3, label='Sensor 3')
ax.plot(tempo, sensor_4, label='Sensor 4')
ax.plot(tempo, sensor_5, label='Sensor 5')
ax.legend()
ax.set_xlabel('Tempo')
ax.set_ylabel('Temperatura (Celsius)')
ax.set_title('Temperaturas dos Sensores')
plt.gcf().autofmt_xdate()
plt.show()
