import bpy
import math
import random

def main():
    
    for object in bpy.context.selected_objects:
    
        
        object.delta_location.x = random.uniform(0.0, 1.0)
    
main()