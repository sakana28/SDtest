import numpy as np
import matplotlib.pyplot as plt

def sigmoid(x):
    """
    计算一个数的 sigmoid 函数值
    """
    return 1 / (1 + np.exp(-x))

def main():
    # 计算一组数的 sigmoid 函数值
    x_values = np.linspace(-10, 10, num=100)
    y_values = sigmoid(x_values)

    # 绘制图形
    plt.plot(x_values, y_values)
    plt.xlabel('X Value')
    plt.ylabel('Y Value')
    plt.title('Sigmoid Function')
    plt.show()

if __name__ == '__main__':
    main()
