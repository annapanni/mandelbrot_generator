import matplotlib.pyplot as plt
import json

f = open('mandelbrot.json')
img = json.load(f)
f.close()
finesse = len(img)/2

# plot
plt.style.use('_mpl-gallery-nogrid')
fig, ax = plt.subplots(figsize=(8,6))
plt.subplots_adjust(left=0.08, right=0.95)

ax.imshow(img, extent=(-2, 1, -1, 1), cmap="inferno")

plt.gcf().savefig('mandelbrot.png', dpi=max(finesse/3, 100))
plt.show()





""" without a frame
plt.style.use('_mpl-gallery-nogrid')
fig, ax = plt.subplots(figsize=(9,6), frameon=False)
plt.subplots_adjust(left=0.08, right=0.95)

ax = plt.Axes(fig, [0., 0., 1., 1.])
ax.set_axis_off()
fig.add_axes(ax)

ax.imshow(img, extent=(-2, 1, -1, 1), cmap="inferno", aspect='auto')

plt.gcf().savefig('mandelbrot.png', dpi=max(finesse/3, 100))
plt.show()
"""
