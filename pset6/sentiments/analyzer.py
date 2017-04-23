import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        self.negatives = []
        self.positives = []

        with open("negative-words.txt") as negative:
            for line in negative:
                if line.startswith((";", " ")):
                    continue
                else:
                    self.negatives.extend(line.split())

        with open("positive-words.txt") as positive:
            for line in positive:
                if line.startswith((";", " ")):
                    continue
                else:
                    self.positives.extend(line.split())
    
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        score = 0

        for token in tokens:
            token.lower()

            if token in self.positives:
                score += 1
            elif token in self.negatives:
                score -= 1

        return score