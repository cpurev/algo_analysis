# threeCardPokerOptimized.py
# Calculate the optimal startegy to draw on all possible 3 card poker hand
# Written for 3 card hands, deck size 52
from itertools import combinations

class Card:
    def __init__(self, value, suite):
        self.value = value
        self.suite = suite
    def __str__(self):
        return f"{self.value} of {self.suite}"
    def __repr__(self):
        return str((self.value, self.suite))
    def __eq__(self, other):
        if isinstance(other, Card):
            return self.value == other.value and self.suite == other.suite
        return NotImplemented

# Create our deck        
suites = ["Hearts", "Clubs", "Spades", "Diamonds"]
deck = [Card(value, suite) for value in range(1, 14) for suite in suites]

# Hand value table
rTable = {
    "RF": 250,
    "SF": 50,
    "3A": 100,
    "3K": 40,
    "ST": 10,
    "FL": 5,
    "PR": 1,
    "HC": 0
}

# Optimize the hand by drawing(0, 1, 2 or 3 cards)
# Replaced cards will not be put back into deck
# hand - tuple of hands i.e. (Card1, Card2, Card3)
# returns maximum expected value 
# and its corresponding draw number(ex: if optimal play is to draw 1 card it will return 1 )
def optimize(hand):
    # Create deck of possible card draws(i.e. deck - hand)
    cardsLeft = [x for x in deck if x not in hand]

    max1, max2 = 0, 0 # Temp max holder
    e1, e2, e3 = 0, 0, 0 # Expected values

    # Redraw 1 card
    # There is 1 in 49 chance of drawing a specific card
    for x in cardsLeft:
        e1 += rTable[indentifier((hand[0], hand[1], x))] / 49
        e2 += rTable[indentifier((hand[0], hand[2], x))] / 49
        e3 += rTable[indentifier((hand[1], hand[2], x))] / 49
    max1 = max(e1, e2, e3)
    
    # Redraw 2 cards
    # Chance of drawing 2 specific cards, which is 49 choose 2 = 1176
    e1, e2, e3 = 0, 0, 0
    for x in combinations(cardsLeft, 2):
        e1 += rTable[indentifier(((hand[0], ) + x))] / 1176
        e2 += rTable[indentifier(((hand[1], ) + x))] / 1176
        e3 += rTable[indentifier(((hand[2], ) + x))] / 1176
    max2 = max(e1, e2, e3)
    
    # Redraw 3 cards, 49 choose 3 = 18424
    e1, e2, e3 = 0, 0, 0
    for x in combinations(cardsLeft, 3):
        e1 += rTable[indentifier(x)] / 18424
        
    # Redraw 0 cards a.k.a current value of hand
    e2 = rTable[indentifier(hand)]

    rMax = max(e1, e2, max2, max1)
    if(rMax == e1):
        return rMax, 3
    if(rMax == e2):
        return rMax, 0
    if(rMax == max2):
        return rMax, 2
    if(rMax == max1):
        return rMax, 1
    return 0, -1

# Identify poker hand
# combo must be a tuple
def indentifier(combo):
    if(combo[0].value == 1 and combo[1].value == 1 and combo[2].value == 1):
        return "3A"
    if(combo[0].value == combo[1].value and combo[1].value == combo[2].value):
        return "3K"
    if(combo[0].value == combo[1].value or combo[0].value == combo[2].value or combo[1].value == combo[2].value):
        return "PR"
    flush = False
    if(combo[0].suite == combo[1].suite and combo[0].suite == combo[2].suite):
        flush = True
    straight = False
    sortCombo = sorted(combo, key=lambda x: x.value) # sort by card rank
    if(sortCombo[2].value == (sortCombo[1].value + 1) and sortCombo[1].value == (sortCombo[0].value + 1 )):
        straight = True
    if(flush and sortCombo[0].value == 1 and sortCombo[1].value == 12 and sortCombo[2].value == 13):
       return "RF"
    if(sortCombo[0].value == 1 and sortCombo[1].value == 12 and sortCombo[2].value == 13):
       straight = True
    if(straight and flush):
        return "SF"
    if(straight):
        return "ST"
    if(flush):
        return "FL"
    return "HC"

return_table = {
    "RF": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "SF": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "3A": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "3K": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "ST": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "FL": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "PR": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } },
    "HC": { 3: { "count": 0, "E": 0 }, 2: { "count": 0, "E": 0 }, 1: { "count": 0, "E": 0 }, 0: { "count": 0, "E": 0 } }
}
for x in combinations(deck, 3):
    hand = indentifier(x)
    exp, play = optimize(x)
    return_table[hand][play]["count"] += 1
    return_table[hand][play]["E"] += exp

print(return_table)