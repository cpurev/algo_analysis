from itertools import combinations

class Card:
    def __init__(self, value, suite):
        self.value = value
        self.suite = suite
    def __str__(self):
        return f"{self.value} of {self.suite}"
    def __lt__(self, other):
         return self.value < other.value

# Create our deck        
suites = ["Hearts", "Clubs", "Spades", "Diamonds"]
deck = [Card(value, suite) for value in range(1, 14) for suite in suites]

# Combinations are tuple
# Written for 3 cards
def indentifier(combo):
    if(combo[0].value == combo[1].value and combo[1].value == combo[2].value):
        return "3K"
    if(combo[0].value == combo[1].value or combo[0].value == combo[2].value or combo[1].value == combo[2].value):
        return "PR"
    flush = False
    if(combo[0].suite == combo[1].suite and combo[0].suite == combo[2].suite):
        flush = True
    straight = False
    sorted(combo)
    if(combo[1].value == combo[2].value + 1 and combo[2].value == combo[3].value + 1 ):
        straight = True
    if(combo[0].value == 1 and combo[1].value == 12 and combo[2].value == 13):
        straight = True
    if(straight and flush):
        return "SF"
    if(straight):
        return "ST"
    if(flush):
        return "FL"
    return "HC"
    
hand = {
    "3K": 0,
    "PR": 0,
    "SF": 0,
    "ST": 0,
    "FL": 0,
    "HC": 0,
    "total": 0
}
# Create every 3 combinations, 52 Choose 3
for combo in combinations(deck, 3):
    hand["total"] += 1
    hand[indentifier(combo)] += 1
    
print(hand)
