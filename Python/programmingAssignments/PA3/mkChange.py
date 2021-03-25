import numpy as np
import sys

coins = [1,5,10,25]
calls = 0
reads = 0

  
''' Making Change based on the either or recursion
    slide 6 06-coinsPA lecture
'''
#This is the recursive function 
def mkChangeDC(n, c):
   global calls
   global coins

   # increment global calls with 1
   calls+=1
   if (c == 0): 
      return 1
   if (c> 0):
      if n < coins[c]:
         return mkChangeDC(n, c-1)
      else:
         return mkChangeDC((n - coins[c]), c) + mkChangeDC(n, c-1)  
      


''' Dynamic Programming version of mkChangeDC'''     
def mkChangeDP(cap):
   global calls
   calls += 1
   global reads
   global coins
    # We need n+1 rows as the table is constructed  
    # in bottom up manner using the base case 0 value 
    # case (n = 0) 
   table = [1]+[0]*cap
   for coin in coins:
      for i in range(coin,cap+1):
         table[i]+=table[i-coin]
         for k in range(3):
            if k == 2:
               reads +=1
   return table[cap-1]




if __name__ == "__main__":
   c = len(coins)-1
   print()
   print("Making change with coins:", coins)

   # performance data: [[n, complexity], ... ]
   dataDC  = []
   dataDP  = []
   
   for n in range(200,2050,200):
      print()
      print("Amount:",n)
      
      calls = 0
      ways = mkChangeDC(n,c)
      print("DC", ways, calls, "calls")
      dataDC.append([n,calls])
                        
      reads = 0
      ways = mkChangeDP(n+1)
      print("DP", ways, reads, "reads")
      dataDP.append([n,reads])
      
      
   print("dataDC:", dataDC)
   np.savetxt('dataDC', dataDC, delimiter=',', fmt='%d')

   
   print("dataDP:", dataDP)
   np.savetxt('dataDP', dataDP, delimiter=',', fmt='%d')