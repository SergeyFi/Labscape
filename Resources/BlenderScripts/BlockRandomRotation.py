import bpy
import math
import random

def main():
    
    for object in bpy.context.selected_objects:
        rotation_x = object.rotation_euler.x
        rotation_y = object.rotation_euler.y
        
        rotations = [0, 90, 180, 270]
        
        object.rotation_euler = [rotation_x, rotation_y, math.radians(random.choice(rotations))]
    
main()