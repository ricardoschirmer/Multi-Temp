
import csv
import matplotlib.pyplot as plt

# PERGUNTAR AO USUÁRIO QUAL EXPERIMENTO ELE DESEJA VISUALIZAR
arquivo = input("Digite o nome do arquivo CSV que deseja visualizar (ex: 202305121521): ") + '.csv'

# LER OS DADOS DO ARQUIVO CSV
tempo = []
sensor_1 = []
sensor_2 = []
sensor_3 = []
sensor_4 = []
sensor_5 = []
# LEITURA DE TODOS DADOS GERANDO, GRÁFICO FINAL
with open(arquivo, 'r', newline='') as arquivo_csv:
    leitor = csv.reader(arquivo_csv)
    for linha in leitor:
        tempo.append(linha[0])
        sensor_1.append(float(linha[1]))
        sensor_2.append(float(linha[2]))
        sensor_3.append(float(linha[3]))
        sensor_4.append(float(linha[4]))
        sensor_5.append(float(linha[5]))

# Criação da figura e do eixo
fig, ax = plt.subplots()

# Plotagem dos dados
ax.plot(tempo, sensor_1, color='blue', label='Sensor 1')  # COR DA LINHA DO SENSOR 1
ax.plot(tempo, sensor_2, color='navy', label='Sensor 2')  # COR DA LINHA DO SENSOR 2
ax.plot(tempo, sensor_3, color='lime', label='Sensor 3')  # COR DA LINHA DO SENSOR 3
ax.plot(tempo, sensor_4, color='aqua', label='Sensor 4')  # COR DA LINHA DO SENSOR 4
ax.plot(tempo, sensor_5, color='red', label='Sensor 5')   # COR DA LINHA DO SENSOR DA RESISTÊNCIA 5
ax.legend()
ax.set_xlabel('Tempo')  # EIXO X
ax.set_ylabel('Temperatura (Celsius)')  # EIXO Y
ax.set_title('Temperaturas dos Sensores')  # TITULO DO GRÁFICO
plt.gcf().autofmt_xdate()
plt.show()
