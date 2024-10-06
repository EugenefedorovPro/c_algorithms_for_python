import lcs

print(lcs.__doc__)

STR1 = "ABC"
STR2 = "ACD"

print(f"longest common subsequence of '{STR1} and {STR2}' = {lcs.lcs(STR1, STR2)}")
