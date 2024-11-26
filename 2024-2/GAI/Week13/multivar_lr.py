import keras
import numpy as np
import matplotlib.pyplot as plt
import os

# training data
'''
x = np.array([
  [14.0, 80.0,  73.0],
  [18.0, 88.0,  95.0],
  [20.0, 98.0, 100.0],
  [14.0, 66.0,  70.0]
])
y = np.array([
  [100.0],
  [131.0],
  [129.0],
  [143.0],
#  [ 98.0]
])
'''
input_data = np.loadtxt(("testdata.csv"), delimiter = ",", dtype = np.float32)
x = input_data[:, 0:-1]
y = input_data[:, [-1]]
x_dim = np.shape(x)[1]
y_dim = np.shape(y)[1]

# model
model = keras.models.Sequential()
# model.add(keras.layers.Dense(units = 1, input_dim = 3))
model.add(keras.layers.Dense(units = y_dim, input_dim = x_dim))
model.add(keras.layers.Activation("linear"))

# optimizer
sgd = keras.optimizers.SGD(learning_rate = 1e-5)
model.compile(loss = "mse", optimizer = sgd)

model.summary()

# learning
history: keras.callbacks.History = model.fit(x, y, epochs = 500)

# predict
predict = model.predict(np.array([[72.0, 93.0, 90.0]]))
print(predict)

# plot the graph
plt.figure(figsize = (12, 4))
plt.title("Loss")
plt.plot(history.history["loss"], marker = ".", c = "blue", label = "loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.show()
