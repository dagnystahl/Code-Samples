#Dagny Stahl
#Knapsack problem
#8/32/2020

from itertools import combinations
import time

def create_powerset(items, n): #helper
    powerset = []
    for i in range(n + 1):
        #add all the combos of i pairs to the powerset list
        powerset += list(combinations(items, i)) 
    return powerset

def ratio(pair): #helper, just return tuple ratio
    return pair[1]/pair[0]

def print_formatted_output(knapsack, item_dict): #makes the answer look nice
    value = 0
    item_nums = []
    for item in knapsack:
        value += item[1]
        item_nums.append(item_dict[item])
    item_nums.sort()
    print()
    print(value)
    for item_num in item_nums:
        print(item_num, end=' ')
        

def value_weight_sort(items, n): #helper, sorts based on value ratio
    #insertion sort
    for j in range(1, n):
        temp = items[j]
        i = j - 1
        while i >= 0 and ratio(items[i]) <= ratio(temp):
            #sort by value when equal
            if ratio(items[i]) == ratio(temp):
                if items[i][1] > temp[1]:
                    break  
            items[i + 1] = items[i]
            i -= 1
        items[i+1] = temp
    return items

def exhaustive(max_weight, n, items):
    powerset = create_powerset(items, n) #creates list of tuples that is the powerset
    knapsack = []
    best_val = 0
    for subset in powerset: #check every combo
        subset_val = 0
        subset_weight = 0
        for pair in subset:
            subset_val += pair[1]
            subset_weight += pair[0]
        #check if better than current best
        if subset_weight <= max_weight and subset_val > best_val:
            best_val = subset_val
            knapsack = subset
    return knapsack
    
def heuristic(max_weight, n, items):
    knapsack = []
    current_weight = max_weight
    sorted_items = value_weight_sort(items, n)
    #fit the best value/weight items in order
    for pair in sorted_items:
        if pair[0] <= current_weight:
            knapsack.append(pair)
            current_weight -= pair[0]
    return knapsack

#program
all_lines = []
with open("25.dat", mode='r') as f:
    all_lines = f.readlines()
    
capacity = int(all_lines[0])
n = int(all_lines[1])
all_lines = all_lines[2:] #chop off the first 2 elements
item_dict = {}
items = []
for i,line in enumerate(all_lines,1): #build item list and dict
    nums = line.split(" ")
    pair = (int(nums[0]), int(nums[1]))
    items.append(pair)
    item_dict[pair] = i

items2 = items.copy()

#call exhaustive approach
print("Exhaustive approach", end='')
start = time.perf_counter()
knapsack = exhaustive(capacity, n, items)
print_formatted_output(knapsack, item_dict)
end = time.perf_counter()
seconds = end - start
minutes = seconds / 60
print("\nruntime: ", seconds, "seconds ", minutes, " minutes\n")

#call heuristic approach
print("Greedy Heuristic approach", end='')
start = time.perf_counter()
knapsack = heuristic(capacity, n, items2)
print_formatted_output(knapsack, item_dict)
end = time.perf_counter()
seconds = end - start
minutes = seconds / 60
print("\nruntime:", seconds, "seconds ", minutes, "minutes\n")
    
    
