import tensorflow as tf
import keras as K
import numpy as np
import matplotlib.pyplot as plt

# test data
x = np.array([i for i in range(10)])
y = np.array([10, 20, 25, 15, 40, 30, 60, 70, 55, 80])

# model
model = K.models.Sequential()
model.add(K.layers.Dense(1, input_dim = 1, activation = "linear"))

# optimizer - stochastic gradient descent
sgd = K.optimizers.SGD(learning_rate = 0.03)
model.compile(optimizer = sgd, loss = "mse", metrics = ["mse"])

# learning
history: K.callbacks.History = model.fit(x, y, epochs = 100)

# predict
predict = model.predict(np.array([18]))
print(predict)

# plot the graph
plt.figure(figsize = (12, 4))
plt.title("Loss")
plt.plot(history.history["loss"], marker = ".", c = "blue", label = "loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.show()
