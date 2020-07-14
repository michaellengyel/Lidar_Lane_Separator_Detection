"""The cloudalization_static.py takes the data of a single revolution and displays it. This is a simplification of the
cloudalization_dynamic.py, in that it does not update animate the data via a sliding window. In this context, a 'frame'
means all the data generated during single 360 degrees rotation of the lidar."""

# Imports
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import pandas
import numpy as np

# Global Variables
measurement_name = '../../Lidar_Lane_Separator_Detection/res/2.csv'


def render_data():

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    data_skip = 1

    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')

    df = pandas.read_csv(measurement_name, usecols=[0, 1, 2])

    x = df.iloc[:, 0]
    y = df.iloc[:, 1]
    z = df.iloc[:, 2]

    ax.scatter(x, y, z, c='g', marker='.', s=1)

    ax.set_xlim3d(-15, 15)
    ax.set_ylim3d(-15, 15)
    ax.set_zlim3d(-3, 3)

    plt.show()


def main():
    render_data()


if __name__ == "__main__":
    main()
