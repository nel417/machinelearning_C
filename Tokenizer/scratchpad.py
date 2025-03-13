text = "If you're visiting this page, you're likely here because you're searching for a random sentence. Sometimes a random word just isn't enough, and that is where the random sentence generator comes into play. By inputting the desired number, you can make a list of as many random sentences as you want or need. Producing random sentences can be helpful in a number of different ways.";

#hashmap
pair_counts = {}

#iterate through text
for char in range(len(text) - 1):
    #a pair is the current character and the next character
    pairs = text[char] + text[char+1]
    #if the pair is already in the hashmap, increment the count
    if pairs in pair_counts:
        pair_counts[pairs] += 1
    #if the pair is not in the hashmap, add it and set the count to 1
    else:
        pair_counts[pairs] = 1

sorted_pairs = sorted(pair_counts.items(), key=lambda item: item[1], reverse=True)

for pair, count in sorted_pairs:
    print(f"{pair} : {count}")


