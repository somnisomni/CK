import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import keras

# training data
data = np.loadtxt("diabetes.csv", delimiter = ",", dtype = np.float32)
x = data[:, 0:-1]
y = data[:, [-1]]

# data shape
xDim = tf.shape(x)[1].numpy()
yDim = tf.shape(y)[1].numpy()
print("xDim:", xDim, " yDim:", yDim)

# model
model = keras.models.Sequential()
model.add(keras.layers.Dense(units = yDim, input_dim = xDim))
model.add(keras.layers.Activation("sigmoid"))

# optimizer
sgd = keras.optimizers.SGD(learning_rate = 0.01)
model.compile(loss = "binary_crossentropy", optimizer = sgd, metrics = ["accuracy"])
model.summary()

# training
history: keras.callbacks.History = model.fit(x, y, epochs = 500)
print("\nAccuracy: ", history.history["accuracy"][-1], "  Loss: ", history.history["loss"][-1], "\n")

# predict
xInput = np.array([[0.17, 0.15, 0, 0, 0, 0.05, -0.09, -0.07]])
predict = tf.cast(model.predict(xInput) > 0.5, dtype = np.float32)
print("Predict: ", predict, "\n")

# plot
plt.figure(figsize = (12, 4))
plt.title("Loss & Accuracy")
plt.plot(history.history["loss"], c = "blue", label = "loss")
plt.plot(history.history["accuracy"], marker = ".", c = "red", label = "accuracy")
plt.xlabel("Epoch")
plt.ylabel("Loss & Accuracy")
plt.legend()
plt.show()
