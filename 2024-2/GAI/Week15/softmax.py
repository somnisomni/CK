from tensorflow.keras.datasets import fashion_mnist
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import keras

(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()

print("x_train: ", x_train.shape)
print("y_train: ", y_train.shape)
print("x_train[0]: ", x_train[0])
print("y_train[0]: ", y_train[0])
print()

# Flatten
x_train = x_train.reshape(60000, 784)
x_test = x_test.reshape(10000, 784)

# Normalize
x_train = x_train / 255
x_test = x_test / 255

print("after flatten/normalize x_train min: ", x_train.min())
print("after flatten/normalize x_train max: ", x_train.max())
print()

# category
num_category = 10
y_train = tf.keras.utils.to_categorical(y_train, num_classes = num_category)
y_test = tf.keras.utils.to_categorical(y_test, num_classes = num_category)
print("after categorization y_train[0:9]: ", y_train[0:9])

# model
model = keras.Sequential()
model.add(keras.layers.Dense(units = 512, activation = "relu", input_shape = (784,)))  # input
model.add(keras.layers.Dense(units = 512, activation = "relu"))  # hidden
model.add(keras.layers.Dense(units = 10, activation = "softmax"))  # output
model.summary()
model.compile(optimizer = "adam", loss = "categorical_crossentropy", metrics = ["accuracy"])

# train
history = model.fit(x_train, y_train, epochs = 10)

# accuracy / loss plot
fig, loss_ax = plt.subplots()
acc_ax = loss_ax.twinx()
loss_ax.plot(history.history["loss"], "y", label = "train loss")
acc_ax.plot(history.history["accuracy"], "b", label = "train accuracy")
loss_ax.set_xlabel("epoch")
loss_ax.set_ylabel("loss")
acc_ax.set_ylabel("accuracy")
loss_ax.legend(loc = "upper left")
acc_ax.legend(loc = "lower left")
plt.show()

# label
classes = ["T-shirt/top", "Trouser", "Pullover", "Dress", "Coat", "Sandal", "Shirt", "Sneaker", "Bag", "Ankle boot"]

# evaluate
model.evaluate(x_test, y_test)
predict = model.predict(x_test[115:180])
print("predict #115: ", classes[np.argmax(y_test[115])])

img = x_test.reshape(10000, 28, 28)
plt.imshow(img[115], cmap = "gray")
plt.show()
