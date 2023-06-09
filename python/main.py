import serial
import time
import datetime
import csv
import matplotlib.pyplot as plt

# Inicialização da porta serial
ser = serial.Serial('COM5', 9600)
nome_arquivo = datetime.datetime.now().strftime('%Y%m%d%H%M') + '.csv'

# Criação da figura e do eixo
fig, ax = plt.subplots()

# Definição das listas vazias para armazenar as medições
tempo = []
sensor_1 = []
sensor_2 = []
sensor_3 = []
sensor_4 = []
sensor_5 = []

# Loop principal
while True:
    # Leitura dos dados da porta serial
    dados = ser.readline().decode('utf-8').rstrip()

    # Separando os dados em uma lista
    dados_separados = dados.split(',')

    # Checagem para garantir que os dados são válidos
    if len(dados_separados) == 6:
        # Armazenamento dos dados em variáveis em cada 10 segundos
        t = datetime.datetime.now().strftime('%H:%M:%S')
        s1 = float(dados_separados[1])
        s2 = float(dados_separados[2])
        s3 = float(dados_separados[3])
        s4 = float(dados_separados[4])
        s5 = float(dados_separados[5])

        # Adição dos dados às listas
        tempo.append(t)
        sensor_1.append(s1)
        sensor_2.append(s2)
        sensor_3.append(s3)
        sensor_4.append(s4)
        sensor_5.append(s5)

        # Plotagem dos dados
        ax.clear()
        ax.plot(tempo, sensor_1, color='blue', label='Sensor 1')    # cor da linha no sensor 1
        ax.plot(tempo, sensor_2, color='navy', label='Sensor 2')    # cor na linha no sensor 2
        ax.plot(tempo, sensor_3, color='lime', label='Sensor 3')    # cor da linha no sensor 3
        ax.plot(tempo, sensor_4, color='aqua', label='Sensor 4')    # cor da linha no sensor 4
        ax.plot(tempo, sensor_5, color='red', label='Resistência')  # cor da linha no sensor resistência 5
        ax.legend()
        ax.set_xlabel('Tempo')  # no eixo x
        ax.set_ylabel('Temperatura (Celsius)')  # no eixo y
        ax.set_title('Temperaturas dos Sensores')  # legenda superior
        plt.gcf().autofmt_xdate()
        plt.draw()
        plt.pause(0.1)

        # Salvar os dados em um arquivo CSV para visualização posterior completa do gráfico
        with open(nome_arquivo, 'a', newline='') as arquivo_csv:
            escrever = csv.writer(arquivo_csv)
            escrever.writerow([t, s1, s2, s3, s4, s5])
