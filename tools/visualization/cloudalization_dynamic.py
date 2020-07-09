from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import pandas
import numpy as np


"""Planned stratagy for data visualization is as follows. In every cycle the software reads in the next 360 degrees of
data from the .csv file. This 360 degrees of data will then be displayed as a single 3D Frame. Since each such frame 
has a significant duration in time (1/t) during which the vehicle will move forward, this will cause an offset for
which the visualization must correct. Since no vehicle speed is provided, it is not clear how this will be done."""

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
data_skip = 1


"""Reads in a Frame of data from the .csv file. In each cycle it reads in the next frame of data. Probably also has to
check what that next data exactly means since it seems the lidar's rotation and it's scans are not in sync."""
#TODO: Parameterize
#TODO: Handle readfile exception
def init_func():

    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')


"""All rendering of the frame should be done in this function"""
#TODO: Move rendering from readDate() to this function
def update_plot(i):
    #ax.clear()
    df = pandas.read_csv('../../Lidar_Lane_Separator_Detection/res/4.csv', skiprows=i*400, nrows=64, header=1,
                         usecols=[0, 1, 2])

    print(i)

    x = df.iloc[:, 0]
    y = df.iloc[:, 1]
    z = df.iloc[:, 2]

    ax.set_xlim3d(-10, 10)
    ax.set_ylim3d(-10, 10)
    ax.set_zlim3d(-3, 3)

    ax.scatter(x, y, z, c='r', marker='.')


"""Main function is responsible for the sliding window logic. This logic will feed data to the helper funtions
which then load the next frame and render it"""
# TODO: Implement


def main():

    anim = FuncAnimation(fig, update_plot, frames=np.arange(0, 5000, 1), init_func=init_func, interval=30)
    plt.show()

if __name__ == "__main__":

    main()
