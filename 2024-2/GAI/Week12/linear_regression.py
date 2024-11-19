import numpy as np
import matplotlib.pyplot as plt

# w, b: weights and bias
w = -2
b = 40

# test data
x = np.array([i for i in range(10)])
y = np.array([10, 20, 25, 15, 40, 30, 60, 70, 55, 80])

# yHat (Wx)
yHat = x * w + b

# learning setup
learningRate = 0.03
epoch = 500 + 1       # epoch: the number of iterations

# weights and losses
weights = []
losses = []

# gradient descent algorithm
for i in range(epoch):
  yHat = x * w + b
  error = y - yHat

  # calculate the cost(loss)
  loss = np.sum((y - yHat) ** 2) / len(x)
  losses.append(loss)
  print(f"#{i}, Loss: {loss}")

  # partial derivative of w, b
  wDiff = -(2 / len(x)) * np.sum(x * error)
  bDiff = -(2 / len(x)) * np.sum(error)

  # update w, b
  w = w - learningRate * wDiff
  b = b - learningRate * bDiff
  weights.append(w)

# plot the graph
yHat = x * w + b

plt.subplot(1, 3, 1)
plt.plot(x, y, '.-')
plt.plot(x, yHat, '-')

plt.subplot(1, 3, 2)
plt.plot(losses, 'o-')
plt.tight_layout()

plt.subplot(1, 3, 3)
plt.plot(weights, losses, 'o-')
plt.tight_layout()

plt.show()
