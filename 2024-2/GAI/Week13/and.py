import keras
import numpy as np
import tensorflow as tf

# training data
x = np.array([
  [0, 0],
  [0, 1],
  [1, 0],
  [1, 1]
])
y = np.array([
  [0],
  [0],
  [0],
  [1]
])

# model
model = keras.models.Sequential()
model.add(keras.layers.Dense(units = 1, input_dim = 2, activation = "sigmoid"))

sgd = keras.optimizers.SGD(learning_rate = 0.1)
model.compile(loss = "binary_crossentropy", optimizer = sgd, metrics = ["accuracy"])
model.summary()

# fit
history: keras.callbacks.History = model.fit(x, y, epochs = 500)

# predict
predict = model.predict(x)
predictCasted = tf.cast(predict > 0.5, dtype = np.float32)
print("\nPrediction\n", predict)
print("\nPrediction (Casted)\n", predictCasted.numpy())

score = model.evaluate(x, y)
print("\nAccuracy\n", score)
