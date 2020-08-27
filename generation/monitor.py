import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from matplotlib.gridspec import GridSpec
from matplotlib import rcParams
from collections import namedtuple
from time import time

# Disable toolbar on top of the plots
rcParams['toolbar'] = 'None'

# Python translation of the Monitor struct
Monitor = namedtuple('Monitor', ['gen', 'wp', 'lp', 'rw', 'bw', 'numGames', 'ms'])

# Create plots
fig = plt.figure(constrained_layout=True, figsize=(12, 8))
fig.canvas.set_window_title('64W Generation Monitor')
gs = GridSpec(2, 2, figure=fig)
fig.show()
fig.canvas.draw()

ax1 = fig.add_subplot(gs[0, :])
ax1.set_title('Average Winning Points / Losing Points over Time')
ax1.set_xlabel('Generation')
ax1.xaxis.set_major_locator(ticker.MaxNLocator(integer=True))
ax1.set_ylabel('Points')

ax2 = fig.add_subplot(gs[1, 0])
ax2.set_title('Wins by Alliance')

ax3 = fig.add_subplot(gs[1, 1])
ax3.set_title('Execution Time')
ax3.set_xlabel('Generation')
ax3.xaxis.set_major_locator(ticker.MaxNLocator(integer=True))
ax3.set_ylabel('Time (ms)')
warningtext = ax3.text(.5, .5,
  'Warning: Monitor may not\nbe keeping up with Generation Data Output',
  horizontalalignment='center', verticalalignment='center', transform=ax3.transAxes)
warningtext.set_visible(False)

# Arrays containing data to be plotted
gen = []
awp = []
alp = []
ap = []
ms = []
rw = 0
bw = 0

# Turn on interactive mode in matplotlib
plt.ion()

# Function to update the plot when new data comes in
def graph():
  g, = ax1.plot(gen, awp, c='green', label='Avg. Winning Points')
  p, = ax1.plot(gen, ap, c='purple', label='Avg. Points')
  o, = ax1.plot(gen, alp, c='orange', label='Avg. Losing Points')
  ax1.legend(loc='lower left', handles=[g, p, o])
  ax1.set_ylim(0, 1.1*max(awp))

  ax2.pie([rw, bw], colors=['red', 'blue'], startangle=90)
  ax2.axis('equal')

  ax3.plot(gen, ms, c='gray')
  ax3.set_ylim(0, 1.1*max(ms))

  #fig.draw(fig.canvas.renderer)
  plt.show(block=False)
  plt.pause(.001)

# Main loop
while True:
  data = []
  line = input() # Collect input and wait for the :begin signal or the :done signal

  if line == ':begin':
    tstart = time()
    line = input()
    while line != ':end': # Collect data until the :end signal
      data.append(int(line))
      line = input()

    mon = Monitor._make(data) # Make a Monitor namedtuple out of the inputted data
    gen.append(mon.gen + 1)
    awp.append(mon.wp / mon.numGames)
    alp.append(mon.lp / mon.numGames)
    ap.append((mon.wp + mon.lp) / (mon.numGames * 2))
    ms.append(mon.ms)
    rw += mon.rw
    bw += mon.bw

    graph() # Update the on-screen plot

    warningtext.set_visible(time() - tstart > mon.ms / 1000)

  elif line == ':done':
    break

  else:
    print(line) # Any input that's not data gets passed through to the command-line

# After the program exits, keep the window open
plt.ioff()
plt.show()
