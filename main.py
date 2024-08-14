
from src.city import City

if __name__ == '__main__':
    c = City(city_size=50, population_size=50_000, neigh_dist=3, move_out_dist=3)
    c.plot()
    for _ in range(100):
        c.next_year()

    c.make_gif()
    print("Finished")
    