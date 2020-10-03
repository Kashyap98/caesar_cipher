import os

BASE_HASH = 5381
max_value = 0
hashes = []
values = {}
conflicts = 0
with open(os.path.join(os.getcwd(), "dictionary2.txt"), "r") as dict_file:

    max_hash_value = 0
    words = dict_file.read().split("\n")
    
    print(len(hashes))
    print(len(set(hashes)))

    words = set(words)

    for word in words:
        current_value = 0

        hash_val = 5381
        for letter in word:
            hash_val = hash_val * 33 + ord(letter)

        hash_val = abs(hash_val) % 10000 

        if hash_val > max_hash_value:
            max_hash_value = hash_val

        if hash_val in hashes:
            conflicts += 1
            
            print(values[hash_val])
            print(word)
            print("____________")
        else:
            hashes.append(hash_val)
            values[hash_val] = hash_val
        

print(conflicts)

print(len(hashes))
print(len(set(hashes)))
print(max_hash_value)

