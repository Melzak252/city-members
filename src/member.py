from dataclasses import dataclass
import math
import random

@dataclass
class Member:
    x: float
    y: float
    type: int
    neigbourhood: int = 0
    
    @property
    def coords(self):
        return self.x, self.y
    
    def move_out(self, dist, city_size):
        angle = random.uniform(0, 2 * math.pi)
        self.x = (self.x + math.cos(angle) * dist + city_size) % city_size    
        self.y = (self.y + math.sin(angle) * dist + city_size) % city_size   
    
if __name__ == '__main__':
    m = Member(0, 0, 1)
    print(m)