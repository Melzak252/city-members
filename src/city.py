import math
import tqdm
import imageio

from src.party import Party

import numpy as np
import matplotlib.pyplot as plt

plt.style.use("dark_background")


def distance(p1: Party, p2: Party):
    return math.dist(p1.coords, p2.coords)


class City:

    def __init__(self, city_size: float = 25.0, population_size: int = 10_000, neigh_dist: float = 1.0,
                 move_out_dist: float = 1.0):
        self.size = city_size
        self.populate(population_size)
        self.current_year = 0
        self.neigh_dist = neigh_dist
        self.move_out_dist = move_out_dist

    def populate(self, population_size):
        self.population: list[Party] = [Party(x, y, (i % 2) * 2 - 1) for i, (x, y) in
                                        enumerate(np.random.uniform(0, self.size, size=(population_size, 2)))]

    def next_year(self):

        for p in self.population:
            p.neigbourhood = 0

        move_out = []
        for i, p in tqdm.tqdm(enumerate(self.population), total=len(self.population)):
            for p1 in self.population[i:]:
                if distance(p, p1) < self.neigh_dist:
                    tmp = p.type * p1.type

                    p.neigbourhood += tmp
                    p1.neigbourhood += tmp

            if p.neigbourhood < 0:
                move_out.append(p)

        for p in move_out:
            p.move_out(self.move_out_dist, self.size)

        self.plot()

        self.current_year += 1

    def plot(self):
        x_axis = [p.x for p in self.population]
        y_axis = [p.y for p in self.population]
        colours = ["red" if p.type > 0 else "blue" for p in self.population]
        plt.scatter(x_axis, y_axis, c=colours, s=1)
        plt.axis("off")

        # plt.imsave(f"../fig/year_{self.current_year}.png")
        plt.savefig(f"../fig/year_{self.current_year}.png", bbox_inches='tight', pad_inches=0, dpi=400)

    def make_gif(self):
        frames = [imageio.v2.imread(f'../fig/year_{t}.png') for t in range(self.current_year)]
        imageio.mimsave('example.gif', frames, duration=200)
