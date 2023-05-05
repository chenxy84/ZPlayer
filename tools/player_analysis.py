# This is a sample Python script.
import numpy as np
import matplotlib.pyplot as plt

# Press ⌃R to execute it or replace it with your code.
# Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.


def printAnalysis(file):
    data = np.loadtxt(file, delimiter=",", usecols=(2, 3, 4, 5))
    print(np.shape(data))
    time = range(0, data.shape[0])
    # print(time)

    fps = data[:, 0]
    tcp = data[:, 1]
    cpu = data[:, 2]
    mem = data[:, 3]
    # print(fps)

    fig, axs = plt.subplots(4, 1)
    axs[0].plot(time, fps, color='darkblue')
    axs[0].set_ylabel('FPS')
    axs[0].grid(True)

    axs[1].plot(time, tcp, color='deepskyblue')
    axs[1].set_ylabel('TCP bitrate')
    axs[1].get_yaxis().get_major_formatter().set_scientific(False)
    axs[1].grid(True)

    axs[2].plot(time, cpu, color='deeppink')
    axs[2].set_ylabel('CPU %')
    axs[2].grid(True)

    axs[3].plot(time, mem, color='darkgreen')
    axs[3].set_xlabel('Time(s)')
    axs[3].set_ylabel('MEM')
    axs[3].grid(True)

    plt.show()

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    printAnalysis("/Users/chenxiangyu/Documents/player_log_2023_01_03_17_25_26.txt")

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
