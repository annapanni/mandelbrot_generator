import matplotlib.pyplot as plt

finesse = 500

img = [[0 for x in range(-2*finesse, 1*finesse)] for y in range(-1*finesse, 1*finesse)]

def nem_korlatos(re, im):
    zn_re = re
    zn_im = im
    for i in range(1,90):
        zn_re, zn_im = zn_re**2 -zn_im**2 + re, 2*zn_re*zn_im + im
        if zn_re**2 + zn_im**2 > 4:
            return i
    return -20

for i in range(2*finesse):
    for j in range(3*finesse):
        img[i][j] = nem_korlatos((j-finesse*2)/finesse, (i-finesse)/finesse)


# plot
plt.style.use('_mpl-gallery-nogrid')
fig, ax = plt.subplots(figsize=(8,6))
plt.subplots_adjust(left=0.08, right=0.95)

ax.imshow(img, extent=(-2, 1, -1, 1), cmap="inferno")

plt.show()
