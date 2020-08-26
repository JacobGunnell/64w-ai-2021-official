import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from collections import namedtuple

# Python translation of the Monitor struct
Monitor = namedtuple('Monitor', ['gen', 'wp', 'lp', 'rw', 'bw', 'numGames', 'ms'])

# Arrays containing data to be plotted
gen = []
awp = []
alp = []
ap = []
ms = []

# Turn on interactive mode in matplotlib
plt.ion()
plt.show()

# Function to update the plot when new data comes in
def graph():
  plt.title("Average Winning Points / Losing Points over Time")
  g, = plt.plot(gen, awp, c='green', label='Avg. Winning Points')
  o, = plt.plot(gen, alp, c='orange', label='Avg. Losing Points')
  plt.xlabel("Generation")
  plt.legend(loc='lower left', handles=[g, o])
  #ax.xaxis.set_major_locator(ticker.MaxNLocator(integer=True))
  plt.draw()
  plt.pause(.001)

# Main loop
while True:
  data = []
  line = input() # Collect input and wait for the :begin signal or the :done signal

  if line == ":done":
    break

  elif line == ":begin":
    line = input()
    while line != ":end": # Collect data until the :end signal
      data.append(int(line))
      line = input()
    mon = Monitor._make(data) # Make a Monitor namedtuple out of the inputted data
    gen.append(mon.gen + 1)
    awp.append(mon.wp / mon.numGames)
    alp.append(mon.lp / mon.numGames)
    ap.append(mon.wp + mon.lp / (mon.numGames * 2))
    ms.append(mon.ms)
    graph() # Update the on-screen plot

  else:
    print(line) # Any input that's not data gets passed through to the command-line

# After the program exits, keep the window open
plt.ioff()
plt.show()
