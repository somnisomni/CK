import tensorflow as tf
import numpy as np
import keras

# training data
x = np.array([
  [1, 2],
  [2, 3],
  [3, 1],
  [4, 3],
  [5, 3],
  [6, 2]
])
y = np.array([
  [0],
  [0],
  [0],
  [1],
  [1],
  [1]
])

# modeel
model = keras.Sequential()
model.add(keras.layers.Dense(units = 1, input_dim = 2, activation = "sigmoid"))

# optimizer
sgd = keras.optimizers.SGD(learning_rate = 0.01)
model.compile(loss = "binary_crossentropy", optimizer = sgd, metrics = ["accuracy"])
model.summary()

# training
history: keras.callbacks.History = model.fit(x, y, epochs = 500)

# predict
predict = model.predict(x)
predictCasted = tf.cast(predict > 0.5, dtype = np.float32)
print("\nPrediction\n", predictCasted)
