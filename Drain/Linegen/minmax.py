f = open('xy.txt', 'r')
full = f.read()
pairs = full.split()
x = []
y = []
first = True
for element in pairs:
    if element == ';':
        continue #ignore
    two = element.split(',')
    x.append(float(two[0]))
    y.append(float(two[1]))
# print(min(x), max(x), min(y), max(y))
xavg = (min(x)+max(x))/2
yavg = (min(y)+max(y))/2
# shift coordinates to be centered at 0,0
for i in xrange(len(x)):
    x[i] -= xavg
    y[i] -= yavg
# scale to fit 853x480
xscale = 852/(abs(min(x))+abs(max(x)))
yscale = 480/(abs(min(y))+abs(max(y)))
for i in xrange(len(x)):
    x[i] *= xscale
    y[i] *= yscale
print(min(x), max(x), min(y), max(y))
